CXX := g++
CXXFLAGS := -std=c++17 -O3 -I.

DEFAULT_TARGET := custom
TARGET := allocator_test

SRCS := testallocator.cpp

ifeq ($(test), std)
    CXXFLAGS += -DUSE_STD_ALLOCATOR
    TARGET := allocator_test_std
else ifeq ($(test), usr)
    CXXFLAGS += 
    TARGET := allocator_test_usr
else
    TARGET := allocator_test
endif

.PHONY: all std usr clean

all: $(TARGET)

build_all: std usr

std:
	$(MAKE) test=std

usr:
	$(MAKE) test=usr

$(TARGET): $(SRCS) my_allocator.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f allocator_test allocator_test_std allocator_test_usr

run: $(TARGET)
	./$(TARGET)

compare: std usr
	@echo "=== std::allocator ==="
	@./allocator_test_std || true
	@echo "\n=== Custom Allocator ==="
	@./allocator_test_usr || true

.DEFAULT_GOAL := all