# Skrypt, dla wersji (Mint XFCE)
import serial
import os

port = "/dev/ttyACM0" 
baud = 115200

try:
    os.system(f"sudo chmod 666 {port}")
    ser = serial.Serial(port, baud, timeout=1)
    print(f">>> SŁUCHAM NA {port} (Mint XFCE) <<<")

    while True:
        if ser.in_waiting > 0:
            cmd = ser.readline().decode('utf-8', errors='ignore').strip()
            if cmd:
                print(f"Odebrano: {cmd}")
                cmd_l = cmd.lower()
                
                if "offmatrix" in cmd_l:
                    os.system("pkill cmatrix")
                elif "matrix" in cmd_l:
                    os.system("xfce4-terminal --fullscreen -e cmatrix &")
                elif "lock" in cmd_l:
                    os.system("xflock4")

except Exception as e:
    print(f"Błąd: {e}")
