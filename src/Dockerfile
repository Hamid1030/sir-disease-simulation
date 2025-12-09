FROM ubuntu:24.04 AS build


ENV DEBIAN_FRONTEND=noninteractive

# Set working directory
WORKDIR /src

# Copy source and CMake configuration
COPY CMakeLists.txt .
COPY simulation ./simulation
COPY include ./include

# Install build tools and CMake
RUN apt-get update && \
   apt-get install -y build-essential cmake && \
  apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir build
WORKDIR /src/build
RUN cmake .. 
RUN make

FROM ubuntu as run

# Set working directory in runtime image
WORKDIR /app

COPY --from=build /src/build/hpc_disease_simulation .

RUN mkdir /scratch
WORKDIR /scratch

# Set the entrypoint to run the simulation
ENTRYPOINT ["/app/hpc_disease_simulation"]
