#Makefile for building demo applications
# by karto1000

#edit this file to compile C files into their own programs
TARGETS = test_main

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c++11 -Werror -lgtest -lpthread
#g++ -lgtest -lpthread -std=c++11 -o main
all: clean $(TARGETS)
$(TARGETS):
	$(CC_CPP) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f $(TARGETS)
