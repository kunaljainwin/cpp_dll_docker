
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

To connect to the container and build binaries

```bash
make all 
```

