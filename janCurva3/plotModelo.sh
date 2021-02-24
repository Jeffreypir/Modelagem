#!/bin/bash

#Removendo arquivo 
rm -f pjan012020.txt

#Declarando variavel auxilar para atualizacao das horas 
declare -i cont=0

while read linha
do
	echo "$cont"  "$linha" >> pjan012020.txt
	((cont++))

	sleep 1

done < janCurva3.txt

gcc -O0 plotModelo.c -o plotModelo && ./plotModelo 

gcc -O0 plotModeloVento.c -o plotModeloVento && ./plotModeloVento 
