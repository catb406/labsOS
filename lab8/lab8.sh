#!/bin/bash
g++ -c writer.cpp
g++ -c reader.cpp
g++ -o writer writer.o -lpthread -lrt
g++ -o reader reader.o -lpthread -lrt
sudo setcap cap_sys_resource=eip writer
sudo setcap cap_sys_resource=eip reader
