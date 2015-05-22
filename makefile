# makefile for 
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
all: myprog.c
  $(CC) -g -Wall -o generateRandomParticles generate.cpp
  $(CC) -g -Wall -o speedtest_struct speedtest_struct.cpp
  $(CC) -g -Wall -o speedtest_array speedtest_array.cpp

clean:
  $(RM) myprog