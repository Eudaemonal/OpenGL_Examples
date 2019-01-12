#!/bin/sh

CLEAN=0

for i in "$@"
do
    case $i in
        -c)
        CLEAN=1
        ;;
        *)
        # unknown option
        ;;
esac
done


if [ $CLEAN -eq 1 ]; then
    rm -rf build
else
    mkdir build
    cd build
    cmake ..
    make
fi
