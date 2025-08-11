CXX = clang++
CXXFLAGS = -std=c++2b -Wall

TARGET = bin/Iowa

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=bin/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 

bin/%.o: src/%.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

test:
	make
	./bin/Iowa tests/test_looping.ia

clean:
	rm -rf bin

	