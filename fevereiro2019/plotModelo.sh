#!/bin/bash

#Removendo arquivo 
rm -f pfev2019.txt

#Declarando variavel auxilar para atualizacao das horas 
declare -i cont=0

while read linha
do
	echo "$cont"  "$linha" >> pfev2019.txt
	((cont++))

done < fevereiro2019.txt

gcc -O2 plotModelo.c -o plotModelo && ./plotModelo 


