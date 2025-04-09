# Compiler to use
CXX = g++
# Define the moc tool with the full path on your system
MOC = /usr/lib64/qt6/libexec/moc

# Compiler flags for C++17 and necessary Qt6 include directories
CXXFLAGS = -std=c++17 -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtNetwork

# Linker flags: Link against the Qt6Core and Qt6Network libraries
LDFLAGS = -lQt6Core -lQt6Network

# Source files (main.cpp and ApiClient.cpp)
SOURCES = main.cpp ApiClient.cpp

# Object files produced from your sources and the moc-generated file
OBJECTS = main.o ApiClient.o moc_ApiClient.o

# Name of the final executable
TARGET = MyApp

# Default target: Build the final executable
all: $(TARGET)

# Link object files to produce the final executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) main.o ApiClient.o moc_ApiClient.o $(LDFLAGS)

# Rule to compile main.cpp into main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile ApiClient.cpp into ApiClient.o
ApiClient.o: ApiClient.cpp
	$(CXX) $(CXXFLAGS) -c ApiClient.cpp -o ApiClient.o

# Generate moc_ApiClient.cpp from ApiClient.h
moc_ApiClient.cpp: ApiClient.h
	$(MOC) -o moc_ApiClient.cpp ApiClient.h

# Compile moc_ApiClient.cpp into moc_ApiClient.o
moc_ApiClient.o: moc_ApiClient.cpp
	$(CXX) $(CXXFLAGS) -c moc_ApiClient.cpp -o moc_ApiClient.o

# Clean: Remove the executable, object files, and the generated moc file
clean:
	rm -f $(TARGET) main.o ApiClient.o moc_ApiClient.o moc_ApiClient.cpp