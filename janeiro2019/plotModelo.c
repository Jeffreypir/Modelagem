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
	fprintf(gp,"set title '{/:Bold=12 Curva de carga do subsistema nordeste}' \n");
	fprintf(gp,"set output 'pjan2019.pdf'\n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Helvetica,10' \n");
	fprintf(gp,"set origin 0,0 \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'MWh' \n");
	fprintf(gp,"plot [0:724] 'pjan2019.txt' using 1:2 with linespoints lc 6 pt 6 ps 0.2 t'Janeiro 2019'\n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

