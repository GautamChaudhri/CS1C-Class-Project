CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -Icrow/include -Iasio/asio/include -pthread -DCROW_USE_STANDALONE_ASIO

TARGET = webservice
SRC    = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o