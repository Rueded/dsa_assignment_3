# Makefile for Logistics Hub Management System
# Usage: make        (to compile)
#        make run    (to compile and run)
#        make clean  (to remove compiled files)

CXX      = g++
CXXFLAGS = -Wall -std=c++11
TARGET   = logistics

ifeq ($(OS),Windows_NT)
    TARGET_BIN = $(TARGET).exe
    RM         = del /Q /F
    RUN_CMD    = $(TARGET_BIN)
else
    TARGET_BIN = $(TARGET)
    RM         = rm -f
    RUN_CMD    = ./$(TARGET)
endif

SRCS     = main.cpp intake.cpp priority.cpp capacity.cpp search.cpp fileio.cpp menu.cpp

all: $(TARGET_BIN)

$(TARGET_BIN): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET_BIN)

run: all
	$(RUN_CMD)

clean:
	-$(RM) $(TARGET_BIN)
