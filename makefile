# makefile for 
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
all:
	$(CC) -std=gnu++11 -g -Wall -o generate generateRandomParticles.cpp
	$(CC) -g -Wall -o speedtest_struct speedtest_struct.cpp
	$(CC) -g -Wall -o speedtest_array speedtest_array.cpp

clean:
	rm generate
	rm speedtest_array
	rm speedtest_struct