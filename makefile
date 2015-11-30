CC = g++
CC_FLAG = -g -Wall -I
INCLUDE = include
SRC = src/*.cpp
TARGET = bin/logsys
TEMPFILE = source/
TESTFILE = source/test.txt
OUTFILE = source/result.txt

$(TARGET):$(SRC)
	$(CC) $(CC_FLAG) $(INCLUDE) $(SRC) -o $(TARGET)

clean:				
	rm $(TARGET)
test:
	@./$(TARGET) $(TESTFILE) $(OUTFILE)
debug:
	@$(DEBUG) ./$(TARGET) $(TESTFILE) $(OUTFILE)

.PHONY:test debug
