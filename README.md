
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

# Copy the source code into the container
COPY . .

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
    ports:
      - "8080:8080"
```

To build and run the Docker image using Docker Compose, use the following command:

```bash
docker-compose up
```
