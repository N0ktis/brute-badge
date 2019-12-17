import serial
import os
import time
A=[]
from hexdump import hexdump
for i in range(255):
    os.system("python forcecrc32.py test.bin 4 000000" + "{0:02X}".format(i))
    with open("test.bin", "rb") as f:
        A.append(f.read(8))
ser = serial.Serial('COM7', 115200)  # open serial port

print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")

while True:
    print(ser.readline().decode("ascii"), end="")
    ser.write(A[0])
    print(ser.readline().decode("ascii"), end="")
    print(ser.readline().decode("ascii"), end="")
