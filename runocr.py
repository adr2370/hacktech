import os
import sys
import subprocess
import shlex
command = "./TessOp " + sys.argv[1]
tmp = os.popen(command).read()
os.system("cat " + tmp + " > blablah.txt")
print tmp