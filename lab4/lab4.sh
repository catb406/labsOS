#!/bin/bash
g++	-c	prog2.cpp
g++	-o	prog2	prog2.o		-lpthread
g++	-c	prog2_2.cpp
g++	-o	prog2_2	prog2_2.o		-lpthread
g++	-c	prog2_3.cpp
g++	-o	prog2_3	prog2_3.o		-lpthread
g++	-c	prog1.cpp
g++	-o	prog1	prog1.o		-lpthread