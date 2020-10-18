FROM ubuntu:16.04

## Configuration, read from environment.
ARG PROJ_NAME
ENV PROJ_NAME=${PROJ_NAME}

## Toolchain Setup
# Install required tools to run the compiler.
RUN   dpkg --add-architecture i386 \
 &&   apt-get update \
 &&   apt-get install --yes ca-certificates wget libc6:i386 libncurses5:i386 libstdc++6:i386 lib32z1 make cmake hashdeep bzip2 \
 &&   update-ca-certificates
# Get the S32DS build_tools folder, extracted from S32PA.
RUN wget -qO- https://github.com/AutomotiveDevOps/powerpc-eabivle-gcc-dockerfiles/releases/download/v2.1.10/S32DS_build_tools.tar.bz2 | tar xjvf - -C /
# Copy board specific make files to the build_tools directory.
WORKDIR /S32DS/build_tools/
# Add the powerpc-eabivle gcc folder to the path
ENV PATH=${PATH}:/S32DS/build_tools/powerpc-eabivle-4_9/bin

## Build
# Set up the build directory
RUN mkdir -p /S32DS/build
WORKDIR /S32DS/build
# Copy Source, Include, & Project_Settings to the build source directory.
COPY Makefile /S32DS/build/Makefile
COPY src /S32DS/build/src
COPY include /S32DS/build/include
COPY Project_Settings /S32DS/build/Project_Settings
# Build everything.
RUN make \
	--always-make \
	--directory=/S32DS/build \
	--environment-overrides \
	--makefile=/S32DS/build/Makefile \
	--jobs=8

# Generate Digital Forensics XML: Maximum tracibility for all of the build and artifacts.
#     DFXML is a file format designed to capture metadata and provenance
#     information about the operation of software tools in a systematic fashion.
RUN hashdeep -c md5,sha256,tiger,whirlpool -d -r /S32DS/build > /S32DS/build/${PROJ_NAME}.dfxml

# Bundle up the build
WORKDIR /S32DS/artifacts/
RUN tar -cjf /S32DS/artifacts/${PROJ_NAME}_artifacts.tar.bz2 /S32DS/build
