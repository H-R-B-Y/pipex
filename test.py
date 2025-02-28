# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:02:10 by hbreeze           #+#    #+#              #
#    Updated: 2025/02/23 18:02:34 by hbreeze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import time, os
import subprocess

def launch_test(input_file, cmd_arr, testname):
	# Prep OS system call
	cmd = f'< "{input_file}" ' + ' | '.join([''+c+'' for c in cmd_arr]) + f' > "{testname}_bash"'
	print(f"Running: $ {cmd}")
	pipe1 = os.popen(cmd)
	return_code = pipe1.close()
	print(f"Returned {return_code if return_code else 0}")
	# Prep PIPEX call
	cmd2 = f'./pipex {input_file} ' + ' '.join(['"'+c+'"' for c in cmd_arr]) + f' {testname}_pipex'
	print(f"Running: $ {cmd2}")
	pipe2 = os.popen(cmd2)
	return_code2 = pipe2.close()
	print(f"Returned {return_code2 if return_code2 else 0}")
	time.sleep(1)
	print("Checking Diffs: ", end="")
	result = subprocess.run(["diff", f'{testname}_pipex', f"{testname}_bash"], capture_output=True, text=True)

	if result.returncode == 0:
		print("Files are identical")
		os.popen(f"rm -rf {testname}_pipex {testname}_bash")
	elif result.returncode == 1:
		print("Files are different")
	else:
		print(f"Error running diff: {result.stderr}")


def launch_append(input_file, cmd_arr, testname, basetext):
	# Prep OS system call
	cmd = f'< "{input_file}" ' + ' | '.join([''+c+'' for c in cmd_arr]) + f' >> "{testname}_bash"'
	os.popen(f"echo \"{basetext}\" > \"{testname}_bash\"")
	print(f"Running: $ {cmd}")
	pipe1 = os.popen(cmd)
	return_code = pipe1.close()
	print(f"Returned {return_code if return_code else 0}")
	# Prep PIPEX call
	cmd2 = f'./pipex append_ {input_file} ' + ' '.join(['"'+c+'"' for c in cmd_arr]) + f' {testname}_pipex'
	os.popen(f"echo \"{basetext}\" > \"{testname}_pipex\"")
	print(f"Running: $ {cmd2}")
	pipe2 = os.popen(cmd2)
	return_code2 = pipe2.close()
	print(f"Returned {return_code2 if return_code2 else 0}")
	time.sleep(1)
	print("Checking Diffs: ", end="")
	result = subprocess.run(["diff", f'{testname}_pipex', f"{testname}_bash"], capture_output=True, text=True)

	if result.returncode == 0:
		print("Files are identical")
		os.popen(f"rm -rf {testname}_pipex {testname}_bash")
	elif result.returncode == 1:
		print("Files are different")
	else:
		print(f"Error running diff: {result.stderr}")


def launch_heredoc(input_file, cmd_arr, testname, heredoc, inputtext):
	cmd_arr_fix = ' | '.join(cmd_arr[1::])
	cmd = \
f"""{cmd_arr[0]} <<{heredoc} | {cmd_arr_fix} > {testname}_bash
{inputtext}
{heredoc}"""
	print(f"Running: $ {cmd}")
	result = subprocess.Popen(cmd, shell=True, text=True, executable="/bin/bash")
	print(f"Returned: {result.returncode}")
	
	cmd_arr_fix = ' '.join(['"'+c+'"' for c in cmd_arr])
	cmd2 = \
f"""echo "{inputtext + '\n' + heredoc}" | ./pipex here_doc {heredoc} {cmd_arr_fix} {testname}_pipex"""
	print(f"Running: $ {cmd2}")
	result = subprocess.Popen(cmd2, shell=True, text=True, executable="/bin/bash")
	print(f"Returned: {result.returncode}")
	time.sleep(1)
	print("Checking Diffs: ", end="")
	result = subprocess.run(["diff", f'{testname}_pipex', f"{testname}_bash"], capture_output=True, text=True)

	if result.returncode == 0:
		print("Files are identical")
		os.popen(f"rm -rf {testname}_pipex {testname}_bash")
	elif result.returncode == 1:
		print("Files are different")
	else:
		print(f"Error running diff: {result.stderr}")


def launch_heredoc_append(input_file, cmd_arr, testname, basetext, heredoc, inputtext):
	cmd_arr_fix = ' | '.join(cmd_arr[1::])
	cmd = \
f"""{cmd_arr[0]} <<{heredoc} | {cmd_arr_fix} > {testname}_bash
{inputtext}
{heredoc}"""
	os.popen(f"echo \"{basetext}\" > \"{testname}_bash\"")
	print(f"Running: $ {cmd}")
	result = subprocess.Popen(cmd, shell=True, text=True, executable="/bin/bash")
	print(f"Returned: {result.returncode}")
	
	cmd_arr_fix = ' '.join(['"'+c+'"' for c in cmd_arr])
	cmd2 = \
f"""echo "{inputtext + '\n' + heredoc}" | ./pipex here_doc {heredoc} {cmd_arr_fix} {testname}_pipex"""
	os.popen(f"echo \"{basetext}\" > \"{testname}_bash\"")
	print(f"Running: $ {cmd2}")
	result = subprocess.Popen(cmd2, shell=True, text=True, executable="/bin/bash")
	print(f"Returned: {result.returncode}")
	time.sleep(1)
	print("Checking Diffs: ", end="")
	result = subprocess.run(["diff", f'{testname}_pipex', f"{testname}_bash"], capture_output=True, text=True)

	if result.returncode == 0:
		print("Files are identical")
		os.popen(f"rm -rf {testname}_pipex {testname}_bash")
	elif result.returncode == 1:
		print("Files are different")
	else:
		print(f"Error running diff: {result.stderr}")

def launch_valgrind(input_file, cmd_arr, testname):
	fix_cmd = ' '.join(['"'+c+'"' for c in cmd_arr])
	cmd = f"valgrind --track-fds=yes ./pipex {input_file} {fix_cmd} {testname}_valgrind"
	print(f"Running: $ {cmd}")
	result = subprocess.run(cmd, shell=True, text=True, executable="/bin/bash", capture_output=True)
	print(f"Returned: {result.returncode}")
	print(f"Output:\n{result.stdout.strip()}")


if __name__ == "__main__":
	launch_test("test.py", ["cat", "wc -l", "cat", "cat"], "simple")
	launch_append("test.py", ["cat", "wc -l", "cat", "cat"], "append", "Text already in file\n")
	launch_heredoc("test.py", ["cat", "wc -l", "cat", "cat"], "heredoc", "EOF", "YOU ARE SILLY\nSILLY\nSILLY CODE!")
	launch_heredoc_append("test.py", ["cat", "wc -l", "cat", "cat"], "heredoc_append", "Text already in file", "EOF", "YOU ARE SILLY\nSILLY\nSILLY CODE!")
