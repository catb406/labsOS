#!/bin/bash
g++	-c	lab3.cpp
g++	-c	lab3_2.cpp
g++	-c	lab3_3.cpp
g++	-o	lab3	lab3.o		-lpthread
g++	-o	lab3_2	lab3_2.o		-lpthread
g++	-o	lab3_3	lab3_3.o		-lpthread