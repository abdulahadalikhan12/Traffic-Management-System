CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = src/main.cpp src/Graph.cpp src/Queue.cpp src/Vehicle.cpp src/TrafficMonitor.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = traffic_simulator

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for compiling .cpp files into .o files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)
