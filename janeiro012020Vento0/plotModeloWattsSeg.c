#include <stdio.h>
#include <stdlib.h>
#define GNUPLOT "gnuplot -persist"   
#define EXIT_SUCESS 0

/*==================== PROGRAM ==============================
 * Program: plotModelo.c
 * Description: plotagem da curva de carga 
 * Date of Create: qua 24 jun 2020 16:36
 * Update in:  qua 24 jun 2020 16:36
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
	fprintf(gp,"set term pdf \n");
	fprintf(gp,"set title '{/:Times=12 Curva da Geração}' \n");
	fprintf(gp,"set output 'wattsSeg.pdf'\n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Times,10' \n");
	fprintf(gp,"set origin 0,0 \n");
	fprintf(gp,"set xlabel 'Tempo (s)'\n");
	fprintf(gp,"set ylabel 'Geração (MW)' \n");
	fprintf(gp,"set grid back ls 10\n");
	fprintf(gp,"plot 'wSeg.txt' using 1:2 with points lc 6 pt 7 ps 0.5 t'Geração'\n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

