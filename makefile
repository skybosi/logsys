#
# Copyright (c) 2005, Wei Mingzhi. All rights reserved.
#
# Use, redistributions and modifications of this file is
# unrestricted provided the above copyright notice is
# preserved.
#
INCLUDE=include
SRC=src/log_main.cpp
LIB=lib
OBJ = Basethread.o confdata.o lmutex.o log_T.o filedata.o lthread.o parseconf.o	
HEADERS = Basethread.h confdata.h lmutex.h log_T.h filedata.h lthread.h Mdef.h parseconf.h	
LIB_SRC = $(INCLUDE)/*.cpp
CC = gcc
CXX = g++
TARGET = bin/logsys
#BASEFLAGS = -s -O3
DFLAGS=-fPIC -shared
LLDFLAGS=-lsys -lpthread
CC_FLAG = -g -Wall -I

all:initdir libsys.a ${TARGET}

libsys.a:$(OBJ)
	ar rcs libsys.a $^ 
	mv $^ libsys.a $(LIB)

#libsys.so:$(OBJ)
#	$(CXX) $(INCLUDE)/*.cpp $(DFLAGS) -o $@  
#	mv $^ libsys.so $(LIB)

$(OBJ):$(LIB_SRC)
	${CXX} -c $^

${TARGET}:$(SRC)
	${CXX} $< $(CC_FLAG) $(INCLUDE) -L $(LIB) ${LLDFLAGS} -o ${TARGET}

test:
	@./$(TARGET) 

initdir:
#	export LD_LIBRARY_PATH=./lib
	mkdir -p bin
	mkdir -p $(LIB)
	mkdir -p log
	
clean:
	rm -rf $(LIB)/* ${TARGET} lib bin log/*

.PHONY:test debug
