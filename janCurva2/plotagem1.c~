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
	fprintf(gp,"set term pdf \n");
	fprintf(gp,"set output 'splot1.pdf'\n");
	fprintf(gp,"set multiplot \n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set origin 0,0 \n");
	fprintf(gp,"set size 1,1 \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MW/h' \n");
	fprintf(gp,"plot [0:720] [0:45000] 'plot.txt' using 1:2 with linespoints lc 6 pt 6 ps 0.2 t'Hidrelétrica 1'\n");
	fprintf(gp,"set notitle \n");
	fprintf(gp,"set nokey \n");
	fprintf(gp,"set tics font ',8' \n");
	fprintf(gp,"set origin 0.1,0.13 \n");
	fprintf(gp,"set size 0.5,0.45 \n");
	fprintf(gp,"set noxlabel \n");
	fprintf(gp,"set noylabel \n");
	fprintf(gp,"plot [0:10] [44910:45000] 'plot.txt' using 1:2 with linespoints lc 6 pt 6 ps 0.3 notitle \n");
	fprintf(gp,"unset multiplot \n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

