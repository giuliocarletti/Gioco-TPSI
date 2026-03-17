# 1. Rilevamento OS
ifeq ($(OS),Windows_NT)
    # Configurazione Windows
    LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
    RM = del /q
    MKDIR = if not exist build mkdir build
    BIN = build/raylib-test.exe
else
    # Configurazione Linux
    LDFLAGS = -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    RM = rm -rf
    MKDIR = mkdir -p build
    BIN = build/raylib-test
endif

CC = gcc
CFLAGS = -Iinclude -Wall -std=c99
SRC = $(wildcard src/*.c)

all:
	@$(MKDIR)
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) build/*