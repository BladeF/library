#!/bin/bash

cd data

if [ -f bookData.txt ]; then
    rm bookData.txt
fi
if [ -f tagData.txt ]; then
    rm tagData.txt
fi

cat bookOutput.txt | tee bookData.txt
cat tagOutput.txt | tee tagData.txt

rm bookOutput.txt
rm tagOut.txt
