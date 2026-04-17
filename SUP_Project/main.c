#pragma config OSC = HS
#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 4000000

#define adresa_regIODIRA 0x00
#define adresa_regIODIRB 0x01
#define adresa_regGPIOA  0x12
#define adresa_regGPIOB  0x13

#define CS PORTAbits.RA2
#define SPI1_CLK RC3
#define SPI1_SDI RC4
#define SPI1_SDO RC5

#define linie1_inc 0x80
#define linie2_inc 0xC0
#define length 16

#define BUTON      PORTDbits.RD0
#define LED_ROSU   LATDbits.LATD1
#define LED_GALBEN LATDbits.LATD2
#define LED_VERDE  LATDbits.LATD3

/* TIMER0: Fosc=4MHz, Div=1:32, 8 biti, TMR0L=0
   Nr ˜ 122 overflow-uri pentru ~1 secunda */
volatile int i = 0;
volatile unsigned int sec = 0;


void SPI_init()
{
    TRISCbits.SPI1_CLK = 0;
    TRISCbits.SPI1_SDO = 0;
    TRISCbits.SPI1_SDI = 1;
}

void SPI_open()
{
    SSP1CON1bits.SSPM3 = 0;
    SSP1CON1bits.SSPM2 = 0;
    SSP1CON1bits.SSPM1 = 1;
    SSP1CON1bits.SSPM0 = 0;

    SSP1STATbits.CKE = 1;
    SSP1CON1bits.CKP = 0;
    SSP1STATbits.SMP = 0;

    SSP1CON1bits.SSPEN = 1;
}

void SPI_close()
{
    SSP1CON1bits.SSPEN = 0;
}

char SPI_write(unsigned char data)
{
    SSPBUF = data;
    while(!SSPSTATbits.BF);
    return SSPBUF;
}

void MCP_init()
{
    TRISF = 0x00;
    LATFbits.LATF6 = 1;      /* RESET MCP = 1 */

    TRISAbits.RA2 = 0;       /* CS output */
    CS = 1;
}

void regGPIO_init(char address, char value)
{
    CS = 0;
    SPI_write(0x40);
    SPI_write(address);
    SPI_write(value);
    CS = 1;
}

void regIODIR_init(char address, char dir)
{
    CS = 0;
    SPI_write(0x40);
    SPI_write(address);
    SPI_write(dir);
    CS = 1;
}


void LCD_cmd(char c)
{
    regGPIO_init(adresa_regGPIOA, 0x00);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOB, c);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOA, 0x40);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOA, 0x00);
    __delay_ms(5);
}

void LCD_init()
{
    regIODIR_init(adresa_regIODIRA, 0x00);
    regIODIR_init(adresa_regIODIRB, 0x00);

    LCD_cmd(0b00111111);
    LCD_cmd(0b00001111);
    LCD_cmd(0b00000001);
    LCD_cmd(0b00000110);
}

void LCD_out(char litera, int linie, int coloana)
{
    if(linie == 1)
    {
        LCD_cmd(linie1_inc + coloana);
    }
    if(linie == 2)
    {
        LCD_cmd(linie2_inc + coloana);
    }

    regGPIO_init(adresa_regGPIOA, 0x80);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOB, litera);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOA, 0xC0);
    __delay_ms(5);
    regGPIO_init(adresa_regGPIOA, 0x00);
    __delay_ms(5);
}

void scriere_fix(char* sir, int linie)
{
    int col = 1;

    while(*sir && col <= 16)
    {
        LCD_out(*sir++, linie, col++);
    }
    while(col <= 16)
    {
        LCD_out(' ', linie, col++);
    }
}


{
    scriere_fix("VERDE PIETONI", 1);
    scriere_fix("TIMP: 05s", 2);   /* incepem direct cu 05 */
}

void afisare_galben_start()
{
    scriere_fix("GALBEN", 1);
    scriere_fix("TIMP: 03s", 2);   /* incepem direct cu 03 */
}

void update_secunde(unsigned char secunde)
{
    LCD_out((char)('0' + (secunde / 10)), 2, 7);
    LCD_out((char)('0' + (secunde % 10)), 2, 8);
}

void timer0_init()
{
    INTCONbits.GIE = 1;

    T0CONbits.T08BIT = 1; /* 8 biti */
    T0CONbits.T0CS   = 0; /* timer (Fosc/4) */
    T0CONbits.PSA    = 0; /* prescaler activ */

    /* 1:32 => T0PS = 100 */
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 0;

    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;

    TMR0L = 0;
    T0CONbits.TMR0ON = 1;
}

void interrupt t0()
{
    if(INTCONbits.TMR0IF == 1)
    {
        i++;
        if(i == 122)
        {
            sec++;
            i = 0;
        }
        INTCONbits.TMR0IF = 0;
    }
}

void asteapta_1s()
{
    unsigned int s = sec;
    while(sec == s) { }
}

void semafor_rosu()
{
    LED_ROSU = 1;
    LED_GALBEN = 0;
    LED_VERDE = 0;
}

void semafor_verde()
{
    LED_ROSU = 0;
    LED_GALBEN = 0;
    LED_VERDE = 1;
}

void semafor_galben()
{
    LED_ROSU = 0;
    LED_GALBEN = 1;
    LED_VERDE = 0;
}

char buton_apasat()
{
    if(BUTON)
    {
        __delay_ms(30);
        if(BUTON)
        {
            while(BUTON) { }
            __delay_ms(30);
            return 1;
        }
    }
    return 0;
}

void afisare_rosu()
{
    scriere_fix("APASA BUTONUL", 1);
    scriere_fix("PENTRU VERDE", 2);
}

void init()
{
    ADCON1 = 0x0F;
    OSCCON = 0x62;

    LATD = 0x00;
    TRISDbits.RD0 = 1; /* buton */
    TRISDbits.RD1 = 0; /* rosu */
    TRISDbits.RD2 = 0; /* galben */
    TRISDbits.RD3 = 0; /* verde */

    MCP_init();
    SPI_init();
    SPI_open();
    LCD_init();

    timer0_init();

    semafor_rosu();
    afisare_rosu();
}

void main(void)
{
    init();

    while(1)
    {
        if(buton_apasat())
        {
            signed char k;

            /* VERDE = 5 sec: 05,04,03,02,01,00 */
            semafor_verde();
            afisare_verde_start();
            update_secunde(5);

            for(k = 4; k >= 0; k--)
            {
                asteapta_1s();
                update_secunde((unsigned char)k);
                if(k == 0) break;
            }

            /* GALBEN = 3 sec: 03,02,01,00 */
            semafor_galben();
            afisare_galben_start();
            update_secunde(3);

            for(k = 2; k >= 0; k--)
            {
                asteapta_1s();
                update_secunde((unsigned char)k);
                if(k == 0) break;
            }

            /* inapoi pe ROSU */
            semafor_rosu();
            afisare_rosu();
        }
        else
        {
            /* ramane pe rosu pana la buton */
        }
    }
}