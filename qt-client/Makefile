CXX = g++
CXXFLAGS = -std=c++17 -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtNetwork
LDFLAGS = -lQt6Core -lQt6Network
SOURCES = main.cpp api_client.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = MyApp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)