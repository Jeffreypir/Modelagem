#!/usr/bin/env bash

while read linha; 
do
	echo "$linha" | cut -f1 >> janNovo.txt
	sleep 1
done < "janeiro012020.backup"
