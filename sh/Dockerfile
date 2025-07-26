FROM ubuntu:latest AS builder

# install g++
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        g++ && \
    rm -rf /var/lib/apt/lists/* # Clean up apt cache to reduce image size

WORKDIR /home/src

COPY ./src /home/src
# Compile the source code
RUN g++ -std=c++20 cli_arguments.cpp recursive_scan.cpp color_scale.cpp plantuml_schema.cpp main.cpp -o /home/code_creator.o && \
    rm -rf /home/src



FROM ubuntu:latest AS runner

# Install Graphviz, OpenJDK, and other tools
# 'apk update' updates the package lists
# 'apk add' installs packages. '--no-cache' is crucial for keeping image size small.
# We also need font-related packages for PlantUML to render text correctly.
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        graphviz \
        openjdk-17-jre-headless \
        curl \
        libstdc++6 \
        libc6 \
        fonts-dejavu-core \
        # Add other font packages if you anticipate specific language/character needs
        # e.g., fonts-noto-cjk, fonts-noto-color-emoji, ttf-mscorefonts-installer (for MS fonts, requires license agreement)
        && \
    rm -rf /var/lib/apt/lists/* # Clean up apt cache to reduce image size

RUN apt update

WORKDIR /home/dist
COPY ./sh/plantuml.jar /home/dist/plantuml.jar

COPY --from=builder /home/code_creator.o /home/dist/code_creator.o
RUN chmod +x /home/dist
RUN chmod +x /home/dist/code_creator.o
RUN chmod 777 /home/dist/plantuml.jar