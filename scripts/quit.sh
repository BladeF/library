#!/bin/bash

cd data

# Checks for old data files and removes if present
if [ -f bookData.txt ]; then
    rm bookData.txt
fi
if [ -f tagData.txt ]; then
    rm tagData.txt
fi

# Takes current status and saves it as the input
# for the next run of the program
if [ -f bookOutput.txt ]; then
    mv bookOutput.txt bookData.txt
fi
if [ -f tagOutput.txt ]; then
    mv tagOutput.txt tagData.txt
fi
