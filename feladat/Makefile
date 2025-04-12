CC=gcc
CFLAGS=-Iinclude
SRC=$(wildcard src/*.c)
OUT=run.exe
LIBS=-lmingw32 -lSDL2main -lSDL2_image -lSDL2 -lopengl32

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)
