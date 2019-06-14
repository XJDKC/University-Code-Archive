import serial
import random
from time import sleep

ser = serial.Serial('/dev/ttyUSB1',115200,timeout=0.5)

while True:
    # .to_bytes(1, byteorder="little",signed=False)
    num = random.randint(0,9)
    print(num)
    ser.write("P".encode())
    sleep(5)
    ser.write(("%d"%num).encode())
    sleep(5)
    command = ser.readline()
    print("Debug:"+command.decode())
    sleep(5)