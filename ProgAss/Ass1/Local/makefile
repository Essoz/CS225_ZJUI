# Definition of normal variables
CC := g++
LD := g++
SOURCES := $(wildcard *.cpp)
OBJECTIVES := $(patsubst %cpp, %o, $(SOURCES))
TARGET := MP1 # PUT YOUR INTENDED NAME HERE

# Link ALL dependency files to carry out ALL target files
$(TARGET): $(OBJECTIVES)
	$(LD) -o $@ $^

# Compile ALL objective files EACH BY EACH
%.o:%.c
	$(CC) -c $^

# Definition of phony targets
.PHONY: all clear
all: $(TARGET)
clear:
	rm -f $(OBJECTIVES) $(TARGET)