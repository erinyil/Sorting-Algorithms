#
# Makefile for Homework 5
#
# Homework 5 (fall 2019)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 


sorter: sorter.o sortAlgs.o 
	${CXX} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf sorter *.o *.dSYM

provide:
	provide comp15 hw5 sorter.cpp sortAlgs.h sortAlgs.cpp \
	        README Makefile
