# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executables
APPHEAP = appheap
APPSORTS = appsorts

# Source files
SOURCES_HEAP = appheap.cpp
SOURCES_SORT = appsorts.cpp

all: $(APPHEAP) $(APPSORTS)

$(APPHEAP): $(SOURCES_HEAP) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -o $(APPHEAP) $(SOURCES_HEAP)

$(APPSORTS): $(SOURCES_SORT) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -o $(APPSORTS) $(SOURCES_SORT)

# Clean up build files
clean:
	rm -f $(APPHEAP) $(APPSORTS)

# Phony targets
.PHONY: all clean
