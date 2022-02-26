CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb `pkg-config --cflags gtkmm-3.0`

BIN		:= bin
SRC		:= src
MKDIR_SHELL := $(shell if [ ! -d $(BIN) ]; then mkdir -p $(BIN); fi)
LIBRARIES	:= `pkg-config --libs gtkmm-3.0`

# 选择需要运行的程序
EXECUTABLE	:= checksum


all: $(BIN)/checksum $(BIN)/encoding $(BIN)/filesystem $(BIN)/iniFile $(BIN)/loadDLL $(BIN)/path $(BIN)/time $(BIN)/regex
# all: $(BIN)/$(EXECUTABLE)

run: clean all
# run: all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/%: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
