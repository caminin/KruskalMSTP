TARGET = prog.exe

SRCS = main.cpp\

OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
INC_DIR = ./include

DEP_DIRS =

OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

SYS_LIBS = 

INCLUDES = -I$(INC_DIR) $(addprefix -I, $(DEP_DIRS))
CXXFLAGS = -std=c++11 -W -Wall $(INCLUDES)
LDLIBS = $(addprefix -l, $(SYS_LIBS))
LDFLAGS = -W -Wall
CXX = g++

.PHONY: all clean fclean

debug: CPPFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: all

release: CPPFLAGS += -O2
release: all

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

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

