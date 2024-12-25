CXX = clang++
CXXFLAGS = -std=c++11 -Wall

TARGET = bin/Iowa

# Find all .cpp files in the src directory and generate corresponding .o files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=bin/%.o)

# Default rule: build the target
all: $(TARGET)

# Rule for linking the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 

# Generic rule for compiling all .cpp files into .o files
bin/%.o: src/%.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove the target and object files

# Mark these as phony targets to avoid conflicts with files named "all" or "clean"
.PHONY: all clean