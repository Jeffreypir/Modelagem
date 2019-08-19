/*
 * ===========================================================================
 *
 *       Filename: L_shaped.c 
 *
 *    Description:  Programação utilizando os mult cortes de Benders, GNU GLPK
 *                  Despacho de energia, progrmação Linear,
 *                  programação estocástica. 
 *                  Viva o linux !!!
 *                  Por que amamos a liberdade.
 *
 *        Version:  0.1
 *        Created:  23-05-2019 19:39:38
 *       Revision:  23-05-2019 19:40:00
 *       Compiler:  gcc
 *
 *         Author:  Jefferson Bezerra dos Santos 
 *
 * ===========================================================================
 */

# include <stdio.h> /* Entrada e saida C */ 
# include <stdlib.h> /* Biblioteca padrão do C */
# include <glpk.h> /*  Gnu GLPK */
# include <math.h>

int main(void){ // Inicio da main ()
	       printf ("INICIO \n");	
		   printf ( "Primal \n");
		   printf (" Chute Inicial: x1 = 0, x2 = 0, lambda_1 = 0, lambda_2 = 0  \n \n"); 


		   /* Definindo o espaço amostral Omega */
		   int Omega[] = {1.2,3.7};

		   /* Definindo a probabilidades assocadas a Omega */ 
		   double probabilidade[] = {1/2,1/2};

		   /* Atualizando x1 é para o cálculo da dual 
		   *
		   * CHUTE INICIAL sem restrições para o problema mestre completo */
		   double x_1 = 0.0,x_2 = 0.0;
		   double lamb_da_1 = 0.0, lamb_da_2 = 0.0;
		   double Q1x = 2.0, Q2x = 5.0;


		  /* PROBLEMA DUAL 1
		   * Declarando as variaveis 
		   *
		   * ======== INICIO ======== */
		  glp_prob *ld_1;
		  int iia_1[30+1], jja_1[30+1];
		  double aar_1[30+1],Q_1;
		  double u1_1,u2_1,u3_1; // O underline final indicar o cenário
		  /* ========= FIM ========== */

          /* PROBLEMA DUAL 2
		   * Declarando as variaveis 
		   *
		   * ======== INICIO ======== */
		  glp_prob *ld_2;
		  int iia_2[30+1], jja_2[30+1];
		  double aar_2[30+1],Q_2;
		  double u1_2,u2_2,u3_2; // O underline final indicar o cenário
		  /* ========= FIM ========== */


		  
           /* PROBLEMA PRIMAL */

          /* Declarando as variaveis 
		   *
		   * ======== INICIO ====== */
		  glp_prob *lp;
		  int ia[130+1], ja[130+1]; // Inciando vetores dos indices das linhas e das colunas, mesmo tamanho para ambos
		  int i,l,j = 0, ci,cj; // Contadores auxiliares 
		  double z,x1,x2,lambda_1,lambda_2; // Valores de saida
		  double ar[130+1]; //Vetor com os valores para os indices 
		  double sup[130+1]; //Vetor com os valores limites superiores
		  double inf[130+1]; //Vetor com o valores inferiores
		  double soma_1[4+1][130+1];// Vetor com os valores do arra dos coefientes para colocar as restrições 1
		  double soma_2[4+1][130+1];// Vetor com os valores do arra dos coefientes para colocar as restrições 2
		  /*======== FIM ========== */


		  /* INICIANDO O LOOP */
		  while (fabs((Q1x - lamb_da_1)) >= 0.001 && fabs((Q2x - lamb_da_2)) >= 0.001 ){
				  printf ("Diferença de (Q_1-lambda_1) = %lf \n \n",(Q1x - lamb_da_1)); 
				  printf ("Diferença de (Q_2-lambda_2) = %lf \n \n",(Q2x - lamb_da_2)); 
				  ++j;
				  i = 2*3*j;
				  l = 2*j;

 
          /* CREANDO O PROBLEMA  DUAL 1
		   *
		   * =========== INICIO ================= */
		  ld_1 = glp_create_prob();
		  glp_set_obj_dir(ld_1,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(ld_1,1);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_1,1,GLP_UP,0.0,5.0);

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_1, 3);

		  /* Defindo um limitante das linha(s) */
		  glp_set_col_bnds(ld_1,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,3,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo para o problema mestre completo*/
		  glp_set_obj_coef(ld_1,1,5.0 -3*x_1 -2*x_2);
		  glp_set_obj_coef(ld_1,2,7.0 -1*x_1 -1*x_2);
		  glp_set_obj_coef(ld_1,3,4.0 -1*x_1 +1*x_2);

		  /* Preechimento dos valores da matriz das restrições */
		  	iia_1[1] = 1, jja_1[1] = 1, aar_1[1] = 1.0; // a[1,1] = 1.0 
		    iia_1[2] = 1, jja_1[2] = 2, aar_1[2] = 4.0; // a[1,2] = 4.0
		    iia_1[3] = 1, jja_1[3] = 3, aar_1[3] = 2.0; // a[1,3] = 2.0

		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld_1,3,iia_1,jja_1,aar_1);

		  /* Resolve o problema */
		  glp_simplex(ld_1,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  Q_1  = glp_get_obj_val(ld_1);
		  u1_1 = glp_get_col_prim(ld_1,1);
		  u2_1 = glp_get_col_prim(ld_1,2);
		  u3_1 = glp_get_col_prim(ld_1,3);

		  /* Atualizando o valor de Q_1 para ser verificado */
		  Q1x = Q_1;

		  /*=================== FIM ======================= */


		  /* CREANDO O PROBLEMA  DUAL 2 
		   * 
		   * ================= INICIO ====================*/

		  ld_2 = glp_create_prob();
		  glp_set_obj_dir(ld_2,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(ld_2,1);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_2,1,GLP_UP,0.0,5.0);

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_2, 3);

		  /* Defindo um limitante das linha(s) */
		  glp_set_col_bnds(ld_2,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,3,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo para o problema mestre completo*/
		  glp_set_obj_coef(ld_2,1,5.0 -3*x_1 -2*x_2);
		  glp_set_obj_coef(ld_2,2,7.0 -1*x_1 -1*x_2);
		  glp_set_obj_coef(ld_2,3,4.0 -1*x_1 +1*x_2);

		  /* Preechimento dos valores da matriz das restrições */
		  	iia_2[1] = 1, jja_2[1] = 1, aar_2[1] = 1.0; // a[1,1] = 1.0 
		    iia_2[2] = 1, jja_2[2] = 2, aar_2[2] = 4.0; // a[1,2] = 4.0
		    iia_2[3] = 1, jja_2[3] = 3, aar_2[3] = 2.0; // a[1,3] = 2.0

		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld_2,3,iia_2,jja_2,aar_2);

		  /* Resolve o problema */
		  glp_simplex(ld_2,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  Q_2  = glp_get_obj_val(ld_2);
		  u1_2 = glp_get_col_prim(ld_2,1);
		  u2_2 = glp_get_col_prim(ld_2,2);
		  u3_2 = glp_get_col_prim(ld_2,3);

		  /* Atualizando o valor de Q_2 para ser verificado */
		  Q2x = Q_2;

		  /*==================== FIM =========================== */


		  /*  Imprimindo os dados */
		  printf (" Problema Dual Interação : %d \n", j);
		  printf ("Q_1 = %g; u1_1 = %g; u2_1 = %g; u3_1 = %g \n \n \n", Q_1,u1_1,u2_1,u3_1);
		  printf ("Q_2 = %g; u1_2 = %g; u2_2 = %g; u3_2 = %g \n \n \n", Q_2,u1_2,u2_2,u3_2);

		  
          /* Matriz dos coeficiente para o dual 1*/
		  double matriz_variavel_1[3][3] = {
				 						 {5*Omega[0]*u1_1, -3*u1_1, -2*u1_1},
										 {7*Omega[0]*u2_1,  1*u2_1, -1*u2_1},
										 {4*Omega[0]*u3_1, -1*u3_1,  1*u3_1}};


		  /* Matriz dos coefiecientes para o dual 2 */
		  double matriz_variavel_2[3][3] = {
				 						 {5*Omega[1]*u1_2, -3*u1_2, -2*u1_2},
										 {7*Omega[1]*u2_2,  1*u2_2, -1*u2_2},
										 {4*Omega[1]*u3_2, -1*u3_2,  1*u3_2}};


 
		  /* CREANDO O PROBLEMA PRIMAL  parei aqui 22-05-2019 18:25:14*/

		  lp = glp_create_prob();
		  glp_set_obj_dir(lp,GLP_MIN);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(lp,l);

  		   /* Número de coluna(s) da matriz */
		  glp_add_cols(lp, 4);

          /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(lp,1,2.0);/* 2*x1 */
		  glp_set_obj_coef(lp,2,2.0);/* 2*x2 */
		  glp_set_obj_coef(lp,3,probabilidade[0]*1.0);/* lambda_1 */
		  glp_set_obj_coef(lp,4,probabilidade[1]*1.0);/* lambda_2 */

		  /* Definido o limites das colunas por default deixe com zero para a maioria dos problemas de progração Linear */
		  glp_set_col_bnds(lp,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,3,GLP_LO,0.0,0.0);

         /* Preechendo a(s) coluna(s) com os valores que seram utilizados nas restrições */
		 for (cj = 0; cj < 3; cj++){
				 for (ci = 0; ci < 3; ci++){
						 soma_1[cj][j-1] += matriz_variavel_1[ci][cj];
						 soma_2[cj][j-1] += matriz_variavel_2[ci][cj];
				 }
		 } 

		 /* Os elemento do array soma[][] obtida acima são utilizados nas restrições, use somente para cada interação a mesma coluna j */

                       /* Definindo os limites das linhas */

         /*==========================INICIO==================================== */

		 /* Inferiores:                  Superiores: */
		 
 		 		/* Dados para a 1  interação  do multi corte */
		  inf[0] = -100.0,          sup[0] = -soma_1[0][0]; /* use colunas iguais  */
		  inf[1] = -100.0,          sup[1] = -soma_2[0][0]; /* use colunas iguais  */

		       /* Dados para a 2  interação do multi cortes */
		  inf[2] = -100.0,          sup[2] = -soma_1[0][1]; /* use colunas iguais  */
		  inf[3] = -100.0,          sup[3] = -soma_2[0][1]; /* use colunas iguais  */


		       /* Dados para a 3  interação do multi cortes */
		  inf[4] = -100.0,          sup[4] = -soma_1[0][2]; /* use colunas iguais  */
		  inf[5] = -100.0,          sup[5] = -soma_2[0][2]; /* use colunas iguais  */


		       /* Dados para a 4  interação do multi cortes */
		  inf[6] = -100.0,          sup[6] = -soma_1[0][3]; /* use colunas iguais  */
		  inf[7] = -100.0,          sup[7] = -soma_2[0][3]; /* use colunas iguais  */


		       /* Dados para a 5  interação do multi cortes */
		  inf[8] = -100.0,          sup[8] = -soma_1[0][4]; /* use colunas iguais  */
		  inf[9] = -100.0,          sup[9] = -soma_2[0][4]; /* use colunas iguais  */

              /* Dados para a 6 interação do multi cortes */
		  inf[10] = -100.0,         sup[10] = -soma_1[0][5]; /* use colunas iguais  */
		  inf[11] = -100.0,         sup[11] = -soma_2[0][5]; /* use colunas iguais  */

		      /* Dados para a 7 interação do multi cortes */
		  inf[12] = -100.0,         sup[12] = -soma_1[0][6]; /* use colunas iguais  */
		  inf[13] = -100.0,         sup[13] = -soma_2[0][6]; /* use colunas iguais  */
		  
		  
		     /* Dados para a 8 interação do multi cortes */
		  inf[14] = -100.0,         sup[14] = -soma_1[0][7]; /* use colunas iguais  */
		  inf[15] = -100.0,         sup[15] = -soma_2[0][7]; /* use colunas iguais  */
		 
		    /* Dados para a 9 interação do multi cortes */
		  inf[16] = -100.0,         sup[16] = -soma_1[0][8]; /* use colunas iguais  */
		  inf[17] = -100.0,         sup[17] = -soma_2[0][8]; /* use colunas iguais  */
		  
			/* Dados para a 10 interação do multi cortes */
		  inf[18] = -100.0,         sup[18] = -soma_1[0][9]; /* use colunas iguais  */
		  inf[19] = -100.0,         sup[19] = -soma_2[0][9]; /* use colunas iguais  */
		  
		  /* Dados para a 11 interação do multi cortes inserindo a limitação */

		  /* ========================= INICIO ===================================== */
		  inf[20] = -100.0,         sup[20] = -Omega[0]*25; /* use colunas iguais  */
		  inf[21] = -100.0,         sup[21] = -Omega[0]*35; /* use colunas iguais  */


		  /* Dados para a 12 interação do multi cortes */
		  inf[22] = -100.0,         sup[22] = -Omega[0]*20; /* use colunas iguais  */
		  inf[23] = -100.0,         sup[23] = -Omega[1]*25; /* use colunas iguais  */
		  
		  /* Dados para a 13 interação do multi cortes */
		  inf[24] = -100.0,         sup[24] = -Omega[1]*35; /* use colunas iguais  */
		  inf[25] = -100.0,         sup[25] = -Omega[1]*20; /* use colunas iguais  */
		  /*========================= FIM ========================================= */

		  /* Dados para a 14 interação do multi cortes */
		  inf[26] = -100.0,         sup[26] =  -soma_1[0][10]; /* use colunas iguais  */
		  inf[27] = -100.0,         sup[27] =  -soma_2[0][10]; /* use colunas iguais  */


		  /* Dados para a 15 interação do multi cortes */
		  inf[28] = -100.0,         sup[28] =  -soma_1[0][11];/* use colunas iguais  */
		  inf[29] = -100.0,         sup[29] =  -soma_2[0][11]; /* use colunas iguais  */

		  /* Dados para a 16 interação do multi cortes */
		  inf[30] = -100.0,         sup[30] =  -soma_1[0][12];/* use colunas iguais  */
		  inf[31] = -100.0,         sup[31] =  -soma_2[0][12]; /* use colunas iguais  */


		  /* Dados para a 17 interação do multi cortes */
		  inf[32] = -100.0,         sup[32] =  -soma_1[0][13];/* use colunas iguais  */
		  inf[33] = -100.0,         sup[33] =  -soma_2[0][13]; /* use colunas iguais  */

		  /* Dados para a 18 interação do multi cortes */
		  inf[34] = -100.0,         sup[34] =  -soma_1[0][14];/* use colunas iguais  */
		  inf[35] = -100.0,         sup[35] =  -soma_2[0][14]; /* use colunas iguais  */
		  
		  /* Dados para a 19 interação do multi cortes */
		  inf[36] = -100.0,         sup[36] =  -soma_1[0][15];/* use colunas iguais  */
		  inf[37] = -100.0,         sup[37] =  -soma_2[0][15]; /* use colunas iguais  */

		  /* Dados para a 20 interação do multi cortes */
		  inf[38] = -100.0,         sup[38] =  -soma_1[0][16];/* use colunas iguais  */
		  inf[39] = -100.0,         sup[39] =  -soma_2[0][16]; /* use colunas iguais  */

 		/* ============================== FIM ========================================== */


 
		  /* Acrescentando as restrições  em que o loop procura o ótimo */

          /* Multi corte 1 */
		  if (j >= 1){	

		  /* Definindo os limitantes da linha 1 para o Q1*/ 
		  glp_set_row_bnds(lp,1,GLP_UP,inf[0],sup[0]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[1]  = 1, ja[1]  = 1, ar[1]  =  soma_1[1][0];
		    ia[2]  = 1, ja[2]  = 2, ar[2]  =  soma_1[2][0];
		    ia[3]  = 1, ja[3]  = 3, ar[3]  =  -1.0;

		  /* Definindo os limitantes da linha 2 para o Q2*/ 
		  glp_set_row_bnds(lp,2,GLP_UP,inf[1],sup[1]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[4]  = 2, ja[4]  = 1, ar[4]  =  soma_2[1][0]; 
		    ia[5]  = 2, ja[5]  = 2, ar[5]  =  soma_2[2][0];
		    ia[6]  = 2, ja[6]  = 3, ar[6]  =  -1.0;

		  }
           
		  if (j >= 2){

		  /* Definindo os limitantes da linha 3 para o Q1*/ 
		  glp_set_row_bnds(lp,3,GLP_UP,inf[2],sup[2]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[7]  = 3, ja[7]  = 1, ar[7]  =  soma_1[1][1];
		    ia[8]  = 3, ja[8]  = 2, ar[8]  =  soma_1[2][1];
		    ia[9]  = 3, ja[9]  = 3, ar[9]  =  -1.0;

		  /* Definindo os limitantes da linha 4 para o Q2*/ 
		  glp_set_row_bnds(lp,4,GLP_UP,inf[3],sup[3]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[10]  = 4, ja[10]  = 1, ar[10]  =  soma_2[1][1]; 
		    ia[11]  = 4, ja[11]  = 2, ar[11]  =  soma_2[2][1];
		    ia[12]  = 4, ja[12]  = 3, ar[12]  =  -1.0;

		  }
          
          if (j >= 3){

		  /* Definindo os limitantes da linha 5 para o Q1*/ 
		  glp_set_row_bnds(lp,5,GLP_UP,inf[4],sup[4]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[13]  = 5, ja[13]  = 1, ar[13]  =  soma_1[1][2];
		    ia[14]  = 5, ja[14]  = 2, ar[14]  =  soma_1[2][2];
		    ia[15]  = 5, ja[15]  = 3, ar[15]  =  -1.0;

			 /* Definindo os limitantes da linha 6 para o Q2*/ 
		  glp_set_row_bnds(lp,6,GLP_UP,inf[5],sup[5]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[16]  = 6, ja[16]  = 1, ar[16]  =  soma_2[1][2]; 
		    ia[17]  = 6, ja[17]  = 2, ar[17]  =  soma_2[2][2];
		    ia[18]  = 6, ja[18]  = 3, ar[18]  =  -1.0;
		  }

          if (j >= 4){

		  /* Definindo os limitantes da linha 7 para o Q1*/ 
		  glp_set_row_bnds(lp,7,GLP_UP,inf[6],sup[6]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[19]  = 7, ja[19]  = 1, ar[19]  =  soma_1[1][3];
		    ia[20]  = 7, ja[20]  = 2, ar[20]  =  soma_1[2][3];
		    ia[21]  = 7, ja[21]  = 3, ar[21]  =  -1.0;

			 /* Definindo os limitantes da linha 8 para o Q2*/ 
		  glp_set_row_bnds(lp,8,GLP_UP,inf[7],sup[7]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[22]  = 8, ja[22]  = 1, ar[22]  =  soma_2[1][3]; 
		    ia[23]  = 8, ja[23]  = 2, ar[23]  =  soma_2[2][3];
		    ia[24]  = 8, ja[24]  = 3, ar[24]  =  -1.0;
		  }

          if (j >= 5){

		  /* Definindo os limitantes da linha 9 para o Q1*/ 
		  glp_set_row_bnds(lp,9,GLP_UP,inf[8],sup[8]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[25]  = 9, ja[25]  = 1, ar[25]  =  soma_1[1][4];
		    ia[26]  = 9, ja[26]  = 2, ar[26]  =  soma_1[2][4];
		    ia[27]  = 9, ja[27]  = 3, ar[27]  =  -1.0;

			 /* Definindo os limitantes da linha 10 para o Q2*/ 
		  glp_set_row_bnds(lp,10,GLP_UP,inf[9],sup[9]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[28]  = 10, ja[28]  = 1, ar[28]  =  soma_2[1][4]; 
		    ia[29]  = 10, ja[29]  = 2, ar[29]  =  soma_2[2][4];
		    ia[30]  = 10, ja[30]  = 3, ar[30]  =  -1.0;
		  }

		  if (j >= 6){

          /* Definindo os limitantes da linha 11 para o Q1*/ 
		  glp_set_row_bnds(lp,11,GLP_UP,inf[10],sup[10]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[31]  = 11, ja[31]  = 1, ar[31]  =  soma_1[1][5];
		    ia[32]  = 11, ja[32]  = 2, ar[32]  =  soma_1[2][5];
		    ia[33]  = 11, ja[33]  = 3, ar[33]  =  -1.0;

			 /* Definindo os limitantes da linha 12 para o Q2*/ 
		  glp_set_row_bnds(lp,12,GLP_UP,inf[11],sup[11]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[34]  = 12, ja[34]  = 1, ar[34]  =  soma_2[1][5]; 
		    ia[35]  = 12, ja[35]  = 2, ar[35]  =  soma_2[2][5];
		    ia[36]  = 12, ja[36]  = 3, ar[36]  =  -1.0;
		  }
		   
		  if (j >= 7){

		  /* Definindo os limitantes da linha 13 para o Q1*/ 
		  glp_set_row_bnds(lp,13,GLP_UP,inf[12],sup[12]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[37]  = 13, ja[37]  = 1, ar[37]  =  soma_1[1][6];
		    ia[38]  = 13, ja[38]  = 2, ar[38]  =  soma_1[2][6];
		    ia[39]  = 13, ja[39]  = 3, ar[39]  =  -1.0;

		  /* Definindo os limitantes da linha 14 para o Q2*/ 
		  glp_set_row_bnds(lp,14,GLP_UP,inf[13],sup[13]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[40]  = 14, ja[40]  = 1, ar[40]  =  soma_2[1][6]; 
		    ia[41]  = 14, ja[41]  = 2, ar[41]  =  soma_2[2][6];
		    ia[42]  = 14, ja[42]  = 3, ar[42]  =  -1.0;
		  }
		  
		  if (j >= 8){

		  /* Definindo os limitantes da linha 15 para o Q1*/ 
		  glp_set_row_bnds(lp,15,GLP_UP,inf[14],sup[14]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[43]  = 15, ja[43]  = 1, ar[43]  =  soma_1[1][7];
		    ia[44]  = 15, ja[44]  = 2, ar[44]  =  soma_1[2][7];
		    ia[45]  = 15, ja[45]  = 3, ar[45]  =  -1.0;

		  /* Definindo os limitantes da linha 16 para o Q2*/ 
		  glp_set_row_bnds(lp,16,GLP_UP,inf[15],sup[15]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[46]  = 16, ja[46]  = 1, ar[46]  =  soma_2[1][7]; 
		    ia[47]  = 16, ja[47]  = 2, ar[47]  =  soma_2[2][7];
		    ia[48]  = 16, ja[48]  = 3, ar[48]  =  -1.0;
		  }
		  
		  if (j >= 9){
		
		   /* Definindo os limitantes da linha 17 para o Q1*/ 
		  glp_set_row_bnds(lp,17,GLP_UP,inf[16],sup[16]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[49]  = 17, ja[49]  = 1, ar[49]  =  soma_1[1][8];
		    ia[50]  = 17, ja[50]  = 2, ar[50]  =  soma_1[2][8];
		    ia[51]  = 17, ja[51]  = 3, ar[51]  =  -1.0;

		  /* Definindo os limitantes da linha 18 para o Q2*/ 
		  glp_set_row_bnds(lp,18,GLP_UP,inf[17],sup[17]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[52]  = 18, ja[52]  = 1, ar[52]  =  soma_2[1][8]; 
		    ia[53]  = 18, ja[53]  = 2, ar[53]  =  soma_2[2][8];
		    ia[54]  = 18, ja[54]  = 3, ar[54]  =  -1.0;
		  }

		  if (j >= 10){
			
		   /* Definindo os limitantes da linha 19 para o Q1*/ 
		  glp_set_row_bnds(lp,19,GLP_UP,inf[18],sup[18]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[55]  = 19, ja[55]  = 1, ar[55]  =  soma_1[1][9];
		    ia[56]  = 19, ja[56]  = 2, ar[56]  =  soma_1[2][9];
		    ia[57]  = 19, ja[57]  = 3, ar[57]  =  -1.0;

		  /* Definindo os limitantes da linha 20 para o Q2*/ 
		  glp_set_row_bnds(lp,20,GLP_UP,inf[19],sup[19]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[58]  = 20, ja[58]  = 1, ar[58]  =  soma_1[1][9]; 
		    ia[59]  = 20, ja[59]  = 2, ar[59]  =  soma_2[2][9];
		    ia[60]  = 20, ja[60]  = 3, ar[60]  =  -1.0;
		  }

		  if (j >= 11){
			
		   /* Definindo os limitantes da linha 21 para o Q1*/ 
		  glp_set_row_bnds(lp,21,GLP_UP,inf[20],sup[20]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[61]  = 21, ja[61]  = 1, ar[61]  =  -75.0;
		    ia[62]  = 21, ja[62]  = 2, ar[62]  =  -10.0;
		    ia[63]  = 21, ja[63]  = 3, ar[63]  =   0.0;

		  /* Definindo os limitantes da linha 22 para o Q2*/ 
		  glp_set_row_bnds(lp,22,GLP_UP,inf[21],sup[21]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[64]  = 22, ja[64]  = 1, ar[64]  =   5.0; 
		    ia[65]  = 22, ja[65]  = 2, ar[65]  =  -10.0;
		    ia[66]  = 22, ja[66]  = 3, ar[66]  =   0.0;
		  }
		 
		  if (j >= 12){
			
		   /* Definindo os limitantes da linha 23 para o Q1*/ 
		  glp_set_row_bnds(lp,23,GLP_UP,inf[22],sup[22]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[67]  = 23, ja[67]  = 1, ar[67]  =  -5.0;
		    ia[68]  = 23, ja[68]  = 2, ar[68]  =   5.0;
		    ia[69]  = 23, ja[69]  = 3, ar[69]  =   0.0;

		  /* Definindo os limitantes da linha 24 para o Q2*/ 
		  glp_set_row_bnds(lp,24,GLP_UP,inf[23],sup[23]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[70]  = 24, ja[70]  = 1, ar[70]  =  -75.0; 
		    ia[71]  = 24, ja[71]  = 2, ar[71]  =  -10.0;
		    ia[72]  = 24, ja[72]  = 3, ar[72]  =   0.0;
		  }
		  
		  if (j >= 13){
			
		   /* Definindo os limitantes da linha 25 para o Q1*/ 
		  glp_set_row_bnds(lp,25,GLP_UP,inf[24],sup[24]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[73]  = 25, ja[73]  = 1, ar[73]  =    5.0;
		    ia[74]  = 25, ja[74]  = 2, ar[74]  =  -10.0;
		    ia[75]  = 25, ja[75]  = 3, ar[75]  =    0.0;

		  /* Definindo os limitantes da linha 26 para o Q2*/ 
		  glp_set_row_bnds(lp,26,GLP_UP,inf[25],sup[25]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[76]  = 26, ja[76]  = 1, ar[76]  =  -5.0; 
		    ia[77]  = 26, ja[77]  = 2, ar[77]  =   5.0;
		    ia[78]  = 26, ja[78]  = 3, ar[78]  =   0.0;
		  }

		  if (j >= 14){
			
		   /* Definindo os limitantes da linha 27 para o Q1*/ 
		  glp_set_row_bnds(lp,27,GLP_UP,inf[26],sup[26]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[79]  = 27, ja[79]  = 1, ar[79]  =  soma_1[1][10];
		    ia[80]  = 27, ja[80]  = 2, ar[80]  =  soma_1[2][10]; 
		    ia[81]  = 27, ja[81]  = 3, ar[81]  =    -1.0;

		  /* Definindo os limitantes da linha 28 para o Q2*/ 
		  glp_set_row_bnds(lp,28,GLP_UP,inf[27],sup[27]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[82]  = 28, ja[82]  = 1, ar[82]  =   soma_2[1][10];
		    ia[83]  = 28, ja[83]  = 2, ar[83]  =   soma_2[2][10];
		    ia[84]  = 28, ja[84]  = 3, ar[84]  =   -1.0;
		  }

		  if (j >= 15){
			
		   /* Definindo os limitantes da linha 29 para o Q1*/ 
		  glp_set_row_bnds(lp,29,GLP_UP,inf[28],sup[28]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[85]  = 29, ja[85]  = 1, ar[85]  =  soma_1[1][11];
		    ia[86]  = 29, ja[86]  = 2, ar[86]  =  soma_1[2][11]; 
		    ia[87]  = 29, ja[87]  = 3, ar[87]  =    -1.0;

		  /* Definindo os limitantes da linha 30 para o Q2*/ 
		  glp_set_row_bnds(lp,30,GLP_UP,inf[29],sup[29]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[88]  = 30, ja[88]  = 1, ar[88]  =   soma_2[1][11];
		    ia[89]  = 30, ja[89]  = 2, ar[89]  =   soma_2[2][11];
		    ia[90]  = 30, ja[90]  = 3, ar[90]  =   -1.0;

		  }

		  if (j >= 16){
			
		   /* Definindo os limitantes da linha 31 para o Q1*/ 
		  glp_set_row_bnds(lp,31,GLP_UP,inf[30],sup[30]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[91]  = 31, ja[91]  = 1, ar[91]  =  soma_1[1][12];
		    ia[92]  = 31, ja[92]  = 2, ar[92]  =  soma_1[2][12]; 
		    ia[93]  = 31, ja[93]  = 3, ar[93]  =    -1.0;

		  /* Definindo os limitantes da linha 32 para o Q2*/ 
		  glp_set_row_bnds(lp,32,GLP_UP,inf[31],sup[31]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[94]  = 32, ja[94]  = 1, ar[94]  =   soma_2[1][12];
		    ia[95]  = 32, ja[95]  = 2, ar[95]  =   soma_2[2][12];
		    ia[96]  = 32, ja[96]  = 3, ar[96]  =   -1.0;
		  }
		  
		  if (j >= 17){
			
		   /* Definindo os limitantes da linha 33 para o Q1*/ 
		  glp_set_row_bnds(lp,33,GLP_UP,inf[32],sup[32]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[97]  = 33, ja[97]  = 1, ar[97]  =  soma_1[1][13];
		    ia[98]  = 33, ja[98]  = 2, ar[98]  =  soma_1[2][13]; 
		    ia[99]  = 33, ja[99]  = 3, ar[99]  =    -1.0;

		  /* Definindo os limitantes da linha 34 para o Q2*/ 
		  glp_set_row_bnds(lp,34,GLP_UP,inf[33],sup[33]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[100]  = 34, ja[100]  = 1, ar[100]  =   soma_2[1][13];
		    ia[101]  = 34, ja[101]  = 2, ar[101]  =   soma_2[2][13];
		    ia[102]  = 34, ja[102]  = 3, ar[102]  =   -1.0;
		  }
		 
		  if (j >= 18){
			
		   /* Definindo os limitantes da linha 35 para o Q1*/ 
		  glp_set_row_bnds(lp,35,GLP_UP,inf[34],sup[34]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[103]  = 35, ja[103]  = 1, ar[103]  =  soma_1[1][14];
		    ia[104]  = 35, ja[104]  = 2, ar[104]  =  soma_1[2][14]; 
		    ia[105]  = 35, ja[105]  = 3, ar[105]  =    -1.0;

		  /* Definindo os limitantes da linha 36 para o Q2*/ 
		  glp_set_row_bnds(lp,36,GLP_UP,inf[35],sup[35]); 


		  /* Preechimento dos valores da matriz das restrições */
		  	ia[106]  = 36, ja[106]  = 1, ar[106]  =   soma_2[1][14];
		    ia[107]  = 36, ja[107]  = 2, ar[107]  =   soma_2[2][14];
		    ia[108]  = 36, ja[108]  = 3, ar[108]  =   -1.0;
		  }

		  if (j >= 19){
			
		   /* Definindo os limitantes da linha 37 para o Q1*/ 
		  glp_set_row_bnds(lp,37,GLP_UP,inf[36],sup[36]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[109]  = 37, ja[109]  = 1, ar[109]  =  soma_1[1][15];
		    ia[110]  = 37, ja[110]  = 2, ar[110]  =  soma_1[2][15]; 
		    ia[111]  = 37, ja[111]  = 3, ar[111]  =    -1.0;

		  /* Definindo os limitantes da linha 38 para o Q2*/ 
		  glp_set_row_bnds(lp,38,GLP_UP,inf[37],sup[37]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[112]  = 38, ja[112]  = 1, ar[112]  =   soma_2[1][15];
		    ia[113]  = 38, ja[113]  = 2, ar[113]  =   soma_2[2][15];
		    ia[114]  = 38, ja[114]  = 3, ar[114]  =   -1.0;
		  }

		  if (j >= 20){
			
		   /* Definindo os limitantes da linha 39 para o Q1*/ 
		  glp_set_row_bnds(lp,39,GLP_UP,inf[38],sup[38]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[115]  = 39, ja[115]  = 1, ar[115]  =  soma_1[1][16];
		    ia[116]  = 39, ja[116]  = 2, ar[116]  =  soma_1[2][16]; 
		    ia[117]  = 39, ja[117]  = 3, ar[117]  =    -1.0;

		  /* Definindo os limitantes da linha 40 para o Q2*/ 
		  glp_set_row_bnds(lp,40,GLP_UP,inf[39],sup[39]); 

		  /* Preechimento dos valores da matriz das restrições */
		  	ia[118]  = 40, ja[118]  = 1, ar[118]  =   soma_2[1][16];
		    ia[119]  = 40, ja[119]  = 2, ar[119]  =   soma_2[2][16];
		    ia[120]  = 40, ja[120]  = 3, ar[120]  =   -1.0;
		  }


          /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(lp,i,ia,ja,ar);

		  /* Resolve o problema */
		  glp_simplex(lp,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  z = glp_get_obj_val(lp);
		  x1 = glp_get_col_prim(lp,1);
		  x2 = glp_get_col_prim(lp,2);
		  lambda_1 = glp_get_col_prim(lp,3);
		  lambda_2 = glp_get_col_prim(lp,4);
		  printf (" Primal interação : %d  \n",j);
		  printf ("z = %g; x1 = %g; x2 = %g; lambda_1 = %g ; lambda_2 = %g\n \n", z,x1,x2,lambda_1,lambda_2);

		  
          /* Atualizando os valores */
		  x_1 = x1;
		  x_2 = x2;
		  lamb_da_1 = lambda_1; 
		  lamb_da_2 = lambda_2; 

		  }

		/* Mostrando a convergência */
		 printf("Houve convergência na interação: %d, Erro =  %lf \n \n",j,fabs(Q1x - lamb_da_1));
		 printf("Os pontos ótimos são: \n");
		 printf("x1 = %lf, x2 = %lf, lambda_1 = %lf, lambda_2 = %lf \n", x_1,x_2, lamb_da_1,lamb_da_2);
		 printf("O valor ótimo de z: \n");
		 printf("z = %lf\n \n", z);

         /* Limpeza */
		 glp_delete_prob(lp);
		 glp_delete_prob(ld_1);
		 glp_free_env();

		  return 0;

} // Fim da main()


