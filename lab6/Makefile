CXX := g++
CXXFLAGS := -Wall -Wextra
TARGET := main
SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
HEADERS := vector.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean