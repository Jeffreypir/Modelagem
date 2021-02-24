#!/bin/Rscript 

 #==================== PROGRAM ==============================
 # Program: comparacao.r
 # Description: Script nojento
 # Date of Create: qua 03 fev 2021 12:03:54 -03
 # Update in: qua 03 fev 2021 12:03:59 -03
 # Author:Jefferson Bezerra dos Santos
 #===========================================================


custo <- mean(custoFuturo.txt)
write.table(custo, file = "custo.txt", sep = "\t", na = "", quote = FALSE)

