import serial
import tkinter as tk

best_results = set()

def read_data(label):
    try:
        ser = serial.Serial('COMX', 9600)  # Zmień COMX na właściwy port szeregowy
        while True:
            data = ser.readline().decode('utf-8').strip()
            label.config(text=data)
            label.place(relx=0.5, rely=0.5, anchor='center')
            label.config(font=("Arial", 40))
            if data.endswith("s"):
                split_data = data.split()
                if len(split_data) >= 5 and split_data[4][:-1].replace('.', '').isdigit():
                    time = split_data[4]  # Pobranie czasu
                    add_to_best_results(time)
            root.update()
    except serial.SerialException as e:
        print("Błąd odczytu danych:", e)

def add_to_best_results(time):
    if time not in best_results:
        best_results.add(time)
        update_results_label()

def update_results_label():
    sorted_results = sorted(best_results, key=lambda x: float(x[:-1]))
    results_label.config(text="\n".join([f"{i + 1}. {time}" for i, time in enumerate(sorted_results)]))

def reset_results():
    global best_results
    best_results = set()
    update_results_label()

root = tk.Tk()
root.title("Odczyt danych")
root.geometry("400x400")
root.configure(bg='white')

main_label = tk.Label(root, text="Główny tekst", bg="white", fg="black")
main_label.pack(pady=20)

results_title_label = tk.Label(root, text="Najlepsze wyniki:", bg="white", fg="black")
results_title_label.place(relx=0.05, rely=0.05, anchor='nw')
results_title_label.config(font=("Arial", 20))

results_label = tk.Label(root, text="", bg="white", fg="black")
results_label.place(relx=0.05, rely=0.1, anchor='nw')
results_label.config(font=("Arial", 17))
update_results_label()

reset_button = tk.Button(root, text="Resetuj", command=reset_results)
reset_button.place(relx=0.19, rely=0.1, anchor='ne')
reset_button.config(font=("Arial", 8))

read_data(main_label)

root.mainloop()
