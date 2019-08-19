# !/bin/bash

# Criando pasta auxiliar
mkdir prob.6.0

# Limpando dados antigos
rm -r prob*.*

echo "oi" > oi.dat
rm *dat


# Percorrendo as probabilides para o despacho de energia 
for p in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0;
do
		clear
		echo " Calculando para a probabilidade"
		echo "$p"
		sleep 4
		echo "$p" > peso.txt

		# Criacao de arquivo auxiliar
		echo "oi" > oi.dat

		# Criando a pasta de probabilidade
		mkdir /home/jefferson/Documentos/projeto_jeffrey/Modelagem/prob."$p"

		# Remocao de arquivos 
		rm *dat

		# Variavel auxiliar
		
		# Iteracao de produtibilidades
		for j in 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0;
		do
				clear
				sleep 4
				echo " Iniciando simulação para produtibilidade $j"
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
				mkdir /home/jefferson/Documentos/projeto_jeffrey/Modelagem/prob."$p"/simulacao."$j"
				cp *dat /home/jefferson/Documentos/projeto_jeffrey/Modelagem/prob."$p"/simulacao."$j"

				# Remocao de dados
				rm *dat

				# Criacao de arquivo auxiliar
				echo "oi" > oi.dat
				clear
		done

done
