
## Requirements

    Docker: Install Docker
    Docker Compose: Install Docker Compose
    

## Running with Docker Compose

Below is the [Dockerfile](Dockerfile) for the C++ application:

```Dockerfile
# Use the official Ubuntu image as the base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake



```

To run this application using Docker Compose, you'll need to create a `compose.yml` file.

Here's the `compose.yml` file:

```yaml
services:
  main:
    image: main
    build:
      context: .
      dockerfile: Dockerfile
    volumes:
      - ./:/app

```

To build and run the Docker image using Docker Compose, use the following command:

```bash
docker-compose up -d
```

To connect to the container and run commands 

```bash
docker exec -it main /bin/bash
```

To build binaries
```make
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

```

```bash
make all 
```

