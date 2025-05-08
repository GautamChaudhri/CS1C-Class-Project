# Compiler to use
CXX = g++
# Define the moc tool with the full path on your system
MOC = /usr/lib64/qt6/libexec/moc

# Compiler flags for C++17, debug symbols, and necessary Qt6 include directories
CXXFLAGS = -std=c++17 -g -O0 \
  -I/usr/include/qt6 \
  -I/usr/include/qt6/QtCore \
  -I/usr/include/qt6/QtNetwork \
  -I/usr/include/qt6/QtGui \
  -I/usr/include/qt6/QtWidgets

# Linker flags: Link against the necessary Qt6 libraries
LDFLAGS = -lQt6Core -lQt6Network -lQt6Gui -lQt6Widgets

# Source files for the test harness
SOURCES = \
    main.cpp \
    SelSort.cpp \
    RenderAreaManager.cpp \
    ../src/backend/Parser.cpp

# Paths to object implementations in the project
OBJ_DIR = ../src/objects
OBJECTS = \
    main.o \
    SelSort.o \
    RenderAreaManager.o \
    Parser.o \
    UserAccount.o \
    Testimonial.o \
    moc_RenderAreaManager.o \
    $(OBJ_DIR)/shape.o \
    $(OBJ_DIR)/line.o \
    $(OBJ_DIR)/polyline.o \
    $(OBJ_DIR)/polygon.o \
    $(OBJ_DIR)/rectangle.o \
    $(OBJ_DIR)/square.o \
    $(OBJ_DIR)/ellipse.o \
    $(OBJ_DIR)/circle.o \
    $(OBJ_DIR)/text.o

# Name of the final executable
TARGET = hwgp02_tests

.PHONY: all clean

all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Compile harness sources
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

SelSort.o: SelSort.cpp
	$(CXX) $(CXXFLAGS) -c SelSort.cpp -o SelSort.o


RenderAreaManager.o: RenderAreaManager.cpp RenderAreaManager.h
	$(CXX) $(CXXFLAGS) -c RenderAreaManager.cpp -o RenderAreaManager.o

Parser.o: ../src/backend/Parser.cpp ../src/backend/Parser.h
	$(CXX) $(CXXFLAGS) -c ../src/backend/Parser.cpp -o Parser.o

# Compile UserAccount.cpp for Parser references
UserAccount.o: ../src/backend/UserAccount.cpp ../src/backend/UserAccount.h
	$(CXX) $(CXXFLAGS) -c ../src/backend/UserAccount.cpp -o UserAccount.o

# Compile Testimonial.cpp for Parser references
Testimonial.o: ../src/backend/Testimonial.cpp ../src/backend/Testimonial.h
	$(CXX) $(CXXFLAGS) -c ../src/backend/Testimonial.cpp -o Testimonial.o

# Generate moc and compile for Qt meta-object processing
moc_RenderAreaManager.cpp: RenderAreaManager.h
	$(MOC) -o moc_RenderAreaManager.cpp RenderAreaManager.h

moc_RenderAreaManager.o: moc_RenderAreaManager.cpp
	$(CXX) $(CXXFLAGS) -c moc_RenderAreaManager.cpp -o moc_RenderAreaManager.o

# Pattern rule for compiling object implementations
$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) moc_*.cpp $(TARGET) UserAccount.o Testimonial.o