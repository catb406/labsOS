#!/bin/bash
g++	-c	lab5_proc1_withblock.cpp
g++	-o	lab5_proc1_withblock	lab5_proc1_withblock.o		-lpthread
g++	-c	lab5_proc2_withblock.cpp
g++	-o	lab5_proc2_withblock	lab5_proc2_withblock.o		-lpthread
g++	-c	lab5_proc1_woblock.cpp
g++	-o	lab5_proc1_woblock	lab5_proc1_woblock.o		-lpthread
g++	-c	lab5_proc2_woblock.cpp
g++	-o	lab5_proc2_woblock	lab5_proc2_woblock.o		-lpthread