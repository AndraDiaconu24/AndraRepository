/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body (Nucleo-F401RE + FreeRTOS)
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PD */

/* Task periods (ms) */
#define TEMP_TASK_PERIOD_MS      500U
#define POT_BTN_TASK_PERIOD_MS    20U
#define UART_TASK_PERIOD_MS      500U

/* PWM configuration */
#define PWM_MAX_COUNTS           999U
#define PWM_FREQUENCY_HZ        1000U

/* Button debounce */
#define BTN_DEBOUNCE_MS           80U

/* NTC thermistor configuration (NTC 10k, Beta 3950, R_fixed 10k) */
#define R_FIXED_OHMS           10000.0f
#define NTC_R0_OHMS            10000.0f
#define NTC_BETA               3950.0f
#define NTC_T0_KELVIN          298.15f

/* Temperature control thresholds (°C) */
#define TEMP_THRESHOLD_MIN       25.0f
#define TEMP_THRESHOLD_LOW       25.0f
#define TEMP_THRESHOLD_MID       27.0f
#define TEMP_THRESHOLD_HIGH      30.0f

/* PWM percentages at temperature thresholds */
#define PWM_PERCENT_AT_LOW       30U
#define PWM_PERCENT_AT_MID       50U
#define PWM_PERCENT_AT_HIGH     100U

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart2;

osThreadId_t TempTaskHandle;
osThreadId_t PotTaskHandle;
osThreadId_t PwmTaskHandle;
osThreadId_t UartTaskHandle;

