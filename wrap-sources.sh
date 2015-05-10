# !/bin/bash

NAME="buried-secrets"
VERSION="1.0"

DIR=$NAME
DIR+="-"
DIR+=$VERSION

mkdir -p $DIR
cp -r Box2D CMakeLists.txt src data UI_data README.md cmake_modules $DIR

tar -cf "$DIR.tar.gz" $DIR
rm -r $DIR
