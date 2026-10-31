CXX = clang++
CXXFLAGS = -std=c++2b -Wall

# Find LLVM on PATH or in Homebrew's default installation locations.
LLVM_CONFIG ?= $(firstword $(shell command -v llvm-config 2>/dev/null) $(wildcard /opt/homebrew/opt/llvm/bin/llvm-config /usr/local/opt/llvm/bin/llvm-config))
CPPFLAGS += $(shell $(LLVM_CONFIG) --cppflags)
LDFLAGS += $(shell $(LLVM_CONFIG) --ldflags)
LDLIBS += $(shell $(LLVM_CONFIG) --libs core --system-libs)

TARGET = bin/Iowa

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=bin/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

bin/%.o: src/%.cpp
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

test:
	make
	./bin/Iowa tests/test_function_call.ia

clean:
	rm -rf bin

	
