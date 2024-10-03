#! /usr/bin/python3

import subprocess, os, time, sys

TEST_DIR = "./working/"
DIFF_DIR = "./diffs/"
TMP_DIR = "./temp/"
PIPEX = "./pipex"

def run_actual (cmd, testname, is_mine = False):
	with open(TEST_DIR+testname+("_mine" if is_mine else ""), "w+") as f:
		p = subprocess.Popen(cmd, shell=True, stdout=f, stderr=f)

def run_test(TESTNAME, commands = ["cat", "cat"], inputfile = True , inputtext = "Some basic text that will be in a file in temp lol", outputfile = True):

	inputfilename = TMP_DIR+TESTNAME+"_pre"
	if inputfile == True:
		with open(TMP_DIR+TESTNAME+"_pre", "w+") as file:
			file.write(inputtext)
	elif type(inputfile) == str:
		inputfilename = inputfile
	
	normaloutput = TMP_DIR+TESTNAME+'_post'
	myoutput = TMP_DIR+TESTNAME+'_mine_post'
	if outputfile == True:
		os.system(f"touch {normaloutput}")
		time.sleep(0.5)
		os.system(f"touch {myoutput}")
		time.sleep(0.5)
	elif type(outputfile) == str:
		normaloutput = outputfile + '_post'
		myoutput = outputfile + '_mine_post'
	
	inputfilename = os.path.realpath(inputfilename)
	myoutput = os.path.realpath(myoutput)
	normaloutput = os.path.realpath(normaloutput)
	print(f"< {inputfilename} {' | '.join(commands)} > {normaloutput}")
	run_actual(f"< {inputfilename} {' | '.join(commands)} > {normaloutput}", TESTNAME, False)
	time.sleep(0.5)
	commands = list(map(lambda x: '"'+x+'"' , commands))
	print(f"{PIPEX} {inputfilename} {' '.join(commands)} {myoutput}")
	run_actual(f"{PIPEX} {inputfilename} {' '.join(commands)} {myoutput}", TESTNAME, True)
	time.sleep(0.5)
	with open(DIFF_DIR+TESTNAME, 'w+') as f:
		subprocess.run(f"diff -s {normaloutput} {myoutput}", shell=True, stdout=f)
		time.sleep(0.5)
		f.write("\n")
		subprocess.run(f"diff -s {TEST_DIR+TESTNAME+''} {TEST_DIR+TESTNAME+'_mine'}", shell=True, stdout=f)
		time.sleep(0.5)


def main (x = -1):
	p = [
		lambda: run_test("cat_cat", commands=["cat", "cat"], inputfile=True, outputfile=True),
		lambda: run_test("wc-l_cat", commands=["wc -l", "cat"], inputfile=True, outputfile=True, inputtext="\n"*10),
		lambda: run_test("upper_lower", commands=["./useful/upper", "./useful/lower"], inputfile=True, outputfile=True),
		lambda: run_test("cannot_read", commands=["./useful/upper", "./useful/lower"], inputfile="./static/no_permissions", outputfile=True),
		lambda: run_test("cannot_execute", commands=["./useful/upper", "./static/no_permissions"], inputfile=True, outputfile=True),
		lambda: run_test("cannot_execute_too", commands=["./static/no_permissions", "cat"], inputfile=True, outputfile=True),
		lambda: run_test("cannot_execute_any", commands=["./static/no_permissions", "./static/no_permissions"], inputfile=True, outputfile=True)
	]
	if (x > 0):
		p[x]()
	else:
		[t() for t in p]

	

if __name__ == "__main__":
	if (len(sys.argv) > 1 and sys.argv[1] == "fclean"):
		os.system(f"rm -f {TEST_DIR}/*")
		os.system(f"rm -f {TMP_DIR}/*")
		os.system(f"rm -f {DIFF_DIR}/*")
	elif (len(sys.argv) > 1 and sys.argv[1].isdecimal):
		main(int(sys.argv[1]))
	else:
		main()