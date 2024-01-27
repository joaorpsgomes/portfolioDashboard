# Use an appropriate base image with C++ environment
FROM ubuntu:latest

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libsystemd-dev \
    libmysqlcppconn-dev \
    mysql-server \
    nlohmann-json3-dev \
    libcurl4-openssl-dev

# Set the working directory in the container
WORKDIR /app

# Copy your C++ application files to the container
COPY ./src/ /app/src/
COPY ./dbFiles /app
COPY ./CMakeLists.txt /app

# Compile your C++ application
RUN mkdir build && cmake -S . -B build
RUN cd build && make

# Configure MySQL to start automatically and set default password
#RUN systemctl enable mysql

# Expose the MySQL port
EXPOSE 3306

# Specify the command to run your application
CMD ["./build/src/portfolioDashboard"]