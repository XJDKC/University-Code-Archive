#!/bin/bash

for file in `ls $1`
	do
		./src/dcc < $1/$file > $1/${file%.*}.out
	done

folder=$1
