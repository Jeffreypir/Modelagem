#include <stdio.h>
#include <stdlib.h>
#define GNUPLOT "gnuplot -persist"   
#define EXIT_SUCESS 0

/*==================== PROGRAM ==============================
 * Program: plotagem.c 
 * Description: plotagem 
 * Date of Create:  seg 22 jun 2020 14:18
 * Update in:  seg 22 jun 2020 14:18
 * Compiler: gcc filename -o filename
 * Author:Jefferson Bezerra dos Santos
 *===========================================================
 */


/*=================== FUNCTION MAIN () ======================
 * Function: main()
 * Description: gnuplot 
 * fprintf(gp,"set nokey \n");
 * ==========================================================
 */
int main(void){
	FILE *gp;
	gp = popen(GNUPLOT, "w");
	fprintf(gp,"set term pdfcairo font 'Times,12' fontscale 0.6 \n");
	fprintf(gp,"set output 'splot1.pdf'\n");
	fprintf(gp,"set multiplot \n");
	fprintf(gp,"set title 'Geração da termelétrica 1' \n");
	fprintf(gp,"set key right top \n");
	fprintf(gp,"set origin 0,0 \n");
	fprintf(gp,"set size 1,1 \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'Geração (MWh) \n");
	fprintf(gp,"set arrow from 18,0 to 7,6300 nohead ls 7 \n");
	fprintf(gp,"set arrow from 22,0 to 18.2,6300 nohead ls 7 \n");
	fprintf(gp,"set grid back ls 10\n");
	fprintf(gp,"plot [0:24] [0:18000] 'plot.txt' using 1:4 with linespoints lc 7 pt 7 ps 0.4 t'Termelétrica 1'\n");
	fprintf(gp,"set notitle \n");
	fprintf(gp,"set nokey \n");
	fprintf(gp,"set tics font ',9' \n");
	fprintf(gp,"set origin 0.3,0.3 \n");
	fprintf(gp,"set size 0.5,0.5 \n");
	fprintf(gp,"set noxlabel \n");
	fprintf(gp,"set noylabel \n");
	fprintf(gp,"unset arrow \n");
	fprintf(gp,"unset grid \n");
	fprintf(gp,"plot [18:22] [0:800] 'plot.txt' using 1:4 with linespoints lc 7 pt 7 ps 0.4 notitle \n");
	fprintf(gp,"unset multiplot \n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

