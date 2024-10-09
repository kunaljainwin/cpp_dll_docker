# Compiler
CXX = g++

# Compiler flags for shared library
CXXFLAGS_LIB = -Wall -Wextra -fPIC -std=c++11

# Compiler flags for the target executable
CXXFLAGS = -Wall -Wextra -std=c++11

# Shared library target
LIBRARY = libmylibrary.so

# Target executable name
TARGET = app

# Source files for the executable
SRCS = main.cpp

# Object files generated from source files
OBJS = $(SRCS:.cpp=.o)

# Source and object directory for library
LIBRARY_SRC_DIR = ./src
LIBRARY_SRCS = $(wildcard $(LIBRARY_SRC_DIR)/*.cpp)
LIBRARY_OBJS = $(LIBRARY_SRCS:.cpp=.o)

# Default target (all)
all: $(LIBRARY) $(TARGET)

# Rule to create the shared library (.so file)
$(LIBRARY): $(LIBRARY_OBJS)
	$(CXX) -shared -o $(LIBRARY) $(LIBRARY_OBJS)

# Rule to create the target executable and link with the shared library
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L. -lmylibrary

# Rule for compiling .cpp files into .o files for the main app
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling library source files into object files
$(LIBRARY_SRC_DIR)/%.o: $(LIBRARY_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS_LIB) -c $< -o $@

# Clean up (remove object files, library, and executable)
clean:
	rm -f $(OBJS) $(LIBRARY_OBJS) $(TARGET) $(LIBRARY)

# Phony targets to avoid conflicts with file names
.PHONY: clean all
