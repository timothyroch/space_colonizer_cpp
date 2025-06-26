CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp src/Game.cpp src/Grid.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = space_colonizer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
