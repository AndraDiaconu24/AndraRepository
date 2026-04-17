import tkinter as tk
import serial

PORT = "COM4"
BAUD = 115200

try:
    ser = serial.Serial(PORT, BAUD, timeout=0.1)
except Exception as e:
    ser = None
    print(f"Eroare: Nu s-a putut deschide portul {PORT}. Verifică conexiunea USB!")
def citeste_serial():
    if ser and ser.in_waiting > 0:
        try:
            linie = ser.readline().decode(errors="ignore").strip()
            if linie:
                lista_mesaje.insert(0, f"ST32: {linie}")
                if lista_mesaje.size() > 15:
                    lista_mesaje.delete(15)
        except:
            pass
    fereastra.after(100, citeste_serial)
fereastra = tk.Tk()
fereastra.title("Consolă Date STM32")
fereastra.geometry("700x450")
tk.Label(fereastra, text="Date recepționate de la STM32:", font=("Arial", 12, "bold")).pack(pady=10)
lista_mesaje = tk.Listbox(
    fereastra, 
    width=85, 
    height=15, 
    fg="darkgreen", 
    bg="#f0f0f0", 
    font=("Courier New", 10, "bold")
)
lista_mesaje.pack(padx=20, pady=10)
buton_inchide = tk.Button(
    fereastra, 
    text="Închide Aplicația", 
    command=fereastra.quit,
    bg="#e1e1e1",
    padx=20
)
buton_inchide.pack(pady=10)
citeste_serial()
fereastra.mainloop()