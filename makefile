CC = g++
CC_FLAG = -g -Wall -lpthread -I
INCLUDE = include
SRC = src/*.cpp
TARGET = bin/logsys
TEMPFILE = log/*
TESTFILE = source/test.txt
OUTFILE = source/result.txt

$(TARGET):$(SRC)
	$(CC) $(CC_FLAG) $(INCLUDE) $(SRC) -o $(TARGET)

clean:				
	rm $(TARGET) $(TEMPFILE)
test:
	@./$(TARGET) $(TESTFILE) $(OUTFILE)
debug:
	@$(DEBUG) ./$(TARGET) $(TESTFILE) $(OUTFILE)

.PHONY:test debug
