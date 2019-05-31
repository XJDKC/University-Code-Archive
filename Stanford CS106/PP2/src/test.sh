#!/bin/bash

for file in `ls $1`
do
    if [ ${file##*.} = "decaf" -o ${file##*.} = "frag" ];  then
        ./dcc < $1/$file &> $1/${file%.*}.out
    fi
done

folder=$1
