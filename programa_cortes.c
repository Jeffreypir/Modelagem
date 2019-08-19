/*
 * ======================================================
 *
 *       Filename: mult_cortes.c 
 *
 *    Description:  Programação utilizando os mult cortes de Benders, GNU GLPK
 *                  Despacho de energia, progrmação Linear,
 *                  programação estocástica. 
 *                  Viva o linux !!!
 *                  Por que amamos a liberdade.
 *
 *        Version:  0.1
 *        Created:  21-05-2019 11:05:42
 *       Revision:  21-05-2019 11:05:26
 *       Compiler:  gcc
 *
 *         Author:  Jefferson Bezerra dos Santos 
 *
 * ======================================================
 */

# include <stdio.h> /* Entrada e saida C */ 
# include <stdlib.h> /* Biblioteca padrão do C */
# include <glpk.h> /*  Gnu GLPK */
# include <math.h>

double PDDE(double dem){
	       printf ("INICIO \n");	
		   printf ( "Primal \n");
		   printf (" Chute Inicial: x1 = 0, x2 = 0, lambda = 0  \n \n"); 

		   /* Atualizando x1 é para o cálculo da dual 
		   *
		   * CHUTE INICIAL sem restrições */
		   double x_1 = dem ,x_2 = 0.0, lamb_da = 0.0, Qx = 2.0;


		  /* PROBLEMA DUAL
		   * Declarando as variaveis 
		   *
		   * ======== INICIO ======== */
		  glp_prob *ld;
		  int iia[300+1], jja[300+1];
		  double aar[300+1],Q,u1,u2,u3;
		  /* ========= FIM ========== */

		  
           /* PROBLEMA PRIMAL */

          /* Declarando as variaveis 
		   *
		   * ======== INICIO ====== */
		  glp_prob *lp;
		  int ia[300+1], ja[300+1]; // Inciando vetores dos indices das linhas e das colunas, mesmo tamanho para ambos
		  int i,l,j = 0, ci,cj; // Contadores auxiliares 
		  double z,x1,x2,lambda; // Valores de saida
		  double ar[300+1]; //Vetor com os valores para os indices 
		  double sup[300+1]; //Vetor com os valores limites superiores
		  double inf[300+1]; //Vetor com o valores inferiores
		  double soma[100+1][300+1];// Vetor com os valores do arra dos coefientes para colocar as restrições
		  /*======== FIM ========== */


		  /* INICIANDO O LOOP */
		  while (fabs((Qx - lamb_da)) >= 0.001){
				  printf ("Diferença de (Q - lambda) = %lf \n \n",(Qx - lamb_da));	  
				  ++j;
				  i = 3*j;
				  l = j;

 
          /* CREANDO O PROBLEMA  DUAL */
		  ld = glp_create_prob();
		  glp_set_obj_dir(ld,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(ld,1);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld,1,GLP_UP,0.0,5.0);

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld, 3);

		  /* Defindo um limitante das linha(s) */
		  glp_set_col_bnds(ld,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld,3,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(ld,1,5.0 -3*x_1 -2*x_2);
		  glp_set_obj_coef(ld,2,7.0 -1*x_1 -1*x_2);
		  glp_set_obj_coef(ld,3,4.0 -1*x_1 +1*x_2);

		  /* Preechimento dos valores da matriz das restrições */
		  	iia[1] = 1, jja[1] = 1, aar[1] = 1.0; // a[1,1] = 1.0 
		    iia[2] = 1, jja[2] = 2, aar[2] = 4.0; // a[1,2] = 2.0
		    iia[3] = 1, jja[3] = 3, aar[3] = 2.0; // a[1,3] = 3.0

		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld,3,iia,jja,aar);

		  /* Resolve o problema */
		  glp_simplex(ld,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  Q  =  glp_get_obj_val(ld);
		  u1 = glp_get_col_prim(ld,1);
		  u2 = glp_get_col_prim(ld,2);
		  u3 = glp_get_col_prim(ld,3);
		  printf (" Problema Dual Interação : %d \n", j);
		  printf ("Q = %g; u1 = %g; u2 = %g; u3 = %g \n \n \n", Q,u1,u2,u3);

		  /* Atualizando o valor de Q para ser verificado */
		  Qx = Q;

          /* Matriz dos coeficiente */

		  double matriz_variavel[3][3] = {
				 						 {5*u1, -3*u1, -2*u1},
										 {7*u2,  1*u2, -1*u2},
										 {4*u3, -1*u3,  1*u3}};

 
		  /* CREANDO O PROBLEMA PRIMAL */

		  lp = glp_create_prob();
		  glp_set_obj_dir(lp,GLP_MIN);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(lp,l);

  		   /* Número de coluna(s) da matriz */
		  glp_add_cols(lp, 3);

          /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(lp,1,2.0);/* 2*x1 */
		  glp_set_obj_coef(lp,2,2.0);/* 2*x2 */
		  glp_set_obj_coef(lp,3,1.0);/* lambda/5 */

		  /* Definido o limites das colunas por default deixe com zero para a maioria dos problemas de progração Linear */
		  glp_set_col_bnds(lp,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,3,GLP_LO,0.0,0.0);

         /* Preechendo a(s) coluna(s) com os valores que seram utilizados nas restrições */
		 for (cj = 0; cj < 3; cj++){
				 for (ci = 0; ci < 3; ci++){
						 soma[cj][j-1] += matriz_variavel[ci][cj];
				 }
		 } 

		 /* Os elemento do array soma[][] obtida acima são utilizados nas restrições, use somente para cada interação a mesma coluna j */

                       /* Definindo os limites das linhas */

         /*==========================INICIO==================================== */

		 /* Inferiores:            Superiores: */
		 
 		 		/* Dados para a 1  interação */
		  inf[0] = -100.0,         sup[0] = -soma[0][0]; /* use colunas iguais  */

		       /* Dados para a 2  interação */
		  inf[1] = -100.0,         sup[1] = -soma[0][1]; /* use colunas iguais  */

		       /* Dados para a 3  interação */
		  inf[2] = -100.0,         sup[2] = -soma[0][2]; /* use colunas iguais  */

		       /* Dados para a 4  interação */
		  inf[3] = -100.0,         sup[3] = -soma[0][3]; /* use colunas iguais  */


		       /* Dados para a 5  interação */
		  inf[4] = -100.0,         sup[4] = -soma[0][4]; /* use colunas iguais  */

		  
		       /* Dados para a 6  interação */
		  inf[5] = -100.0,         sup[5] = -soma[0][5]; /* use colunas iguais  */

		       /* Dados para a 7  interação */
		  inf[6] = -100.0,         sup[6] = -soma[0][6]; /* use colunas iguais  */

		       /* Dados para a 8  interação */
		  inf[7] = -100.0,         sup[7] = -soma[0][7]; /* use colunas iguais  */


		       /* Dados para a 9  interação */
		  inf[8] = -100.0,         sup[8] = -soma[0][8]; /* use colunas iguais  */


		       /* Dados para a 10  interação */
		  inf[9] = -100.0,         sup[9] = -soma[0][9]; /* use colunas iguais  */

 		/* ============================FIM===================================== */


 
		  /* Acrescentando as restrições  em que o loop procura o ótimo */

          /* Restrição : 01 */
		  if (j >= 1){	

		  /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,1,GLP_UP,inf[0],sup[0]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[1]  = 1, ja[1]  = 1, ar[1]  =  soma[1][0];
		    ia[2]  = 1, ja[2]  = 2, ar[2]  =  soma[2][0];
		    ia[3]  = 1, ja[3]  = 3, ar[3]  =  -1.0;
		  }
           
		  /* Restrição : 02 */
		  if (j >= 2){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,2,GLP_UP,inf[1],sup[1]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[4]  = 2, ja[4]  = 1, ar[4]  =  soma[1][1]; 
		    ia[5]  = 2, ja[5]  = 2, ar[5]  =  soma[2][1];
		    ia[6]  = 2, ja[6]  = 3, ar[6]  =  -1.0;

		  }
          
		  /* Restrição : 03 */
          if (j >= 3){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,3,GLP_UP,inf[2],sup[2]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[7]  = 3, ja[7]  = 1, ar[7]  =  soma[1][2]; 
		    ia[8]  = 3, ja[8]  = 2, ar[8]  =  soma[2][2];
		    ia[9]  = 3, ja[9]  = 3, ar[9]  =  -1.0;

		  }

		  /* Restrição : 04 */
          if (j >= 4){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,4,GLP_UP,inf[3],sup[3]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[10]  = 4, ja[10]  = 1, ar[10]  =  soma[1][3]; 
		    ia[11]  = 4, ja[11]  = 2, ar[11]  =  soma[2][3];
		    ia[12]  = 4, ja[12]  = 3, ar[12]  =  -1.0;

		  }

		  /* Restrição : 05 */
          if (j >= 5){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,5,GLP_UP,inf[4],sup[4]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[13]  = 5, ja[13]  = 1, ar[13]  =  soma[1][4]; 
		    ia[14]  = 5, ja[14]  = 2, ar[14]  =  soma[2][4];
		    ia[15]  = 5, ja[15]  = 3, ar[15]  =  -1.0;
		  }

		  /* Restrição : 06 */
		  if (j >= 6){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,6,GLP_UP,inf[5],sup[5]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[16]  = 6, ja[16]  = 1, ar[16]  =  soma[1][5]; 
		    ia[17]  = 6, ja[17]  = 2, ar[17]  =  soma[2][5];
		    ia[18]  = 6, ja[18]  = 3, ar[18]  =  -1.0;
		  }
		   
		  /* Restrição : 07 */
		  if (j >= 7){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,7,GLP_UP,inf[6],sup[6]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[19]  = 5, ja[19]  = 1, ar[19]  =  soma[1][6]; 
		    ia[20]  = 5, ja[20]  = 2, ar[20]  =  soma[2][6];
		    ia[21]  = 5, ja[21]  = 3, ar[21]  =  -1.0;
		  }
		  
		  /* Restrição : 08 */ 
		  if (j >= 8){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,8,GLP_UP,inf[7],sup[7]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[22]  = 6, ja[22]  = 1, ar[19]  =  soma[1][7]; 
		    ia[23]  = 6, ja[23]  = 2, ar[20]  =  soma[2][7];
		    ia[24]  = 6, ja[24]  = 3, ar[21]  =  -1.0;
		  }
		  
		  /* Restrição : 09 */
		  if (j >= 9){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,9,GLP_UP,inf[8],sup[8]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[25]  = 7, ja[22]  = 1, ar[25]  =  soma[1][8]; 
		    ia[26]  = 7, ja[23]  = 2, ar[26]  =  soma[2][8];
		    ia[27]  = 7, ja[24]  = 3, ar[27]  =  -1.0;
		  }

		  /* Restrição : 10 */
		  if (j >= 10){

		   /* Definindo os limitantes da linha*/ 
		  glp_set_row_bnds(lp,10,GLP_UP,inf[9],sup[9]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[28]  = 8, ja[28]  = 1, ar[28]  =  soma[1][9]; 
		    ia[29]  = 8, ja[29]  = 2, ar[29]  =  soma[2][9];
		    ia[30]  = 8, ja[30]  = 3, ar[30]  =  -1.0;
		  }


          /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(lp,i,ia,ja,ar);

		  /* Resolve o problema */
		  glp_simplex(lp,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  z = glp_get_obj_val(lp);
		  x1 = glp_get_col_prim(lp,1);
		  x2 = glp_get_col_prim(lp,2);
		  lambda = glp_get_col_prim(lp,3);
		  printf (" Primal interação : %d  \n",j);
		  printf ("z = %g; x1 = %g; x2 = %g; lambda = %g \n \n", z,x1,x2,lambda);

		  
          /* Atualizando os valores */
		  x_1 = x1;
		  x_2 = x2;
		  lamb_da = lambda; 
		  
		  }

		/* Mostrando a convergência */
		 printf("Houve convergência na interação: %d, Erro =  %lf \n \n",j,fabs(Qx - lamb_da));
		 printf("Os pontos ótimos são: \n");
		 printf("x1 = %lf, x2 = %lf, lambda = %lf \n", x_1,x_2, lamb_da);
		 printf("O valor ótimo de z: \n");
		 printf("z = %lf\n \n", z);

         /* Limpeza */
		 glp_delete_prob(lp);
		 glp_delete_prob(ld);
		 glp_free_env();
}

int main(void){
		int d;
		FILE *arq;
		arq = fopen("dados.txt","r");
		while((fscanf(arq, "%d\n",&d))!=EOF){
		PDDE(d);	
		}
		  return 0;

} // Fim da main()

