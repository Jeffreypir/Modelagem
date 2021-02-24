#!/bin/bash

#Removendo arquivo 
rm -f pmar2019.txt

#Declarando variavel auxilar para atualizacao das horas 
declare -i cont=0

while read linha
do
	echo "$cont"  "$linha" >> pmar2019.txt
	((cont++))

done < marco2019.txt

gcc -O2 plotModelo.c -o plotModelo && ./plotModelo 


