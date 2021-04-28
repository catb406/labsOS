#!/bin/bash
g++ -c writer.cpp
g++ -o writer writer.o -lpthread
g++ -c reader.cpp
g++ -o reader reader.o -lpthread
