FROM ubuntu:latest

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential libssl-dev

# Set the working directory
WORKDIR /app

# Copy the project files, including Makefile and source code
# it uses current directory to copy the source files
COPY . .

# Run make to compile the IRC server
RUN make

# Expose the IRC port
EXPOSE 2000

# Set the entrypoint with default arguments
ENTRYPOINT ["./bin/ircserv", "2000", "pass"]


# Run this to build the container from the image
#docker build -t irc-server .
# Run this to run the container interactively on port 2000
#docker run -it -p 2000:2000 irc-server
