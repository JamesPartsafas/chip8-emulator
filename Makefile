CC=g++
SRC=src
EXECUTABLE=main.exe
LIBRARY=libs

all: Main

Main:
	$(CC) $(SRC)/Main.cpp $(SRC)/Chip8.cpp $(SRC)/Renderer.cpp \
	-I$(LIBRARY)/SDL/include -L$(LIBRARY)/SDL/lib \
	-w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 \
	-o $(EXECUTABLE)
