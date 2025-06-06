# Compiler to use
CXX = g++
# Define the moc tool with the full path on your system
MOC = /usr/lib64/qt6/libexec/moc

# Compiler flags for C++17, debug symbols, and necessary Qt6 include directories
CXXFLAGS = -std=c++17 -g -O0 \
  -I/usr/include/qt6 \
  -I/usr/include/qt6/QtCore \
  -I/usr/include/qt6/QtNetwork \
  -I/usr/include/qt6/QtWidgets \
  -I/usr/include/qt6/QtGui

# Linker flags: Link against the necessary Qt6 libraries
LDFLAGS = -lQt6Core -lQt6Network -lQt6Widgets -lQt6Gui

# Source files: main, ApiClient, Parser, and all shape implementations
SOURCES = main.cpp ApiClient.cpp Parser.cpp UserManager.cpp UserAccount.cpp \
    ../objects/shape.cpp \
    ../objects/line.cpp \
    ../objects/polyline.cpp \
    ../objects/polygon.cpp \
    ../objects/rectangle.cpp \
    ../objects/square.cpp \
    ../objects/ellipse.cpp \
    ../objects/circle.cpp \
    ../objects/text.cpp

# Object files: Convert .cpp file names to .o
OBJECTS = main.o ApiClient.o moc_ApiClient.o moc_UserManager.o \
    Parser.o UserManager.o UserAccount.o \
    ../objects/shape.o \
    ../objects/line.o \
    ../objects/polyline.o \
    ../objects/polygon.o \
    ../objects/rectangle.o \
    ../objects/square.o \
    ../objects/ellipse.o \
    ../objects/circle.o \
    ../objects/text.o

# Name of the final executable
TARGET = Backend

# Default target: Build the final executable
all: $(TARGET)

# Link all object files together to create the target executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Rule to compile main.cpp into main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile ApiClient.cpp into ApiClient.o
ApiClient.o: ApiClient.cpp
	$(CXX) $(CXXFLAGS) -c ApiClient.cpp -o ApiClient.o

# Rule to compile Parser.cpp into Parser.o
Parser.o: Parser.cpp Parser.h
	$(CXX) $(CXXFLAGS) -c Parser.cpp -o Parser.o

# Rule to compile UserManager.cpp into UserManager.o
UserManager.o: UserManager.cpp UserManager.h
	$(CXX) $(CXXFLAGS) -c UserManager.cpp -o UserManager.o

# Rule to compile UserAccount.cpp into UserAccount.o
UserAccount.o: UserAccount.cpp UserAccount.h
	$(CXX) $(CXXFLAGS) -c UserAccount.cpp -o UserAccount.o

# Generate moc_ApiClient.cpp from ApiClient.h
moc_ApiClient.cpp: ApiClient.h
	$(MOC) -o moc_ApiClient.cpp ApiClient.h

# Generate moc_UserManager.cpp from UserManager.h
moc_UserManager.cpp: UserManager.h
	$(MOC) -o moc_UserManager.cpp UserManager.h

# Compile moc_ApiClient.cpp into moc_ApiClient.o
moc_ApiClient.o: moc_ApiClient.cpp
	$(CXX) $(CXXFLAGS) -c moc_ApiClient.cpp -o moc_ApiClient.o

# Compile moc_UserManager.cpp into moc_UserManager.o
moc_UserManager.o: moc_UserManager.cpp
	$(CXX) $(CXXFLAGS) -c moc_UserManager.cpp -o moc_UserManager.o

# Pattern rule to compile any .cpp file in ../objects/ to its corresponding .o file
../objects/%.o: ../objects/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean: Remove the executable, object files, and generated moc files
clean:
	rm -f $(TARGET) main.o ApiClient.o Parser.o moc_ApiClient.o moc_UserManager.o \
	    ../objects/shape.o \
	    ../objects/line.o \
	    ../objects/polyline.o \
	    ../objects/polygon.o \
	    ../objects/rectangle.o \
	    ../objects/square.o \
	    ../objects/ellipse.o \
	    ../objects/circle.o \
	    ../objects/text.o \
	    moc_ApiClient.cpp moc_UserManager.cpp