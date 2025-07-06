CXX = g++
CXXFLAGS = -Iexternal -std=c++2a -pthread
LDLIBS = -ldjvulibre -pthread

TARGET = has_composite_shapes
SRC = has_composite_shapes.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(TARGET) *.o
