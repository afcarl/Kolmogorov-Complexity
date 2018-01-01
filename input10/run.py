import sys, os, time
os.system("g++ -O2 10.cpp")
os.system("a.exe > result.temp")
os.system("del a.exe")
compressed_size = len(open("10.cpp", "rb").read())
print("Compressed size = {0} bytes".format(compressed_size))
if open("result.temp", "r").read() != open("input10.txt", "r").read():
    print("Error!")
else:
    print("OK!")
    os.system("git add .")
    os.system('git commit -m "Shrinking file 9 {0}"'.format(compressed_size))