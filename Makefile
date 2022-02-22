CC=g++
SRC=src
EXE=main.exe

main: $(SRC)/Main.cpp
	$(CC) -o $(EXE) $(SRC)/Main.cpp