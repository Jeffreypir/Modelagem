#!/bin/bash

declare -a MES=('fevereiro2019')

# Voltando ao diretório principal
cd /home/$USER/

for mes in "${MES[@]}"
do
	echo " "
	# Comecando o loop do mes
	echo "Entrando na pasta Modelagem no subdiretorio: $mes "

			# Voltando para a pasta com os arquivos necessários
			cd /home/$USER/Modelagem/"$mes"
			rm -r /home/$USER/Modelamento/"$mes"
			mkdir /home/$USER/Modelamento/"$mes"

			# Copiando os arquivos necessarios
			cp energia_bender_shaped.c /home/$USER/Modelamento/"$mes"
			cp "$mes".txt /home/$USER/Modelamento/"$mes"
			cp plotagem.c /home/$USER/Modelamento/"$mes"
			cp plotagem1.c /home/$USER/Modelamento/"$mes"
			cp plotModelo.c /home/$USER/Modelamento/"$mes"
			cp plotModelo.sh /home/$USER/Modelamento/"$mes"

			# Entrando na pasta criada
			cd /home/$USER/Modelamento/"$mes"

			# Criando os plot da curva de carga
			./plotModelo.sh

			# Criacao do executaveis para o planejamento
			gcc -Wall energia_bender_shaped.c -lglpk -o energia_bender_shaped
			gcc -O2 plotagem.c -o plot


			#Mensagem para a geracao de graficos
			echo "Iniciando simulação: $mes"

			# Percorrendo as probabilides para o despacho de energia 
			for p in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;
			do
				echo "$p" > peso.txt

				# Criando a pasta de probabilidade
				mkdir /home/$USER/Modelamento/"$mes"/prob."$p"

				# Iteracao de produtibilidades
				for j in 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0;

				do
					# Atualizacao
					echo "$j" > dados2.txt 

					#Declarando variavel auxilar para atualizacao das horas 
					declare -i cont=-1

					# Iteracao de demanda
					while read line

					do
						echo "$line" >  dados.txt

						./energia_bender_shaped >> log.txt

					done < "$mes".txt

					while read linha

					do
						((cont++))

						echo  "$cont" "$linha" >> plot.txt

					done < geracao.txt

					# Preparando a plotagem 
					mkdir /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv log.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv plot.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv geracao.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp ./plot /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotagem1.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cd /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"


					# Plotando
					./plot

					# Voltando a pasta Modelamento para simulação seguinte
					cd /home/$USER/Modelamento/"$mes"
				done

				echo "Concluido probabilidade $p" 
			done 
			echo "Finalizada a simulação"
		done


