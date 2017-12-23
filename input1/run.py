import sys, os
os.system("g++ decompress.cpp")
os.system("a.exe > result.temp")
if open("result.temp", "r").read() != open("input1.txt", "r").read():
    print("Error!")
else:
    print("OK!")
    os.system("del result.temp")