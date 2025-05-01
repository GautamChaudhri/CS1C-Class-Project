

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -O0

# Target executable name
TARGET = vector-driver

# Source files
SRCS = main.cpp

# Object files (automatically derived)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

tar:
	tar cvf $(TARGET).tar *.cpp *.rpt *.scr