CC=gcc
CFLAGS="-Wall"

OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
INC_DIR = ./include

debug:clean
	$(CC) $(CFLAGS) -g -o $(BIN_DIR)kruskalmstp main.c
stable:clean
	$(CC) $(CFLAGS) -o $(BIN_DIR)kruskalmstp main.c
clean:
	rm -vfr *~ kruskalmstp