const osThreadAttr_t TempTask_attributes = {
  .name = "TempTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t PotTask_attributes = {
  .name = "PotTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};

const osThreadAttr_t PwmTask_attributes = {
  .name = "PwmTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 384 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

osMessageQueueId_t qPwmHandle;
const osMessageQueueAttr_t qPwm_attributes = { .name = "qPwm" };

/* USER CODE BEGIN PV */
static volatile uint16_t g_currentDuty = 0U;
/* Button state machine */
typedef enum {
    BTN_STATE_IDLE = 0,
    BTN_STATE_PRESSED,
    BTN_STATE_DEBOUNCE
} ButtonState_t;

/* Mutex for ADC */
static osMutexId_t adcMutexHandle;

/* System state */
static volatile uint8_t g_manualMode = 0U;
static volatile float   g_temperature = 0.0f;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);

void StartTempTask(void *argument);
void StartPotTask(void *argument);
void StartPwmTask(void *argument);
void StartUartTask(void *argument);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* ===================== PRIVATE FUNCTIONS ===================== */

/**
 * @brief Read single ADC channel with mutex protection
 */
static uint16_t ADC_ReadSingleChannel(uint32_t channel)
{
    uint16_t adcValue = 0U;
    ADC_ChannelConfTypeDef channelConfig = {0};

    osMutexAcquire(adcMutexHandle, osWaitForever);

    channelConfig.Channel = channel;
    channelConfig.Rank = 1;
    channelConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
    (void)HAL_ADC_ConfigChannel(&hadc1, &channelConfig);

    (void)HAL_ADC_Start(&hadc1);
    (void)HAL_ADC_PollForConversion(&hadc1, 10);
    adcValue = (uint16_t)HAL_ADC_GetValue(&hadc1);
    (void)HAL_ADC_Stop(&hadc1);

    osMutexRelease(adcMutexHandle);

    return adcValue;
}

/**
 * @brief Convert NTC ADC reading to temperature
 */
static float NTC_ConvertToTemperature(uint16_t adcValue)
{
    if (adcValue <= 1U)    { return -40.0f; }
    if (adcValue >= 4094U) { return 125.0f; }

    float adcFloat = (float)adcValue;
    float resistanceNTC = R_FIXED_OHMS * (adcFloat / (4095.0f - adcFloat));

    float inverseTemp = (1.0f / NTC_T0_KELVIN) + (1.0f / NTC_BETA) * logf(resistanceNTC / NTC_R0_OHMS);
    float tempKelvin = 1.0f / inverseTemp;
    float tempCelsius = tempKelvin - 273.15f;

    return tempCelsius;
}

/**
 * @brief Convert temperature to PWM duty cycle
 */
static uint16_t Temperature_CalculateDuty(float temperature)
{
    if (temperature < TEMP_THRESHOLD_MIN) {
        return 0U;
    }

    if (temperature >= TEMP_THRESHOLD_HIGH) {
        return PWM_MAX_COUNTS;
    }

    float pwmPercent = 0.0f;

    if (temperature <= TEMP_THRESHOLD_MID) {
        float tempRange = TEMP_THRESHOLD_MID - TEMP_THRESHOLD_LOW;
        float tempDelta = temperature - TEMP_THRESHOLD_LOW;
        float pwmRange = (float)(PWM_PERCENT_AT_MID - PWM_PERCENT_AT_LOW);
        pwmPercent = (float)PWM_PERCENT_AT_LOW + (tempDelta / tempRange) * pwmRange;
    }
    else {
        float tempRange = TEMP_THRESHOLD_HIGH - TEMP_THRESHOLD_MID;
        float tempDelta = temperature - TEMP_THRESHOLD_MID;
        float pwmRange = (float)(PWM_PERCENT_AT_HIGH - PWM_PERCENT_AT_MID);
        pwmPercent = (float)PWM_PERCENT_AT_MID + (tempDelta / tempRange) * pwmRange;
    }

    uint16_t dutyValue = (uint16_t)((pwmPercent * (float)PWM_MAX_COUNTS) / 100.0f);

    if (dutyValue > PWM_MAX_COUNTS) {
        dutyValue = PWM_MAX_COUNTS;
    }

    return dutyValue;
}

/**
 * @brief Convert potentiometer ADC to PWM duty
 */
static uint16_t Potentiometer_CalculateDuty(uint16_t adcValue)
{
    return (uint16_t)(((uint32_t)adcValue * PWM_MAX_COUNTS) / 4095U);
}

/**
 * @brief Send duty to queue
 */
static void PWM_SendDutyToQueue(uint16_t duty)
{
    osStatus_t status = osMessageQueuePut(qPwmHandle, &duty, 0U, 0U);

    if (status == osErrorResource) {
        (void)osMessageQueueReset(qPwmHandle);
        (void)osMessageQueuePut(qPwmHandle, &duty, 0U, 0U);
    }
}

/**
 * @brief Apply PWM duty to hardware
 */
static void PWM_ApplyDutyCycle(uint16_t duty)
{
    if (duty > PWM_MAX_COUNTS) {
        duty = PWM_MAX_COUNTS;
    }
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
}

/**
 * @brief Print status via UART
 */
static void UART_PrintStatus(void)
{
    char buffer[128];
    uint16_t currentDuty = g_currentDuty;


    float tempCopy = g_temperature;
    int16_t tempInteger = (int16_t)tempCopy;
    uint16_t tempDecimal = (uint16_t)((tempCopy - (float)tempInteger) * 100.0f);

    if (tempCopy < 0.0f) {
        tempInteger = (int16_t)tempCopy;
        tempDecimal = (uint16_t)(((float)tempInteger - tempCopy) * 10.0f);
    }

    uint16_t dutyPercent = (uint16_t)((currentDuty * 100U) / PWM_MAX_COUNTS);

    int msgLength = snprintf(buffer, sizeof(buffer),
                            "MODE=%s | TEMP=%d.%u°C | PWM=%u/%u (%u%%)\r\n",
                            (g_manualMode ? "MANUAL" : "AUTO  "),
                            tempInteger,
                            tempDecimal,
                            currentDuty,
                            PWM_MAX_COUNTS,
                            dutyPercent);

    (void)HAL_UART_Transmit(&huart2, (uint8_t*)buffer, (uint16_t)msgLength, 100);
}

/* USER CODE END 0 */

int main(void)
{
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    HAL_Init();
    SystemClock_Config();

    /* USER CODE BEGIN 2 */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM2_Init();

    (void)HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    /* USER CODE END 2 */

    osKernelInitialize();

    /* USER CODE BEGIN RTOS_MUTEX */
    const osMutexAttr_t adcMutex_attributes = { .name = "adcMutex" };
    adcMutexHandle = osMutexNew(&adcMutex_attributes);
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    qPwmHandle = osMessageQueueNew(5, sizeof(uint16_t), &qPwm_attributes);
    /* USER CODE END RTOS_QUEUES */

    /* USER CODE BEGIN RTOS_THREADS */
    TempTaskHandle = osThreadNew(StartTempTask, NULL, &TempTask_attributes);
    PotTaskHandle  = osThreadNew(StartPotTask,  NULL, &PotTask_attributes);
    PwmTaskHandle  = osThreadNew(StartPwmTask,  NULL, &PwmTask_attributes);
    UartTaskHandle = osThreadNew(StartUartTask, NULL, &UartTask_attributes);
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* USER CODE END RTOS_EVENTS */

    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* USER CODE BEGIN 3 */
    while (1) { }
    /* USER CODE END 3 */
}

/* ================= PERIPHERAL INITIALIZATION ================= */

void SystemClock_Config(void)
{
    /* USER CODE BEGIN SystemClock_Config */
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE END SystemClock_Config */
}

static void MX_ADC1_Init(void)
{
    /* USER CODE BEGIN ADC1_Init 0 */
    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef channelConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */
    /* USER CODE END ADC1_Init 1 */

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        Error_Handler();
    }

    channelConfig.Channel = ADC_CHANNEL_0;
    channelConfig.Rank = 1;
    channelConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &channelConfig) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */
    /* USER CODE END ADC1_Init 2 */
}

