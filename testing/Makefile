# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -pthread

# GoogleTest directories
# for mac
GTEST_DIR = /opt/homebrew/opt/googletest
# for ubuntu define!
GTEST_LIBS = -lgtest -lgtest_main

# Paths to include and library directories
INCLUDE = -I$(GTEST_DIR)/include -I./testing
LIBS = -L$(GTEST_DIR)/lib

# Target executable
TARGET = irc_test

# Source files (all files are inside the 'testing' folder)
SRC = ./IrcClient.cpp ./test_irc_client.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build the target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(INCLUDE) $(LIBS) $(GTEST_LIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
