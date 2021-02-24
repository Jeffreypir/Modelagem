#!/usr/bin/env bash

while read linha; 
do
	echo "$linha" | cut -f2
	sleep 1
done < "janeiro012020.txt"
