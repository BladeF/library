#!/bin/bash

cd data

rm bookData.txt
rm tagData.txt

cat bookOutput.txt | tee bookData.txt
cat tagOutput.txt | tee tagData.txt

rm bookOutput.txt
rm tagOut.txt
