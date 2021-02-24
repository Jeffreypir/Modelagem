#!/bin/bash
rm -rf /home/$USER/Modelamento/janCurva2
rm -rf /home/$USER/Modelamento/janCurva3

#declare -a MES=('janeiro012020' 'janNovo' 'janCurva2' 'janCurva2' )
declare -a MES=('janCurva2' 'janCurva3' )
echo "Verificando a existência da pasta modelamento" 

#Pausa
sleep 2

# Voltando ao diretório principal
cd /home/$USER/

for mes in "${MES[@]}"
do
	echo " "
	# Comecando o loop do mes
	echo "Entrando na pasta Modelagem no subdiretorio: $mes "

			# Voltando para a pasta com os arquivos necessários
			cd /home/$USER/Modelagem/"$mes"
			mkdir /home/$USER/Modelamento/"$mes"

			# Copiando os arquivos necessarios
			cp energia_bender_shaped.c /home/$USER/Modelamento/"$mes"
			cp "$mes".txt /home/$USER/Modelamento/"$mes"
			cp plotagem.c /home/$USER/Modelamento/"$mes"
			cp ventoHoras.txt /home/$USER/Modelamento/"$mes"
			cp ventoSeg.txt /home/$USER/Modelamento/"$mes"
			cp watts.txt  /home/$USER/Modelamento/"$mes"
			cp wSeg.txt  /home/$USER/Modelamento/"$mes"
			cp plotagem1.c /home/$USER/Modelamento/"$mes"
			cp plotModelo.c /home/$USER/Modelamento/"$mes"
			cp plotModeloVento.c /home/$USER/Modelamento/"$mes"
			cp plotModeloVentoSeg.c /home/$USER/Modelamento/"$mes"
			cp plotModeloWatts.c /home/$USER/Modelamento/"$mes"
			cp plotModeloWattsSeg.c /home/$USER/Modelamento/"$mes"
			cp plotModeloCusto.c /home/$USER/Modelamento/"$mes"
			cp plotModelo.sh /home/$USER/Modelamento/"$mes"

			# Entrando na pasta criada
			cd /home/$USER/Modelamento/"$mes"


			# Criando os plot da curva de carga
			./plotModelo.sh

			# Criacao do executaveis para o planejamento
			gcc -Wall energia_bender_shaped.c -lglpk -o energia_bender_shaped
			gcc -O0 plotagem.c -o plot


			#Mensagem para a geracao de graficos
			echo "Iniciando simulação: $mes"

			# Percorrendo as probabilides para o despacho de energia 
			for p in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;
			do
				echo "$p" > peso.txt

				# Criando a pasta de probabilidade
				mkdir /home/$USER/Modelamento/"$mes"/prob."$p"

				# Iteracao de produtibilidades
				for j in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;

				do
					# Atualizacao
					echo "$j" > dados2.txt 

					#Declarando variavel auxilar para atualizacao das horas 
					declare -i cont=-1
					declare -i contCusto=-1

					# Iteracao de demanda
					while read line

					do
						echo "$line" | cut -f1 >  dados.txt
						echo "$line" | cut -f2 >  eolico.txt

						./energia_bender_shaped >> log.txt

					done < "$mes".txt

					while read linha

					do
						((cont++))

						echo  "$cont" "$linha" >> plot.txt

					done < geracao.txt

					while read linha

					do
						((contCusto++))

						echo  "$contCusto" "$linha" >> custoEsperado.txt

					done < custoFuturo.txt


					# Preparando a plotagem 
					mkdir /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv log.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv plot.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv geracao.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv custoFuturo.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					mv custoEsperado.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp ./plot /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotagem1.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp watts.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp wSeg.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp ventoHoras.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp ventoSeg.txt /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotModeloCusto.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotModeloVento.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotModeloVentoSeg.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotModeloWatts.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cp plotModeloWattsSeg.c /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"
					cd /home/$USER/Modelamento/"$mes"/prob."$p"/simulacao."$j"


					# Plotando
					./plot

					gcc -O0 plotModeloCusto.c -o plotModeloCusto && ./plotModeloCusto 
					gcc -O0 plotModeloVento.c -o plotModeloVento && ./plotModeloVento 
					gcc -O0 plotModeloVentoSeg.c -o plotModeloVentoSeg && ./plotModeloVentoSeg 
					gcc -O0 plotModeloWatts.c -o plotModeloWatts && ./plotModeloWatts 
					#gcc -O0 plotModeloWattsSeg.c -o plotModeloWattsSeg && ./plotModeloWattsSeg 

					# Voltando a pasta Modelamento para simulação seguinte
					cd /home/$USER/Modelamento/"$mes"
				done

				echo "Concluido probabilidade $p" 
			done 
			echo "Finalizada a simulação"
		done


