import sys, os, time
os.system("g++ compress.cpp")
os.system("a.exe")
os.system("g++ decompress.cpp")
start = time.time()
os.system("a.exe > result.temp")
print("Decompression used time {0}s".format(time.time() - start))
if open("result.temp", "r").read() != open("input3.txt", "r").read():
    print("Error!")
else:
    print("OK!")
    os.system("del result.temp")