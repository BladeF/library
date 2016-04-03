#!/bin/bash

cd data

if [ -f bookData.txt ]; then
    rm bookData.txt
fi
if [ -f tagData.txt ]; then
    rm tagData.txt
fi

mv bookOutput.txt bookData.txt
mv tagOutput.txt tagData.txt
