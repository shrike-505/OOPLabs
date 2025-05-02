# Compiler and flags
CC = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = 

# Source files and targets
SRCS = Diary.cpp pdadd.cpp pdlist.cpp pdshow.cpp pdremove.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = pdadd pdlist pdshow pdremove

# Default target
all: $(TARGETS)

# Main targets
Diary.o: Diary.cpp Diary.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

pdadd.o: pdadd.cpp Diary.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

pdlist.o: pdlist.cpp Diary.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

pdshow.o: pdshow.cpp Diary.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

pdremove.o: pdremove.cpp Diary.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# Executable linking
pdadd: pdadd.o Diary.o
	$(CC) $(LDFLAGS) $^ -o $@

pdlist: pdlist.o Diary.o
	$(CC) $(LDFLAGS) $^ -o $@

pdshow: pdshow.o Diary.o
	$(CC) $(LDFLAGS) $^ -o $@

pdremove: pdremove.o Diary.o
	$(CC) $(LDFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f $(TARGETS) *.o diary.txt

# Phony targets
.PHONY: all clean