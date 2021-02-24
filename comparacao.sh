#!/bin/bash

declare -a MES=('janeiro012020Vento0' 'janeiro012020' )
for mes in "${MES[@]}"
do
echo "Entrando na pasta $mes"
	cp plotCom.sh /home/$USER/Modelamento/"$mes"
	cp comparacao.r /home/$USER/Modelamento/"$mes"
	cd /home/$USER/Modelamento/"$mes"
	echo "Criando arquivo comparacao" > comparacao.txt

# Percorrendo as probabilides para o despacho de energia 
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;
do
	for j in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;

	do
		mv comparacao.txt /home/$USER/Modelamento/"$mes"/prob."$i"/simulacao."$j"
		cp comparacao.r /home/$USER/Modelamento/"$mes"/prob."$i"/simulacao."$j"
		cd /home/$USER/Modelamento/"$mes"/prob."$i"/simulacao."$j"
		./comparacao.r

		exec 3<'custo.txt'
		echo "$i  $j" " $(head -n 1 <&3)" >> comparacao.txt
		cp comparacao.txt /home/$USER/Modelamento/"$mes" 
	done
done

echo "Entrando na pasta modelagem"
cd /home/$USER/Modelagem/
done
