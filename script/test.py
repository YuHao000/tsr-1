#!/usr/bin/env python
# -*- coding:utf-8 -*-
# Author: liyi_whu@163.com

import os
import sys

def execTester(inPath, outPath, opt):
	prjDir = os.path.split(sys.path[0])[0]
	cmd = prjDir + "\\cvter.exe " + opt + " " + inPath + " " + outPath
	out = os.popen(cmd).read()
	print(out)


if __name__ == '__main__':
	if len(sys.argv) != 4:
		print("Invalid Input!")
		exit(1)
		
	for root, dirs, files in os.walk(sys.argv[2]):
		for file in files:
			if file[-4:] != ".jpg": continue
			inPath = os.path.join(root, file)
			outPath = os.path.join(sys.argv[3], file + "." + sys.argv[1] + ".jpg")
			execTester(inPath, outPath, sys.argv[1])
		