import os
import sys
import time

if len(sys.argv) != 3 :
	exit(1)

cpp = sys.argv[1]
n = len(cpp)
typ = sys.argv[2]

if cpp.index(".cpp") != n - 4 :
	print("File Error")
	exit(1)
	
exe = cpp[0 : n - 4]
#print(exe)

if typ == "1" or typ == "2" :
	print("Compiling")
	re = os.system("g++ \"%s\" -o \"%s\" -Wall -m32 -Wl,--stack,1024000000" % (cpp, exe))
	if re != 0 :
		print("Compile Error")
		exit(re)
	else:
		print("------------------------\n")


if typ == "0" or typ == "1":
	start = time.clock()
	re = os.system("\"%s\"" % (exe))
	t = time.clock() - start
	print("\n\n------------------------")
	print("Process exited after %f seconds with return value %d " % (t, re))

if typ == "3" :
	inf = "%s.in" % (exe)
	ouf = "%s.out" % (exe)
	start = time.clock()
	re = os.system("\"%s\" < %s > %s" % (exe, inf, ouf))
	t = time.clock() - start
	print("\n\n------------------------")
	print("Process exited after %f seconds with return value %d " % (t, re))

exit(0)
