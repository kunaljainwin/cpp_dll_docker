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

# # Compile the C++ code
# RUN g++ -o main main.cpp 

# # Expose the port on which the API will listen
# EXPOSE 8080

# # Command to run the API when the container starts
# CMD ["./ok_api"]
