# !/bin/bash

echo "Verificando a existência da pasta modelamento" 

sleep 2
# Voltando ao diretório principal
cd /home/$USER/

# Testando a existencia da pasta modelagem
nome=`ls -al|grep "^d"|grep "Modelamento"|cut -c56-`
nome1="Modelamento"
sleep 2

# Iniciando o teste
if [ "$nome" == "$nome1" ]
then
		echo "A pasta $nome existe"
		echo "Apagando a pasta $nome"
		sleep 1
		rm -r /home/$USER/Modelamento
		echo "Criando nova pasta $nome"
		mkdir /home/$USER/Modelamento
else
		echo "A pasta $nome1 não existe"
		echo "Criando a pasta $nome1"
		sleep 1
		mkdir /home/$USER/Modelamento

fi

sleep 2
# Voltando para a pasta com os arquivos necessários
echo "Entrando na pasta Modelagem"
cd /home/$USER/Modelagem

echo "Copiando os arquivos necessarios para a pasta $nome1"
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

# Criando pasta auxiliar
mkdir prob.6.0

# Limpando dados antigos
rm -r prob*.*

echo "Tudo deu certo na criação do arquivos" > leia.dat
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
		echo "Tudo deu certo na criação do arquivos" > leia.dat

		# Criando a pasta de probabilidade
		mkdir /home/$USER/Modelamento/prob."$p"

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
				mkdir /home/$USER/Modelamento/prob."$p"/simulacao."$j"
				cp *dat /home/$USER/Modelamento/prob."$p"/simulacao."$j"

				# Remocao de dados
				rm *dat

				# Criacao de arquivo auxiliar
				echo "Tudo de certo na criação dos arquivos" > leia.dat
				clear
		done

done