static void MX_TIM2_Init(void)
{
    /* USER CODE BEGIN TIM2_Init 0 */
    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef clockConfig = {0};
    TIM_MasterConfigTypeDef masterConfig = {0};
    TIM_OC_InitTypeDef outputConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */
    /* USER CODE END TIM2_Init 1 */

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 83;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = PWM_MAX_COUNTS;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    clockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &clockConfig) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &masterConfig) != HAL_OK) {
        Error_Handler();
    }

    outputConfig.OCMode = TIM_OCMODE_PWM1;
    outputConfig.Pulse = 0;
    outputConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    outputConfig.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &outputConfig, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */
    /* USER CODE END TIM2_Init 2 */

    HAL_TIM_MspPostInit(&htim2);
}

static void MX_USART2_UART_Init(void)
{
    /* USER CODE BEGIN USART2_Init 0 */
    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */
    /* USER CODE END USART2_Init 1 */

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */
    /* USER CODE END USART2_Init 2 */
}

static void MX_GPIO_Init(void)
{
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    GPIO_InitTypeDef gpioConfig = {0};
    /* USER CODE END MX_GPIO_Init_1 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    gpioConfig.Pin = GPIO_PIN_13;
    gpioConfig.Mode = GPIO_MODE_INPUT;
    gpioConfig.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &gpioConfig);
    /* USER CODE END MX_GPIO_Init_2 */
}

/* ===================== FREERTOS TASKS ===================== */

/* USER CODE BEGIN Header_StartTempTask */
/**
 * @brief Temperature reading task
 */
/* USER CODE END Header_StartTempTask */
void StartTempTask(void *argument)
{
    /* USER CODE BEGIN StartTempTask */
    (void)argument;

    for (;;)
    {
        uint16_t adcNTC = ADC_ReadSingleChannel(ADC_CHANNEL_0);

        float temperature = NTC_ConvertToTemperature(adcNTC);
        g_temperature = temperature;

        if (g_manualMode == 0U)
        {
            uint16_t dutyValue = Temperature_CalculateDuty(temperature);
            PWM_SendDutyToQueue(dutyValue);
        }

        osDelay(TEMP_TASK_PERIOD_MS);
    }
    /* USER CODE END StartTempTask */
}

/* USER CODE BEGIN Header_StartPotTask */
/**
 * @brief Potentiometer and button task
 */
/* USER CODE END Header_StartPotTask */
void StartPotTask(void *argument)
{
    /* USER CODE BEGIN StartPotTask */
    (void)argument;

    static ButtonState_t buttonState = BTN_STATE_IDLE;
    static uint32_t debounceStartTick = 0U;

    for (;;)
    {
        GPIO_PinState buttonPin = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

        switch (buttonState)
        {
            case BTN_STATE_IDLE:
                if (buttonPin == GPIO_PIN_RESET)
                {
                    buttonState = BTN_STATE_PRESSED;
                    debounceStartTick = HAL_GetTick();
                }
                break;

            case BTN_STATE_PRESSED:
                if (buttonPin == GPIO_PIN_SET)
                {
                    buttonState = BTN_STATE_IDLE;
                }
                else if ((HAL_GetTick() - debounceStartTick) >= BTN_DEBOUNCE_MS)
                {
                    g_manualMode ^= 1U;
                    buttonState = BTN_STATE_DEBOUNCE;
                }
                break;

            case BTN_STATE_DEBOUNCE:
                if (buttonPin == GPIO_PIN_SET)
                {
                    buttonState = BTN_STATE_IDLE;
                }
                break;
        }

        if (g_manualMode != 0U)
        {
            uint16_t adcPot = ADC_ReadSingleChannel(ADC_CHANNEL_1);
            uint16_t dutyValue = Potentiometer_CalculateDuty(adcPot);
            PWM_SendDutyToQueue(dutyValue);
        }

        osDelay(POT_BTN_TASK_PERIOD_MS);
    }
    /* USER CODE END StartPotTask */
}

/* USER CODE BEGIN Header_StartPwmTask */
/**
 * @brief PWM output task
 */
/* USER CODE END Header_StartPwmTask */
void StartPwmTask(void *argument)
{
    /* USER CODE BEGIN StartPwmTask */
    (void)argument;
    uint16_t dutyValue = 0U;

    for (;;)
    {
        if (osMessageQueueGet(qPwmHandle, &dutyValue, NULL, osWaitForever) == osOK)
        {
        	PWM_ApplyDutyCycle(dutyValue);
        	g_currentDuty = dutyValue;
        }
    }
    /* USER CODE END StartPwmTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
 * @brief UART status reporting task
 */
/* USER CODE END Header_StartUartTask */
void StartUartTask(void *argument)
{
    /* USER CODE BEGIN StartUartTask */
    (void)argument;

    for (;;)
    {
        UART_PrintStatus();
        osDelay(UART_TASK_PERIOD_MS);
    }
    /* USER CODE END StartUartTask */
}

void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    __disable_irq();
    while (1) { }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    (void)file;
    (void)line;
    /* USER CODE END 6 */
}
#endif
