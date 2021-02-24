#!/usr/bin/gnuplot -persist
set title "Relação entre custo, produtibilidade e cenários"
set key right bottom 
set key font "Times,8"
set origin 0,0
set xlabel "Probabilidade" rotate parallel offset -5
set ylabel "Produtibilidade" rotate parallel offset -5
set zlabel "Custo" rotate parallel offset -5 
set grid x y z vertical back ls 10
set border 127
set view 80,6
set mouse
splot 'comparacao.txt' using 1:2:3 with linespoints lc 6 pt 7 ps 1.0 t''
pause -1



