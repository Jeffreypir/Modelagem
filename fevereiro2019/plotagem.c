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
 * ==========================================================
 */
int main(void){
	FILE *gp;
	gp = popen(GNUPLOT, "w");
	fprintf(gp,"set term pdf font 'Helvetica,8'\n");
	fprintf(gp,"set output 'splot.pdf'\n");
	fprintf(gp,"set multiplot layout 2,2 columnsfirst title '{/:Bold=12 Geração de energia em relação ao tempo}' margins screen 0.11, 0.94, 0.14,0.92 spacing screen 0.16 \n");
	fprintf(gp,"set size 0.5,0.5 \n");
   	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Helvetica,10' \n");
   	fprintf(gp,"set xrange [0:650] \n");
   	fprintf(gp,"set xrange [0:46000] \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MWh' \n");
	fprintf(gp,"plot [0:650] [0:46000] 'plot.txt' using 1:2 with linespoints lc 6 pt 2 ps 0.2 t'Hidrelétrica 1' \n");
   	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Helvetica,10' \n");
   	fprintf(gp,"set xrange [0:650] \n");
   	fprintf(gp,"set xrange [0:46000] \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MWh' \n");
	fprintf(gp,"set size 0.5,0.5 \n");
	fprintf(gp,"plot [0:650] [0:46000] 'plot.txt' using 1:3 with linespoints lc 2 pt 2 ps 0.2 t'Hidrelétrica 2' \n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Helvetica,10' \n");
   	fprintf(gp,"set xrange [0:720] \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MWh' \n");
	fprintf(gp,"set size 0.5,0.5 \n");
	fprintf(gp,"plot [0:650] [0:46000] 'plot.txt' using 1:4 with linespoints lc 7 pt 2 ps 0.2 t'Termelétrica 1' \n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Helvetica,10' \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MWh' \n");
	fprintf(gp,"set size 0.5,0.5 \n");
	fprintf(gp,"plot [0:650] [0:46000]'plot.txt' using 1:5 with linespoints lc 4 pt 2 ps 0.2 t'Termelétrica 2' \n");
	fprintf(gp,"unset multiplot \n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

