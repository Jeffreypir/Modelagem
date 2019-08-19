
# Plotando grafico da simulacao 
demanda <-unlist (read.table("demanda.dat")) 
custo <- unlist (read.table("z.dat"))

cairo_ps("zpb08pt14.eps",4.0,4.0)
matplot (demanda,cbind(custo),
	  xlab="Demanda (MW)",
	 col = c("red"), 
	 type = "l",
	 pch=20,
	 lwd=1,
	 lty=1,
	 bty="n",
	 ylab="Custo Esperado (R$)")

legend (70000,200000,inset=0.01,legend=c("Valor ótimo"), col= c("red"),lty=1,bg=("white"), horiz=F)
dev.off()

pdf("zpb08pt14.pdf",4.0,4.0)
matplot (demanda,cbind(custo),
	  xlab="Demanda (MW)",
	 col = c("red"), 
	 type = "l",
	 pch=20,
	 lwd=1,
	 lty=1,
	 bty="n",
	 ylab="Custo Esperado (R$)")

legend (70000,200000,inset=0.01,legend=c("Valor ótimo"), col= c("red"),lty=1,bg=("white"), horiz=F)
dev.off()


