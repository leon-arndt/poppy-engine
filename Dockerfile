# Name this initial stage "builder"
FROM debian:latest AS builder
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git libopengl-dev libboost-all-dev libglfw3-dev libglm-dev libglew-dev
COPY . .
WORKDIR .
RUN mkdir ./build
RUN cmake -B/build -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /build
# Create a new stage for our output container
FROM debian:latest
WORKDIR .
# Copy the built binary over from previous stage
COPY --from=builder /build/poppy_run ./
# Run the binary in the new container
CMD ["./poppy_run"]