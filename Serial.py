
import serial 

TIVA = serial.Serial("/dev/ttyACM1",9600)

while True:
    char = TIVA.readline()
    START = str(char[])&(1<<4)
    A =     str(char[])&(1<<3)
    B =     str(char[])&(1<<2)
    X =     str(char[])&(1<<1)
    Y =     str(char[])&(1<<0)
    print("A:"+A+" B:"+B+" X:"+X+" Y:"+Y+" Start:"+START)
    
