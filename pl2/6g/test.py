# -*- coding: utf-8 -*-

#test program
#author: gyane
#date 2014/10/24


import subprocess
import os
import time
import random


##########つかいかた#########
#	1. パラメータを設定する
#		アセンブラソースの名前
#		比較するCのソーソの名前
#		試行を行う回数
#		乱数の数
#		アセンブラソースでincludeするファイル名 (てきとーでよい
#		Cでincludeするヘッダファイル名 (てきとーでよい
#
#	2. アセンブラソースとCソースにそれぞれinclude文を加える
#
#	3. 実行方法
#		 $python test.py
#
#	4. いえーい
#



#########ぱらめーた#######

#assembler sorce file name
asm_file = "kadai2.s"

#c sorce file name
c_file = "kadai2_c.c"

#loop count
loop = 1

#num of random numbers
rand_num = 10

#.def file name(asm)
# (write random numbers)
def_file = "rand.def"

#.h file name(c)
# (write random numbers)
include_file = "rand.h"





def generate_random_num():
	asm_str1 = "	section .data\n"
	asm_str2 = "data:	dd "
	asm_str3 = "ndata: equ ($-data1)/4\n"

	c_str1 = "int array[" + str(rand_num) + "] = {"

	random.seed()
	
	for i in range(rand_num):
		rand = random.randint(0, 0x7fffffff)
		asm_str2 = asm_str2 + str(rand)
		c_str1 = c_str1 + str(rand)
		if i != (rand_num-1):
			asm_str2 = asm_str2 + ","
			c_str1 = c_str1 + ","

	string = asm_str1 + asm_str2 + "\n" + asm_str3
	f = open(def_file, 'w')
	f.write(string)
	f.close()

	string = c_str1 + "};"
	f = open(include_file, 'w')
	f.write(string)
	f.close()



def measure_time_asm():
	time1 = time.time()
	os.system("./a.out")
	time2 = time.time()

	result = time2 - time1
	return result

def measure_time_c():
	time1 = time.time()
	os.system("./kadai2_c")
	time2 = time.time()

	result = time2 - time1
	return result



def average_execution_time():
	asm_total = 0
	c_total = 0

	#generate_random_num()
	
	#os.system("./nasmld " + asm_file)
	#os.system("gcc -o kadai2_c " + c_file)

	for i in range(loop):
		generate_random_num()
		os.system("./nasmld " + asm_file)
		#os.system("gcc -o kadai2_c " + c_file)
		asm_total = asm_total + measure_time_asm()
		#c_total = c_total + mesure_time_c()
	
	average_time = asm_total / loop
	print "asm_average: " + str(average_time)

	#average_time = c_total / loop
	#print "c_average:   " + str(average_time)

	#os.system("rm rand.def")
	os.system("rm rand.h")



if __name__ == '__main__':
	average_execution_time()
	print "program normally exited"
