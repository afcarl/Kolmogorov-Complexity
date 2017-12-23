import sys, os, time
os.system("g++ -O2 compress.cpp")
os.system("a.exe")
compressed_size = len(open("c", "rb").read())
print("Compressed size = {0} bytes".format(compressed_size))
if len(sys.argv) < 2:
    os.system("g++ decompress.cpp")
    start = time.time()
    os.system("a.exe > result.temp")
    print("Decompression used time {0}s".format(time.time() - start))
    if open("result.temp", "r").read() != open("input1.txt", "r").read():
        print("Error!")
    else:
        print("OK!")
        os.system("del result.temp")