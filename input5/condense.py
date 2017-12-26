import sys
from functools import reduce
blank = " \t\r\n"
literal = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_"

def singlePass(line):
    ret = ""
    for i in line:
        if i not in blank:
            ret += i
        elif len(ret) != 0 and ret[-1] in literal:
            ret += i
    return ret

def condense(line):
    ret = singlePass(line)
    ret = singlePass(ret[::-1])[::-1]
    if ret.startswith('#'):
        ret += '\n'
    return ret

if __name__ == "__main__":
    src = open(sys.argv[1], "r").read()
    result = reduce(lambda x,y:x+y, (condense(line) for line in src.split('\n')))
    open(sys.argv[2], "w").write(result)