# Compiler settings
CXX = g++
CXXFLAGS = -O3 -std=c++17
DEBUG_FLAGS=-DVERBOSE
# Source files and the executable name
SOURCES = main.cpp bfs.cpp IdAstar.cpp iterativeDeepening.cpp HeuristicSearch.cpp Heuristic.cpp Memcontrol.cpp tilepuzzle.cpp
TARGET = main


# Default target
all: $(TARGET)


# Debug rule
verbose: CXXFLAGS += $(DEBUG_FLAGS)
verbose: clean all


# Rule to link the program
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Rule for cleaning up
clean:
	rm -f $(TARGET)
