CXX = g++
CXXFLAGS = -Wall -g `pkg-config --cflags ddjvuapi`
LDFLAGS = `pkg-config --libs ddjvuapi`

TARGET = has_composite_shapes
SRC = has_composite_shapes.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o