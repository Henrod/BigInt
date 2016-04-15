CXX		= g++
CXXFLAGS 	= -std=c++11 -Wall -Wextra

CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = BigInt

all:
	$(CXX) $(CXXFLAGS) $(CPP_FILES) -o $(OBJ_FILES)

clean:
	rm -f $(OBJ_FILES)
