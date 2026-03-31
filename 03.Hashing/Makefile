# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
app_hashmap = app_hashmap

# Source files
app_hashmap_src = app_hashmap.cpp

INCLUDES = separatechaining_hashtable.h linearprobing_hashtable.h

# Build target
all: app_hashmap

app_hashmap: $(app_hashmap_src) $(INCLUDES)
	$(CXX) $(app_hashmap_src) $(CXXFLAGS) -o app_hashmap

# Clean up build files
clean:
	rm -f app_hashmap

# Phony targets
.PHONY: all clean
