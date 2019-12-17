import serial
import os
import time
A=[]
from hexdump import hexdump
alh="0123456789ABCDEF"
for i in range (len(alh)):
    for j in range(len(alh)):
        os.system("python forcecrc32.py test.bin 4 000000"+alh[i]+alh[j])
        with open("test.bin", "rb") as f:
            hexdump(f.read(100))
ser = serial.Serial('COM7', 115200)  # open serial port

print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")
print(ser.readline().decode("ascii"), end="")

while True:
    print(ser.readline().decode("ascii"), end="")
    ser.write(b"x\31\x32\x33\x34\x35\x36\x37\x38")
    print(ser.readline().decode("ascii"), end="")
    print(ser.readline().decode("ascii"), end="")
