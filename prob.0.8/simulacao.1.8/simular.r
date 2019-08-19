#! /usr/bin/env Rscript 

# Plotando grafico da simulacao 
demanda <-unlist (read.table("demanda.dat")) 
Hidr1   <- unlist (read.table("VTH1S1.dat"))
Hidr2   <- unlist (read.table("VTH2S1.dat"))
G1 <- unlist (read.table("G1.dat"))
G2 <- unlist (read.table("G2.dat"))

# Arquivo plotagem em formato eps
cairo_ps("simulacaopb01pt10.eps",6.0,6.0)
matplot (demanda,cbind(Hidr1,Hidr2,G1,G2),
		 main ="Despacho Hidrotérmico 1",
		 font.main=1,
		 xlab="Demanda (MW)",
		 col = c("blue","green","red","yellow"), 
		 type = "l",
		 pch=20,
		 lwd=1,
		 lty=1,
		 bty="n",
		 ylab="Geração (MW)")

legend (100000,35000,inset=0.01,
		legend=c(
				 "Hidrelétrica H1",
				 "Hidrelétrica H2","Termelétrica T1",
				 "Termelétrica T2"
				 ), 
		col= c(
			   "blue",
			   "green",
			   "red",
			   "yellow"
			   ),
		lty=1,
		bg=("white"),
	   	horiz=F)
dev.off()

pdf("simulacaopb01pt10.pdf",6.0,6.0)
matplot (demanda,cbind(Hidr1,Hidr2,G1,G2),
		 main ="Depacho Hidrotérmico 1",
		 font.main=1,
		 xlab="Demanda (MW)",
		 col = c("blue","green","red","yellow"), 
		 type = "l",
		 pch=20,
		 lwd=1,
		 lty=1,
		 bty="n",
		 ylab="Geração (MW)")

legend (100000,35000,inset=0.01,
		legend=c(
				 "Hidrelétrica H1",
				 "Hidrelétrica H2","Termelétrica T1",
				 "Termelétrica T2"
				 ), 
		col= c(
			   "blue",
			   "green",
			   "red",
			   "yellow"
			   ),
		lty=1,
		bg=("white"),
	   	horiz=F)
dev.off()

