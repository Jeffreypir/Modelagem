#!/bin/bash

echo "Verificando a existência da pasta modelamento" 

#Pausa
sleep 2

# Voltando ao diretório principal
cd /home/$USER/

# Testando a existencia da pasta modelagem
# Buscando pela existência da pasta antiga modelagem em /home/$USER
nome=`ls -al|grep "^d"|grep "Modelamento"|cut -c56-`
nome1="Modelamento"

#Pausa
sleep 2

# Iniciando o teste
if [ "$nome" == "$nome1" ]
then
		echo "A pasta $nome existe"
		echo "Apagando a pasta $nome"

		#Pausa
		sleep 1
		rm -r /home/$USER/Modelamento
		echo "Criando nova pasta $nome"
		mkdir /home/$USER/Modelamento
else
		echo "A pasta $nome1 não existe"
		echo "Criando a pasta $nome1"

		#Pausa
		sleep 1
		mkdir /home/$USER/Modelamento

fi

#Pausa
sleep 2

# Voltando para a pasta com os arquivos necessários
echo "Entrando na pasta Modelagem"
cd /home/$USER/Modelagem

echo "Copiando os arquivos necessarios para a pasta $nome1"

#Pausa
sleep 3

# Copiando os arquivos necessarios
cp energia_bender_shaped.c /home/$USER/Modelamento
cp dados.txt  /home/$USER/Modelamento
cp dados2.txt /home/$USER/Modelamento
cp peso.txt   /home/$USER/Modelamento

# Entrando na pasta criada
cd /home/$USER/Modelamento

# Compilar o algoritmo energia_bender_shaped.c
 gcc -Wall energia_bender_shaped.c -lglpk -o energia_bender_shaped

# Percorrendo as probabilides para o despacho de energia 
for p in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;
do
		clear
		echo " Calculando para a probabilidade"
		echo "$p"

		#Pausa
		sleep 4
		echo "$p" > peso.txt

		# Criacao de arquivo auxiliar
		echo "Apague" > leia.dat

		# Criando a pasta de probabilidade
		mkdir /home/$USER/Modelamento/prob."$p"

		# Remocao de arquivos 
		rm *dat

		# Variavel auxiliar
		
		# Iteracao de produtibilidades
		for j in 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0;
		do
				clear
				#Pausa
				sleep 4
				echo " Iniciando simulação para produtibilidade $j"
				#Pausa
				sleep 4
				clear

				# Atualizacao
				echo "$j" > dados2.txt 

				# Iteracao de demanda
				for i in $(seq 100 100 200000);
				do
						# Inicio do algoritmo PDDE
						./energia_bender_shaped
						echo " DEMANDA = $i"
						echo " "

						#Atualizacao
						echo "$i" > dados.txt
				done

				# Atualizacao
				echo "100" > dados.txt

				# Criando arquivo de demanda
				for k in $(seq 100 100 200000);
				do
						echo "$k" >> demanda.dat 
				done

				# Arquivando dados 
				mkdir /home/$USER/Modelamento/prob."$p"/simulacao."$j"
				cp *dat /home/$USER/Modelamento/prob."$p"/simulacao."$j" 
				cp /home/$USER/Modelagem/simular.r /home/$USER/Modelamento/prob."$p"/simulacao."$j" 
				cp /home/$USER/Modelagem/scusto.r /home/$USER/Modelamento/prob."$p"/simulacao."$j" 
				cd /home/$USER/Modelamento/prob."$p"/simulacao."$j"/

				sleep 2
				echo "Criando os gráficos para Probabilidade $p e simulação de produtibilidade $j"
				sleep 2

				# Criando os graficos
				chmod +x simular.r
				./simular.r
				chmod +x scusto.r 
				./scusto.r

				# Voltando a pasta Modelamento para simulação seguinte
				cd /home/$USER/Modelamento
	
				# Remocao de dados
				rm *dat

				# Criacao de arquivo auxiliar
				echo "Tudo de certo na criação dos arquivos" > leia.dat
				clear
		done

done

