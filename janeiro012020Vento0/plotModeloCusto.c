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
	fprintf(gp,"set term pdfcairo font 'Times,12' fontscale 0.6\n");
	fprintf(gp,"set title 'Custo esperado' \n");
	fprintf(gp,"set output 'custoEsperado.pdf'\n");
	fprintf(gp,"set key right bottom \n");
	fprintf(gp,"set key font 'Times,10' \n");
	fprintf(gp,"set origin 0,0 \n");
	fprintf(gp,"set xlabel 'Tempo (h)'\n");
	fprintf(gp,"set ylabel 'Custo (R$)' \n");
	fprintf(gp,"set grid back ls 10\n");
	fprintf(gp,"plot [0:24] 'custoEsperado.txt' using 1:2 with linespoints lc 6 pt 7 ps 0.5 t'Valor R$'\n");
    fclose(gp);

	return EXIT_SUCESS;
}/*----------End of function-----------------*/

