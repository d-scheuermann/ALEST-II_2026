# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: app_sorts 

app_sorts = app_sorts
app_sorts_src = app_sorts.cpp
app_sorts_obj = $(app_sorts_src:.cpp=.o)

$(app_sorts): $(app_sorts_obj)
	g++ $(CPPFLAGS) $(app_sorts_obj) -o $@

# Clean up build files
clean:
	rm -f app_sorts app_sorts.o

# Phony targets
.PHONY: all clean
