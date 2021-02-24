#!/bin/Rscript 

 #==================== PROGRAM ==============================
 # Program: comparacao.r
 # Description: Script nojento
 # Date of Create: qua 03 fev 2021 12:03:54 -03
 # Update in: qua 03 fev 2021 12:03:59 -03
 # Author:Jefferson Bezerra dos Santos
 #===========================================================


dados1 <- read.table("custoFuturo.txt") # Lendo os dados e guardando
dados <- as.numeric(unlist(dados1))           # transformcao necessaria para utilizar os dados 

custo <- mean(dados)
write.table(custo, file = "custo.txt", sep = "\t", na = "", quote = FALSE, row.names = FALSE, col.names = FALSE)

