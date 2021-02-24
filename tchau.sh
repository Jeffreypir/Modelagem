#!/usr/bin/env bash
rm terra.txt

while read linha; 
do
	echo "$linha" >> terra.txt
	sleep 1
done < "janeiro012020.txt"
