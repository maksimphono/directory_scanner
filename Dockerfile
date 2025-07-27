FROM ubuntu:latest AS builder

# install g++
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        g++ && \
    rm -rf /var/lib/apt/lists/* # Clean up apt cache to reduce image size

WORKDIR /home/src

COPY ./src /home/src
COPY ./USAGE.txt /home/USAGE.txt
# Compile the source code
RUN g++ -std=c++20 cli_arguments.cpp recursive_scan.cpp color_scale.cpp plantuml_schema.cpp main.cpp -o /home/code_creator.o && \
    rm -rf /home/src



FROM ubuntu:latest AS runner

# Install Graphviz, OpenJDK, and other tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        graphviz \
        openjdk-17-jre-headless \
        curl \
        libstdc++6 \
        libc6 \
        fonts-dejavu-core \
        && \
    rm -rf /var/lib/apt/lists/* # Clean up apt cache to reduce image size

RUN apt update

WORKDIR /home/dist
COPY ./sh/plantuml.jar /home/dist/plantuml.jar
COPY ./USAGE.txt /home/USAGE.txt

COPY --from=builder /home/code_creator.o /home/dist/code_creator.o

RUN chmod +x /home/dist/code_creator.o
RUN chmod +x /home/dist/plantuml.jar