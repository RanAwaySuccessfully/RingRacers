#!/bin/bash
ARCH=$1
GOARCH=""
# tested: aarch64 x86_64

case $ARCH in
    "x86_64")
        GOARCH="amd64"
        ;;

    "aarch64")
        GOARCH="arm64"
        ;;
esac

TAGS=$2

cd ../
echo ""

docker run --cidfile docker.cid -v $(pwd):$(pwd) -w $(pwd) -i -t debian:bookworm ./scripts_new/build.sh $ARCH $GOARCH $TAGS
CID=$(cat docker.cid)
rm docker.cid
docker container rm $CID

echo "END OF FILE"
