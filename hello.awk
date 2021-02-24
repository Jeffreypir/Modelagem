#!/bin/awk -f
#BEGIN {cont=0} {cont++; print $1}   geracao.txt

BEGIN {printf "A geração é dada por:\n   T,  H1,    H2 ,   T1,   T2 \n" ;cont=-1} {++cont;print cont " " $0} 


