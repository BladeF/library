#!/bin/bash

mkdir data
if [ -d data ]
then
    echo "Data directory creation successful"
else
    echo "Data directory creation failed"
fi

chmod 755 src/*
chmod 755 data  src scripts

g++ -o library src/library.cpp src/Book.cpp

chmod 111 ./library

mv init.sh scripts
chmod 555 *.sh scripts/*.sh
