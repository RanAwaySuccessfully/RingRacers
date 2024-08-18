#!/bin/bash
ARCH=$1
GOARCH=$2
TAGS=$3
TOOLCHAIN="-DCMAKE_TOOLCHAIN_FILE="$ARCH".cmake"

if [ $ARCH = "x86_64" ];
then
    TOOLCHAIN=""
fi

if [ -n "$TAGS" ];
then
    TAGS="--tags $TAGS"
fi

# resolving dependencies

dpkg --add-architecture arm64
apt update
apt install cmake gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libfuse2 libcurl4-openssl-dev:$GOARCH zlib1g-dev:$GOARCH libpng-dev:$GOARCH libogg-dev:$GOARCH libvorbis-dev:$GOARCH libvpx-dev:$GOARCH libyuv-dev:$GOARCH libsdl2-dev:$GOARCH ninja-build zlib1g-dev:$GOARCH -y

# building

echo ""
cmake --preset ninja-release-arm64
cmake --build --preset ninja-release-arm64
modprobe fuse
./appimage-builder-x86_64.AppImage --recipe AppImageBuilder.yml

echo "END OF BUILD"
exit
