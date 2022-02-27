CC=g++
SRC=src
EXECUTABLE=main.exe

all: Main

Main:
	$(CC) -o $(EXECUTABLE) $(SRC)/Main.cpp $(SRC)/Chip8.cpp