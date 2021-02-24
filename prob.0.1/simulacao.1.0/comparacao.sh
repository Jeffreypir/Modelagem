#!/bin/bash

declare -a MES=('janNovo')
for mes in "${MES[@]}"
do
	cp comparacao.r /home/$USER/Modelamento"$mes"
	cd /home/$USER/Modelamento/"$mes"
	rm -rf comparacao.txt

# Percorrendo as probabilides para o despacho de energia 
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;

do
	for j in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;

	do
		cp comparacao.r /home/$USER/Modelamento/"$mes"/"i"/"j"
		cd /home/$USER/Modelamento/"$mes"/"i"/"j"
		./comparacao.r

		exec 3<'custo.txt'
		echo "$i  $j" " $(head -n 1 <&3)" >> comparacao.txt
	done
done
done
