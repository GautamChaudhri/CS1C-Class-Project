CXX = g++
#Include directories for Qt6 headers (adjust these if needed)
CXXFLAGS = -std=c++17 -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtNetwork
# Linker flags: Link against the Qt6Core and Qt6Network libraries
LDFLAGS = -lQt6Core -lQt6Network
SOURCES = main.cpp api_client.cpp
OBJECTS = main.o api_client.o
TARGET = MyApp

# Default target: Build the final executable
all: $(TARGET)

# Link object files to produce the final executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) main.o api_client.o $(LDFLAGS)

# Compile main.cpp to produce main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Compile api_client.cpp to produce api_client.o
api_client.o: api_client.cpp
	$(CXX) $(CXXFLAGS) -c api_client.cpp -o api_client.o

# Clean: Remove the executable and object files
clean:
	rm -f $(TARGET) main.o api_client.o