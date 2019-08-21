#! /usr/bin/env Rscript

# Plotando grafico da curva de custo 
demanda <-unlist (read.table("demanda.dat")) 
custo <- unlist (read.table("z.dat"))

# Criando arquivo de plotagem eps
cairo_ps("zpb01pt10.eps",5.0,5.0)
matplot (demanda,cbind(custo),
		 main= "Curva do Custo Esperado 1",
		 font.main=1,
		 xlab="Demanda (MW)",
		 col = c("red"), 
		 type = "l",
		 pch=20,
		 lwd=1,
		 lty=1,
		 bty="n",
		 ylab="Custo Esperado (R$)")
legend (
		120000,200000
		,inset=0.01,
		legend=c(
				 "Valor ótimo"
				 ), 
		col= c(
			   "red"
			   ),
		lty=1,
		bg=("white"),
	   	horiz=F)

dev.off()

# Criando arquivo de plotagem pdf
pdf("zpb01pt10.pdf",5.0,5.0)
matplot (demanda,cbind(custo),
		 main= "Curva do Custo Esperado 1",
		 font.main=1,
		 xlab="Demanda (MW)",
		 col = c("red"), 
		 type = "l",
		 pch=20,
		 lwd=1,
		 lty=1,
		 bty="n",
		 ylab="Custo Esperado (R$)")
legend (
		120000,200000
		,inset=0.01,
		legend=c(
				 "Valor ótimo"
				 ), 
		col= c(
			   "red"
			   ),
		lty=1,
		bg=("white"),
	   	horiz=F)

dev.off()


