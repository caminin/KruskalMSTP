TARGET = prog.exe

SRCS = main.c\
		 edge.c\
		 vertice.c\
		 latex.c\
		 kruskal.c\
		 file.c\

OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
INC_DIR = ./include

DEP_DIRS =

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

SYS_LIBS = 

INCLUDES = -I$(INC_DIR) $(addprefix -I, $(DEP_DIRS))
LDLIBS = $(addprefix -l, $(SYS_LIBS))
LDFLAGS = -W -Wall
CXX = gcc

.PHONY: all clean fclean

debug: CFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: all

release: CFLAGS += -O2
release: all

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(TARGET)
	
rodolphe: CFLAGS += -DRODOLPHE
rodolphe: clean debug

florian: CFLAGS += -DFLORIAN
florian: clean debug

