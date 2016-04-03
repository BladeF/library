#!/bin/bash

mkdir data
if [ -d data ]
then
    echo "Data directory creation successful"
else
    echo "Data directory creation failed"
fi

chmod 755 src/* lib/*
chmod 644 data lib src scripts

g++ -o library src/library.cpp lib/Book.cpp

chmod 400 library

mv init.sh scripts
chmod 700 *.sh scripts/*.sh
