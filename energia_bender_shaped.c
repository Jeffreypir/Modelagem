/*
 * =================================================================
 *
 *       Filename: energia_bender_shaped.c 
 *
 *    Description:  Programação utilizando os mult cortes de Benders,
 *                  GNU GLPK
 *                  Despacho de energia, progrmação Linear,
 *                  programação estocástica. 
 *                  Viva o linux !!!
 *                  Por que amamos a liberdade.
 *
 *        Version:  0.1
 *        Created:  21-05-2019 11:05:42
 *       Revision:  17-06-2019 12:08:37  
 *       Compiler:  gcc -Wall filename.c -lglpk -o filename
 *
 *         Author:  Jefferson Bezerra dos Santos 
 *
 * ==================================================================
 */

# include <stdio.h>  /* Entrada e saida C */ 
# include <string.h>
# include <stdlib.h> /* Biblioteca padrão do C */
# include <glpk.h>   /*  Gnu GLPK */
# include <math.h>   /* math */
# define ERRO 0.01   /* Erro associado */

void PDDE(double dem, double prod, double pb){
				                            /* PROBABILIDADE ASSOCIADA AOS CENARIOS */
		   /*=======================================================================================================*/

		                                /* C1 + C2 + ... Cn = 1 */ 
		   double C1 = pb,C2 = 1-pb;                    
          /*========================================================================================================*/

	      		                           /* CHUTE viável */

		                               /*DEFINIDO O ESTAGIO: 1*/
		   /* ================================= INICIO ============================================================ */
		   /* Vazões turbinadas e vertidas das Usinas no estágio 1 */
		   double VTH1S1 = 50000,VVH1S1 = 10000.0,VTH2S1 = 30000.0, VVH2S1 = 10000.0; 

           /* Definindo a produtibilidade(s) da(s) Usina(s) */
		   double PRODUTIBILIDADE[2] = {1.0,prod};

		   /* Atividade das térmicas associadas as Hidroletricas 1 e 2 respectivamente */
		   double G1 = 0.0, G2 = 0.0; 

		   /* Definido a demanda a ser atingida 1 estagio */
		   double DEMANDAs1[2]= {dem,10000};

		   /* Definindo os volumes máximos da(s) hidroelétrias */
		   double VOL1 = 900000.0;
		   double VOL2 = 90000.0;

		   /* Definindo o volume incremental da Usina hidroelétrica 1 */
		   double VOLI1 = 50000.0;

		   /* Definindo o volume incremental da Usina hidroelétrica 2 */
		   double VOLI2 = VVH1S1;
		  
		   /* Definindo o volume inicial das Usinas */
		   double VINH1 = 40000.0;  // Hidroeletrica 1
		   double VINH2 = 40000.0;  // Hidroeletrica 2


		   /* Definindo o vetor de custo para o 1 estágio 1 */
		   double Cs1[6] = {2, 1.0, 5.0, 1.0, 3.0, 6.0};
		   /*=================================== FIM ============================================================= */

		                              /* DEFININDO O CENARIO 1: */
		   /*================================= INICIO ============================================================ */
		   /* Definindo o volume incremental da Usina hidroelétrica 1 */
		   double VOLI1_1 = 1000.0;

		   /* Definindo o volume incremental da Usina hidroelétrica 2 */
		   double VOLI2_1 = VVH1S1;
		  
		    /* Definindo o volume inicial das Usinas */
		   double VINH1_1 = 80000.0;  // Hidroeletrica 1
		   double VINH2_1 = 70000.0;  // Hidroeletrica 2
		   /*=================================== FIM ============================================================= */

		                            /* DEFININDO O 2 ESTAGIO CENARIO 1 */
		   /*==================================== INICIO ========================================================= */
		   /* Definido a demanda a ser atingida 2 estagio */
		   double DEMANDAs2_1[2]= {400.0,300.0};

		   /* Dfinindo a variável auxiliar para guardar o valor do primal*/
		   double ALFA1_1 = 5000.0; 

		   /* Definindo a variavel auxiliar para guardar o valor do dual */ 
		   double ALFA1_1X = 10000.0;

		   /* Definindo os duais para a atualização */
		   double u1_1 = 0, u2_1 = 0, u3_1 = 0, u4_1 = 0, u5_1 = 0, u6_1 = 0;

		   /* Matriz dos coeficiente para a atualização dual */
		   double matriz_variavel_1[6][3]; 
		  /*==================================== FIM ============================================================= */

		                            /* DEFININDO O CENARIO 2: */
		   /*================================= INICIO ============================================================ */
		   /* Definindo o volume incremental da Usina hidroelétrica 1 */
		   double VOLI1_2 = 20000.0;

		   /* Definindo o volume incremental da Usina hidroelétrica 2 */
		   double VOLI2_2 = VVH1S1;
		  
		    /* Definindo o volume inicial das Usinas */
		   double VINH1_2 = 60000.0;  // Hidroeletrica 1
		   double VINH2_2 = 50000.0;  // Hidroeletrica 2
		   /*=================================== FIM ============================================================= */

		                            /* DEFININDO O 2 ESTAGIO CENARIO 2 */
		   /*==================================== INICIO ========================================================= */
		   /* Definido a demanda a ser atingida 2 estagio */
		   double DEMANDAs2_2[2]= {500.0,200.0};

		   /* Definindo a variável auxiliar para guardar o valor do primal*/
		   double ALFA1_2 = 4.0000; 

		   /* Definindo a variavel auxiliar para guardar o valor do dual */ 
		   double ALFA1_2X = 10000.0;

		   /* Definindo os duais para a atualização */
		   double u1_2 = 0, u2_2 = 0, u3_2 = 0, u4_2 = 0, u5_2 = 0, u6_2 = 0;

		   /* Matriz dos coeficiente para a atualização dual */
		   double matriz_variavel_2[6][3]; 
		  /*==================================== FIM ============================================================= */


		                /* ATIVIDADE DAS TERMICAS ASSOCIADAS A HIFROELETRICA 1 E 2 RESPECTIVAMENTE */ 
		                            /* VARIAVIES COMUNS PARA OS CENARIOS */
		   /*=================================== INICIO =============================================================*/
		   /*Limite de operação das térmicas */
		   double TERMICAS = 400;

		   /* Dfinindo o vetor de custo para o 2 estágio 2 */ 
		   double Cs2[6] = {1.0, 1.0, 1.0, 1.0, 2.5, 2.0};
		   /*================================= FIM =================================================================*/

		                          /* AMOSTRANDO OS DADOS PARA O CENARIO 1*/
		   /*==================================== INICIO ========================================================= */
		   printf ("INICIO \n");	
		   printf ("Primal \n");
		   printf ("Chute viável hidroelétrica 1 e 2 no estágio 1: \n"); 
		   printf ("VTH1S1 = %lf,VVH1S1 = %lf,VTH2S1 = %lf,VVH2S1 = %lf \n\n",VTH1S1,VVH1S1,VTH2S1,VVH2S1); 
		   printf ("Chute viável térmicas no estágio 1: \n");
		   printf ("G1 = %lf, G2 = %lf \n \n", G1,G2); 
		   /*======================================= FIM ======================================================== */
 
		  /* PROBLEMA DUAL CENARIO 1
		   * Declarando as variaveis 
		   *
	       * ======== INICIO ======== */
		  glp_prob *ld_1;
		  int ia_1[200+1], ja_1[200+1];
		  double ar_1[200+1];
		  double u_1[10];
		  /* ========= FIM ========== */

		  /* PROBLEMA DUAL CENARIO 2
		   * Declarando as variaveis 
		   *
	       * ======== INICIO ======== */
		  glp_prob *ld_2;
		  int ia_2[200+1], ja_2[200+1];
		  double ar_2[200+1];
		  double u_2[10];
		  /* ========= FIM ========== */
		  
           /* PROBLEMA PRIMAL */

          /* Declarando as variaveis 
		   *
		   * ======== INICIO ====== */
		  glp_prob *lp;
		  int ia[600+1], ja[600+1];     // Inciando vetores dos indices das linhas e das colunas, mesmo tamanho para ambos
		  int j = 0,ci,cj;              // Contadores auxiliares 
		  double z;                     // Valores de saida
		  double ar[600+1];             // Vetor com os valores para os indices 
		  double sup_1[500+1];          // Vetor com os valores limites superiores para o cenário 1
		  double sup_2[500+1];          // vetor com os valores limites superiores para o cenário 2 
		  double inf_1[500+1];          // Vetor com os valores limites inferiores para o cenário 1  
		  double inf_2[500+1];          // Vetor com os valores limites inferiores para o cenário 2
		  double soma_1[500+1][500+1];  // Vetor com os valores do array dos coeficientes para colocar as restrições para cenário 1
		  double soma_2[500+1][500+1];  // Vetor com os valores do array dos coeficientes para colocar as restrições para cenário 2 
		  /*======== FIM ========== */


		  /* INICIANDO O LOOP */ 
		  while (fabs(ALFA1_1X - ALFA1_1) >= ERRO && fabs(ALFA1_2X - ALFA1_2) >= ERRO ){
				  j++; 
				  printf ("Diferença de (ALFA1_1x - ALFA1_1) = %lf \n \n",fabs((ALFA1_1X - ALFA1_1)));	  
				  printf ("Diferença de (ALFA1_2x - ALFA1_2) = %lf \n \n",fabs((ALFA1_2X - ALFA1_2)));	  
 
                                  /* CREANDO O PROBLEMA  DUAL PARA O CENARIO 1 */
		  /* ====================================== INICIO ===================================================== */
		  ld_1 = glp_create_prob();
		  glp_set_obj_dir(ld_1,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) da matriz */
		  glp_add_rows(ld_1,6);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_1,1,GLP_UP,0.0,Cs2[0]);/* Custo associado a Hidroeletrica 1 vazão turbinada */
		  glp_set_row_bnds(ld_1,2,GLP_UP,0.0,Cs2[1]);/* Custo associado a Hidroeletrica 1 vazão vertida */
		  glp_set_row_bnds(ld_1,3,GLP_UP,0.0,Cs2[2]);/* Custo associado a Hidroeletrica 2 vazão turbinada */
		  glp_set_row_bnds(ld_1,4,GLP_UP,0.0,Cs2[3]);/* Custo associado a Hidroeletrica 2 vazão vertida */
		  glp_set_row_bnds(ld_1,5,GLP_UP,0.0,Cs2[4]);/* Custo associado a Termica 1 */
		  glp_set_row_bnds(ld_1,6,GLP_UP,0.0,Cs2[5]);/* Custo associado a Termica 2 */

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_1,6);

		  /* Defindo um limitante das coluns(s) default 0.0 */
		  glp_set_col_bnds(ld_1,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,6,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(ld_1,1,DEMANDAs2_1[0] + DEMANDAs2_1[1]);
		  glp_set_obj_coef(ld_1,2,-TERMICAS);
		  glp_set_obj_coef(ld_1,3,(-VOL1 + VOLI1_1));
		  glp_set_obj_coef(ld_1,4,(-VOL2 + VOLI2_1));
		  glp_set_obj_coef(ld_1,5,-VINH1_1 - VTH1S1 - VVH1S1);
		  glp_set_obj_coef(ld_1,6,-VINH2_1 - VTH2S1 - VVH2S1);

		  /* Preechimento dos valores da matriz das restrições */

		              /* Definindo a 1 linha */
		  	ia_1[1] = 1, ja_1[1] = 1, ar_1[1] =  PRODUTIBILIDADE[0];   /* a[1,1] */ 
		    ia_1[2] = 1, ja_1[2] = 2, ar_1[2] =  0.0;                  /* a[1,2] */
		    ia_1[3] = 1, ja_1[3] = 3, ar_1[3] =  0.0;                  /* a[1,3] */
		    ia_1[4] = 1, ja_1[4] = 4, ar_1[4] =  PRODUTIBILIDADE[1];   /* a[1,4] */
		    ia_1[5] = 1, ja_1[5] = 5, ar_1[5] =  1.0;                  /* a[1,5] */
		    ia_1[6] = 1, ja_1[6] = 6, ar_1[6] =  1.0;                  /* a[1,6] */

			         /* Definindo a 2 linha */
		  	ia_1[7]  = 2, ja_1[7]  = 1, ar_1[7]  =  0.0;               /* a[2,1] */ 
		    ia_1[8]  = 2, ja_1[8]  = 2, ar_1[8]  =  0.0;               /* a[2,2] */
		    ia_1[9]  = 2, ja_1[9]  = 3, ar_1[9]  =  0.0;               /* a[2,3] */
		    ia_1[10] = 2, ja_1[10] = 4, ar_1[10] =  0.0;               /* a[2,3] */
		    ia_1[11] = 2, ja_1[11] = 5, ar_1[11] = -1.0;               /* a[2,3] */
		    ia_1[12] = 2, ja_1[12] = 6, ar_1[12] = -1.0;               /* a[2,3] */

                      /* Definindo a 3 linha */
		  	ia_1[13] = 3, ja_1[13]  = 1, ar_1[13]  =  1.0;             /* a[3,1] */ 
		    ia_1[14] = 3, ja_1[14]  = 2, ar_1[14]  =  1.0;             /* a[3,2] */
		    ia_1[15] = 3, ja_1[15]  = 3, ar_1[15]  =  0.0;             /* a[3,3] */
		    ia_1[16] = 3, ja_1[16]  = 4, ar_1[16]  =  0.0;             /* a[3,3] */
		    ia_1[17] = 3, ja_1[17]  = 5, ar_1[17]  =  0.0;             /* a[3,3] */
		    ia_1[18] = 3, ja_1[18]  = 6, ar_1[18]  =  0.0;             /* a[3,3] */

			          /* Definindo a 4 linha */
		  	ia_1[19] = 4, ja_1[19]  = 1, ar_1[19]  =  0.0;             /* a[4,1] */ 
		    ia_1[20] = 4, ja_1[20]  = 2, ar_1[20]  =  0.0;             /* a[4,2] */
		    ia_1[21] = 4, ja_1[21]  = 3, ar_1[21]  =  1.0;             /* a[4,3] */
		    ia_1[22] = 4, ja_1[22]  = 4, ar_1[22]  =  1.0;             /* a[4,3] */
		    ia_1[23] = 4, ja_1[23]  = 5, ar_1[23]  =  0.0;             /* a[4,3] */
		    ia_1[24] = 4, ja_1[24]  = 6, ar_1[24]  =  0.0;             /* a[4,3] */

		           	  /* Definindo a 5 linha */
		  	ia_1[25] = 5, ja_1[25]  = 1, ar_1[25]  = -1.0;             /* a[5,1] */ 
		    ia_1[26] = 5, ja_1[26]  = 2, ar_1[26]  = -1.0;             /* a[5,2] */
		    ia_1[27] = 5, ja_1[27]  = 3, ar_1[27]  =  0.0;             /* a[5,3] */
		    ia_1[28] = 5, ja_1[28]  = 4, ar_1[28]  =  0.0;             /* a[5,3] */
		    ia_1[29] = 5, ja_1[29]  = 5, ar_1[29]  =  0.0;             /* a[5,3] */
		    ia_1[30] = 5, ja_1[30]  = 6, ar_1[30]  =  0.0;             /* a[5,3] */

       	              /* Definindo a 6 linha */
		  	ia_1[31] = 6, ja_1[31]  = 1, ar_1[31]  =  0.0;             /* a[6,1] */ 
		    ia_1[32] = 6, ja_1[32]  = 2, ar_1[32]  =  0.0;             /* a[6,2] */
		    ia_1[33] = 6, ja_1[33]  = 3, ar_1[33]  = -1.0;             /* a[6,3] */
		    ia_1[34] = 6, ja_1[34]  = 4, ar_1[34]  = -1.0;             /* a[6,3] */
		    ia_1[35] = 6, ja_1[35]  = 5, ar_1[35]  =  0.0;             /* a[6,3] */
		    ia_1[36] = 6, ja_1[36]  = 6, ar_1[36]  =  0.0;             /* a[6,3] */
	
		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld_1,36,ia_1,ja_1,ar_1);

		  /* Resolve o problema */
		  glp_simplex(ld_1,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  ALFA1_1X  = glp_get_obj_val(ld_1);
		  u_1[0]    = glp_get_col_prim(ld_1,1);
		  u_1[1]    = glp_get_col_prim(ld_1,2);
		  u_1[2]    = glp_get_col_prim(ld_1,3);
		  u_1[3]    = glp_get_col_prim(ld_1,4);
		  u_1[4]    = glp_get_col_prim(ld_1,5);
		  u_1[5]    = glp_get_col_prim(ld_1,6);

	   printf("Problema dual 1 cenário: Interação : %d \n", j);
	   printf("ALFA1_1X = %g;u1_1 = %g;u2_1 = %g u3_1 = %g;u4_1 = %g,u5_1 = %g,u6_1 = %g\n\n",ALFA1_1X,u_1[0],u_1[1],u_1[2],u_1[3],u_1[4],u_1[5]);

		  /* Atualizando o valor de Q para ser verificado */
		  u1_1 = u_1[0];
		  u2_1 = u_1[1];
		  u3_1 = u_1[2];
		  u4_1 = u_1[3];
		  u5_1 = u_1[4];
		  u6_1 = u_1[5];

		 /* Atualizando a matriz dos coeficientes */
	 matriz_variavel_1[0][0] = (DEMANDAs2_1[0]+DEMANDAs2_1[1])*u1_1,matriz_variavel_1[0][1] = 0*u1_1      ,matriz_variavel_1[0][2] = 0*u1_1;
     matriz_variavel_1[1][0] = -TERMICAS*u2_1                      ,matriz_variavel_1[1][1] = 0*u2_1      ,matriz_variavel_1[1][2] = 0*u2_1;
   	 matriz_variavel_1[2][0] = (-VOL1 + VOLI1_1)*u3_1              ,matriz_variavel_1[2][1] = 0*u3_1      ,matriz_variavel_1[2][2] = 0*u3_1;
     matriz_variavel_1[3][0] = (-VOL2 + VOLI2_1)*u4_1              ,matriz_variavel_1[3][1] = 0*u4_1      ,matriz_variavel_1[3][2] = 0*u4_1;
	 matriz_variavel_1[4][0] = -VINH1_1*u5_1                       ,matriz_variavel_1[4][1] = -VTH1S1*u5_1,matriz_variavel_1[4][2] = -VVH1S1*u5_1;
	 matriz_variavel_1[5][0] = -VINH2_1*u6_1                       ,matriz_variavel_1[5][1] = -VTH2S1*u6_1,matriz_variavel_1[5][2] = -VVH2S1*u6_1;
	/*========================================================= FIM ========================================================================== */
		
		                                    /* CREANDO O PROBLEMA  DUAL PARA O CENÁRIO 2 */
		/* ===================================================== INICO ======================================================================= */
		  ld_2 = glp_create_prob();
		  glp_set_obj_dir(ld_2,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) da matriz */
		  glp_add_rows(ld_2,6);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_2,1,GLP_UP,0.0,Cs2[0]);/* Custo associado a Hidroeletrica 1 vazão turbinada */
		  glp_set_row_bnds(ld_2,2,GLP_UP,0.0,Cs2[1]);/* Custo associado a Hidroeletrica 1 vazão vertida */
		  glp_set_row_bnds(ld_2,3,GLP_UP,0.0,Cs2[2]);/* Custo associado a Hidroeletrica 2 vazão turbinada */
		  glp_set_row_bnds(ld_2,4,GLP_UP,0.0,Cs2[3]);/* Custo associado a Hidroeletrica 2 vazão vertida */
		  glp_set_row_bnds(ld_2,5,GLP_UP,0.0,Cs2[4]);/* Custo associado a Termica 1 */
		  glp_set_row_bnds(ld_2,6,GLP_UP,0.0,Cs2[5]);/* Custo associado a Termica 2 */

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_2,6);

		  /* Defindo um limitante das coluns(s) default 0.0 */
		  glp_set_col_bnds(ld_2,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,6,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(ld_2,1,DEMANDAs2_2[0] + DEMANDAs2_2[1]);
		  glp_set_obj_coef(ld_2,2,-TERMICAS);
		  glp_set_obj_coef(ld_2,3,(-VOL1 + VOLI1_2));
		  glp_set_obj_coef(ld_2,4,(-VOL2 + VOLI2_2));
		  glp_set_obj_coef(ld_2,5,-VINH1_2 - VTH1S1 - VVH1S1);
		  glp_set_obj_coef(ld_2,6,-VINH2_2 - VTH2S1 - VVH2S1);

		  /* Preechimento dos valores da matriz das restrições */

		              /* Definindo a 1 linha */
		  	ia_2[1] = 1, ja_2[1] = 1, ar_2[1] =  PRODUTIBILIDADE[0];   /* a[1,1]  */ 
		    ia_2[2] = 1, ja_2[2] = 2, ar_2[2] =  0.0;                  /* a[1,2]  */
		    ia_2[3] = 1, ja_2[3] = 3, ar_2[3] =  0.0;                  /* a[1,3]  */
		    ia_2[4] = 1, ja_2[4] = 4, ar_2[4] =  PRODUTIBILIDADE[1];   /* a[1,4]  */
		    ia_2[5] = 1, ja_2[5] = 5, ar_2[5] =  1.0;                  /* a[1,5]  */
		    ia_2[6] = 1, ja_2[6] = 6, ar_2[6] =  1.0;                  /* a[1,6]  */

			         /* Definindo a 2 linha */
		  	ia_2[7]  = 2, ja_2[7]  = 1, ar_2[7]  =  0.0;               /* a[2,1]  */ 
		    ia_2[8]  = 2, ja_2[8]  = 2, ar_2[8]  =  0.0;               /* a[2,2]  */
		    ia_2[9]  = 2, ja_2[9]  = 3, ar_2[9]  =  0.0;               /* a[2,3]  */
		    ia_2[10] = 2, ja_2[10] = 4, ar_2[10] =  0.0;               /* a[2,3]  */
		    ia_2[11] = 2, ja_2[11] = 5, ar_2[11] = -1.0;               /* a[2,3]  */
		    ia_2[12] = 2, ja_2[12] = 6, ar_2[12] = -1.0;               /* a[2,3]  */

                      /* Definindo a 3 linha */
		  	ia_2[13] = 3, ja_2[13]  = 1, ar_2[13]  =  1.0;             /* a[3,1]  */ 
		    ia_2[14] = 3, ja_2[14]  = 2, ar_2[14]  =  1.0;             /* a[3,2]  */
		    ia_2[15] = 3, ja_2[15]  = 3, ar_2[15]  =  0.0;             /* a[3,3]  */
		    ia_2[16] = 3, ja_2[16]  = 4, ar_2[16]  =  0.0;             /* a[3,3]  */
		    ia_2[17] = 3, ja_2[17]  = 5, ar_2[17]  =  0.0;             /* a[3,3]  */
		    ia_2[18] = 3, ja_2[18]  = 6, ar_2[18]  =  0.0;             /* a[3,3]  */

			          /* Definindo a 4 linha */
		  	ia_2[19] = 4, ja_2[19]  = 1, ar_2[19]  =  0.0;             /* a[4,1]  */ 
		    ia_2[20] = 4, ja_2[20]  = 2, ar_2[20]  =  0.0;             /* a[4,2]  */
		    ia_2[21] = 4, ja_2[21]  = 3, ar_2[21]  =  1.0;             /* a[4,3]  */
		    ia_2[22] = 4, ja_2[22]  = 4, ar_2[22]  =  1.0;             /* a[4,3]  */
		    ia_2[23] = 4, ja_2[23]  = 5, ar_2[23]  =  0.0;             /* a[4,3]  */
		    ia_2[24] = 4, ja_2[24]  = 6, ar_2[24]  =  0.0;             /* a[4,3]  */

		           	  /* Definindo a 5 linha */
		  	ia_2[25] = 5, ja_2[25]  = 1, ar_2[25]  = -1.0;             /* a[5,1]  */ 
		    ia_2[26] = 5, ja_2[26]  = 2, ar_2[26]  = -1.0;             /* a[5,2]  */
		    ia_2[27] = 5, ja_2[27]  = 3, ar_2[27]  =  0.0;             /* a[5,3]  */
		    ia_2[28] = 5, ja_2[28]  = 4, ar_2[28]  =  0.0;             /* a[5,3]  */
		    ia_2[29] = 5, ja_2[29]  = 5, ar_2[29]  =  0.0;             /* a[5,3]  */
		    ia_2[30] = 5, ja_2[30]  = 6, ar_2[30]  =  0.0;             /* a[5,3]  */

       	              /* Definindo a 6 linha */
		  	ia_2[31] = 6, ja_2[31]  = 1, ar_2[31]  =  0.0;             /* a[6,1]  */ 
		    ia_2[32] = 6, ja_2[32]  = 2, ar_2[32]  =  0.0;             /* a[6,2]  */
		    ia_2[33] = 6, ja_2[33]  = 3, ar_2[33]  = -1.0;             /* a[6,3]  */
		    ia_2[34] = 6, ja_2[34]  = 4, ar_2[34]  = -1.0;             /* a[6,3]  */
		    ia_2[35] = 6, ja_2[35]  = 5, ar_2[35]  =  0.0;             /* a[6,3]  */
		    ia_2[36] = 6, ja_2[36]  = 6, ar_2[36]  =  0.0;             /* a[6,3]  */
	
		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld_2,36,ia_2,ja_2,ar_2);

		  /* Resolve o problema */
		  glp_simplex(ld_2,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  ALFA1_2X  = glp_get_obj_val(ld_2);
		  u_2[0]    = glp_get_col_prim(ld_2,1);
		  u_2[1]    = glp_get_col_prim(ld_2,2);
		  u_2[2]    = glp_get_col_prim(ld_2,3);
		  u_2[3]    = glp_get_col_prim(ld_2,4);
		  u_2[4]    = glp_get_col_prim(ld_2,5);
		  u_2[5]    = glp_get_col_prim(ld_2,6);

       printf("Problema Dual Cenário 2: Interação : %d \n", j);
  	   printf("ALFA1_2x = %g;u1_2 = %g;u2_2 = %g;u3_2 = %g;u4_2 = %g,u5_2 = %g,u6_2 = %g\n\n",ALFA1_2X,u_2[0],u_2[1],u_2[2],u_2[3],u_2[4],u_2[5]);

		  /* Atualizando o valor de Q para ser verificado */
		  u1_2 = u_2[0];
		  u2_2 = u_2[1];
		  u3_2 = u_2[2];
		  u4_2 = u_2[3];
		  u5_2 = u_2[4];
		  u6_2 = u_2[5];

		 /* Atualizando a matriz dos coeficientes */
	 matriz_variavel_2[0][0] = (DEMANDAs2_2[0]+DEMANDAs2_2[1])*u1_2,matriz_variavel_2[0][1] =  0*u1_2     ,matriz_variavel_2[0][2] =  0*u1_2;
     matriz_variavel_2[1][0] = -TERMICAS*u2_2                      ,matriz_variavel_2[1][1] =  0*u2_2     ,matriz_variavel_2[1][2] =  0*u2_2;
  	 matriz_variavel_2[2][0] = (-VOL1 + VOLI1_2)*u3_2              ,matriz_variavel_2[2][1] =  0*u3_2     ,matriz_variavel_2[2][2] =  0*u3_2;
     matriz_variavel_2[3][0] = (-VOL2 + VOLI2_2)*u4_2              ,matriz_variavel_2[3][1] =  0*u4_2     ,matriz_variavel_2[3][2] =  0*u4_2;
	 matriz_variavel_2[4][0] = -VINH1_2*u5_2                       ,matriz_variavel_2[4][1] = -VTH1S1*u5_2,matriz_variavel_2[4][2] = -VVH1S1*u5_2;
   	 matriz_variavel_2[5][0] = -VINH2_2*u6_2                       ,matriz_variavel_2[5][1] = -VTH2S1*u6_2,matriz_variavel_2[5][2] = -VVH2S1*u6_2;
	   /*===================================================== FIM =========================================================================== */
 
		                                  /* CREANDO O PROBLEMA PRIMAL */
		/*============================================ INICIO ================================================================================ */
		  lp = glp_create_prob();
		  glp_set_obj_dir(lp,GLP_MIN);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(lp,8 + 2*j);

  		   /* Número de coluna(s) da matriz */
		  glp_add_cols(lp,8);

          /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(lp,1,Cs1[0]);                       /* Custo associado a vazão turbinada Hidroelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,2,Cs1[1]);                       /* Custo associado a vazão vertida   Hidroelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,3,Cs1[2]);                       /* Custo associado a vazão turbinada Hidroelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,4,Cs1[3]);                       /* Custo associado a vazão turbinada Hidroelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,5,Cs1[4]);                       /* Custo associado a termoelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,6,Cs1[5]);                       /* Custo associado a termoelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,7,C1);                           /* Coefiente de alfa1 */
		  glp_set_obj_coef(lp,8,C2);                           /* Coefiente de alfa2 */

          /* Definido o limites das colunas por default deixe com zero para a maioria dos problemas de progração Linear */
		  glp_set_col_bnds(lp,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,6,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,7,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,8,GLP_LO,0.0,0.0);

		  /* Preechendo a(s) coluna(s) com os valores que seram utilizados nas restrições */
		  if (j >= 1){
				  for (cj = 0; cj < 3; cj++){
						  for (ci = 0; ci < 6; ci++){
								  soma_1[cj][j-1] += matriz_variavel_1[ci][cj];
								  soma_2[cj][j-1] += matriz_variavel_2[ci][cj];
						  }
				  } 
				  for (cj = 3; cj <= 6; cj++){
						  soma_1[cj][j-1] = 0;
						  soma_2[cj][j-1] = 0;
				  }
		  }

		 /* Os elemento do array soma[][] obtida acima são utilizados nas restrições, use somente para cada interação a mesma coluna j */

                       /* DEFININDO OS LIMITES DAS LINHAS PARA O CENARIO 1 */

         /*========================== INICIO ==================================== */
		      /* Inferiores:             Superiores: */
		 
 		 		/* Dados para a matriz das restrições */
		  inf_1[0]  = -100.0,         sup_1[0]  = soma_1[0][0];  /* use colunas iguais  */
		  inf_1[1]  = -100.0,         sup_1[1]  = soma_1[0][1];  /* use colunas iguais  */
		  inf_1[2]  = -100.0,         sup_1[2]  = soma_1[0][2];  /* use colunas iguais  */
		  inf_1[3]  = -100.0,         sup_1[3]  = soma_1[0][3];  /* use colunas iguais  */
		  inf_1[4]  = -100.0,         sup_1[4]  = soma_1[0][4];  /* use colunas iguais  */ 
		  inf_1[5]  = -100.0,         sup_1[5]  = soma_1[0][5];  /* use colunas iguais  */
		  inf_1[6]  = -100.0,         sup_1[6]  = soma_1[0][6];  /* use colunas iguais  */
		  inf_1[7]  = -100.0,         sup_1[7]  = soma_1[0][7];  /* use colunas iguais  */
		  inf_1[8]  = -100.0,         sup_1[8]  = soma_1[0][8];  /* use colunas iguais  */
		  inf_1[9]  = -100.0,         sup_1[9]  = soma_1[0][9];  /* use colunas iguais  */
		  inf_1[10] = -100.0,         sup_1[10] = soma_1[0][10]; /* use colunas iguais  */
		  inf_1[11] = -100.0,         sup_1[11] = soma_1[0][11]; /* use colunas iguais  */
		  inf_1[12] = -100.0,         sup_1[12] = soma_1[0][12]; /* use colunas iguais  */
		  inf_1[13] = -100.0,         sup_1[13] = soma_1[0][13]; /* use colunas iguais  */
		  inf_1[14] = -100.0,         sup_1[14] = soma_1[0][14]; /* use colunas iguais  */
		  inf_1[15] = -100.0,         sup_1[15] = soma_1[0][15]; /* use colunas iguais  */
		  inf_1[16] = -100.0,         sup_1[16] = soma_1[0][16]; /* use colunas iguais  */
		  inf_1[17] = -100.0,         sup_1[17] = soma_1[0][17]; /* use colunas iguais  */
		  inf_1[18] = -100.0,         sup_1[18] = soma_1[0][18]; /* use colunas iguais  */
		  inf_1[19] = -100.0,         sup_1[19] = soma_1[0][19]; /* use colunas iguais  */
		  inf_1[20] = -100.0,         sup_1[20] = soma_1[0][20]; /* use colunas iguais  */
		  inf_1[21] = -100.0,         sup_1[21] = soma_1[0][21]; /* use colunas iguais  */
		  inf_1[22] = -100.0,         sup_1[22] = soma_1[0][22]; /* use colunas iguais  */
		  inf_1[23] = -100.0,         sup_1[23] = soma_1[0][23]; /* use colunas iguais  */
		  inf_1[24] = -100.0,         sup_1[24] = soma_1[0][24]; /* use colunas iguais  */
		  inf_1[25] = -100.0,         sup_1[25] = soma_1[0][25]; /* use colunas iguais  */
		  inf_1[26] = -100.0,         sup_1[26] = soma_1[0][26]; /* use colunas iguais  */
		  inf_1[27] = -100.0,         sup_1[27] = soma_1[0][27]; /* use colunas iguais  */
		  inf_1[28] = -100.0,         sup_1[28] = soma_1[0][28]; /* use colunas iguais  */
		  inf_1[29] = -100.0,         sup_1[29] = soma_1[0][29]; /* use colunas iguais  */
		  inf_1[30] = -100.0,         sup_1[30] = soma_1[0][30]; /* use colunas iguais  */
 		/* ============================FIM===================================== */

		             /* DEFININDO OS LIMITES DAS LINHAS PARA O CENARIO 2 */

         /*========================== INICIO ========================================== */
		      /* Inferiores:             Superiores: */
		 
 		 		/* Dados para a matriz das restrições */
		  inf_2[0]  = -100.0,         sup_2[0]  = soma_2[0][0];  /* use colunas iguais  */
		  inf_2[1]  = -100.0,         sup_2[1]  = soma_2[0][1];  /* use colunas iguais  */
		  inf_2[2]  = -100.0,         sup_2[2]  = soma_2[0][2];  /* use colunas iguais  */
		  inf_2[3]  = -100.0,         sup_2[3]  = soma_2[0][3];  /* use colunas iguais  */
		  inf_2[4]  = -100.0,         sup_2[4]  = soma_2[0][4];  /* use colunas iguais  */ 
		  inf_2[5]  = -100.0,         sup_2[5]  = soma_2[0][5];  /* use colunas iguais  */
		  inf_2[6]  = -100.0,         sup_2[6]  = soma_2[0][6];  /* use colunas iguais  */
		  inf_2[7]  = -100.0,         sup_2[7]  = soma_2[0][7];  /* use colunas iguais  */
		  inf_2[8]  = -100.0,         sup_2[8]  = soma_2[0][8];  /* use colunas iguais  */
		  inf_2[9]  = -100.0,         sup_2[9]  = soma_2[0][9];  /* use colunas iguais  */
		  inf_2[10] = -100.0,         sup_2[10] = soma_2[0][10]; /* use colunas iguais  */
		  inf_2[11] = -100.0,         sup_2[11] = soma_2[0][11]; /* use colunas iguais  */
		  inf_2[12] = -100.0,         sup_2[12] = soma_2[0][12]; /* use colunas iguais  */
		  inf_2[13] = -100.0,         sup_2[13] = soma_2[0][13]; /* use colunas iguais  */
		  inf_2[14] = -100.0,         sup_2[14] = soma_2[0][14]; /* use colunas iguais  */
		  inf_2[15] = -100.0,         sup_2[15] = soma_2[0][15]; /* use colunas iguais  */
		  inf_2[16] = -100.0,         sup_2[16] = soma_2[0][16]; /* use colunas iguais  */
		  inf_2[17] = -100.0,         sup_2[17] = soma_2[0][17]; /* use colunas iguais  */
		  inf_2[18] = -100.0,         sup_2[18] = soma_2[0][18]; /* use colunas iguais  */
		  inf_2[19] = -100.0,         sup_2[19] = soma_2[0][19]; /* use colunas iguais  */
		  inf_2[20] = -100.0,         sup_2[20] = soma_2[0][20]; /* use colunas iguais  */
		  inf_2[21] = -100.0,         sup_2[21] = soma_2[0][21]; /* use colunas iguais  */
		  inf_2[22] = -100.0,         sup_2[22] = soma_2[0][22]; /* use colunas iguais  */
		  inf_2[23] = -100.0,         sup_2[23] = soma_2[0][23]; /* use colunas iguais  */
		  inf_2[24] = -100.0,         sup_2[24] = soma_2[0][24]; /* use colunas iguais  */
		  inf_2[25] = -100.0,         sup_2[25] = soma_2[0][25]; /* use colunas iguais  */
		  inf_2[26] = -100.0,         sup_2[26] = soma_2[0][26]; /* use colunas iguais  */
		  inf_2[27] = -100.0,         sup_2[27] = soma_2[0][27]; /* use colunas iguais  */
		  inf_2[28] = -100.0,         sup_2[28] = soma_2[0][28]; /* use colunas iguais  */
		  inf_2[29] = -100.0,         sup_2[29] = soma_2[0][29]; /* use colunas iguais  */
		  inf_2[30] = -100.0,         sup_2[30] = soma_2[0][30]; /* use colunas iguais  */
 		/* ============================FIM============================================= */

 
		  /* Acrescentando as restrições  em que o loop procura o ótimo problema principal */
		  /* Este Algoritmo foi preparado para trabalhar com <= (menor ou igual),
		   * tenha cuidado na contrução do problema dual, para não trabalhar com a matriz
		   * com os sinais trocados */

		  /* Definindo os limitantes da linha 1*/ 
		  glp_set_row_bnds(lp,1,GLP_UP,-100.0,-DEMANDAs1[0]-DEMANDAs1[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 1 */
		  	ia[1]  = 1, ja[1]  = 1, ar[1]  = -PRODUTIBILIDADE[0];               /* a[1,1] */
		    ia[2]  = 1, ja[2]  = 2, ar[2]  =  0.0;                              /* a[1,2] */
		    ia[3]  = 1, ja[3]  = 3, ar[3]  = -PRODUTIBILIDADE[1];               /* a[1,3] */
			ia[4]  = 1, ja[4]  = 4, ar[4]  =  0.0;                              /* a[1,4] */
		    ia[5]  = 1, ja[5]  = 5, ar[5]  = -1.0;                              /* a[1,5] */
		    ia[6]  = 1, ja[6]  = 6, ar[6]  = -1.0;                              /* a[1,6] */
		    ia[7]  = 1, ja[7]  = 7, ar[7]  =  0.0;                              /* a[1,7] */
		    ia[8]  = 1, ja[8]  = 8, ar[8]  =  0.0;                              /* a[1,8] */
 
		  /* Definindo os limitantes da linha 2 */ 
		  glp_set_row_bnds(lp,2,GLP_UP,-100,TERMICAS); 

		  /* Preechimento dos valores da matriz das restrições linha 2 */
		  	ia[9]   = 2, ja[9]   = 1, ar[9]   =  0.0;                          /* a[2,1] */
		    ia[10]  = 2, ja[10]  = 2, ar[10]  =  0.0;                          /* a[2,2] */
		    ia[11]  = 2, ja[11]  = 3, ar[11]  =  0.0;                          /* a[2,3] */
			ia[12]  = 2, ja[12]  = 4, ar[12]  =  0.0;                          /* a[2,4] */
		    ia[13]  = 2, ja[13]  = 5, ar[13]  =  1.0;                          /* a[2,5] */
		    ia[14]  = 2, ja[14]  = 6, ar[14]  =  1.0;                          /* a[2,6] */
		    ia[15]  = 2, ja[15]  = 7, ar[15]  =  0.0;                          /* a[2,7] */
		    ia[16]  = 2, ja[16]  = 8, ar[16]  =  0.0;                          /* a[2,8] */
 
		  /* Definindo os limitantes da linha 3*/ 
		  glp_set_row_bnds(lp,3,GLP_UP,-100.0,(VOL1 - VOLI1)); 

		  /* Preechimento dos valores da matriz das restrições linha 3 */
		  	ia[17]  = 3, ja[17]  = 1, ar[17]  = -1.0;                          /* a[3,1] */
		    ia[18]  = 3, ja[18]  = 2, ar[18]  = -1.0;                          /* a[3,2] */
		    ia[19]  = 3, ja[19]  = 3, ar[19]  =  0.0;                          /* a[3,3] */
			ia[20]  = 3, ja[20]  = 4, ar[20]  =  0.0;                          /* a[3,4] */
		    ia[21]  = 3, ja[21]  = 5, ar[21]  =  0.0;                          /* a[3,5] */
		    ia[22]  = 3, ja[22]  = 6, ar[22]  =  0.0;                          /* a[3,6] */
		    ia[23]  = 3, ja[23]  = 7, ar[23]  =  0.0;                          /* a[3,7] */
		    ia[24]  = 3, ja[24]  = 8, ar[24]  =  0.0;                          /* a[3,8] */
  
		  /* Definindo os limitantes da linha 4 */ 
		  glp_set_row_bnds(lp,4,GLP_UP,-100.0,(VOL2 - VOLI2)); 

		  /* Preechimento dos valores da matriz das restrições linha 4 */
		  	ia[25]  = 4, ja[25]  = 1, ar[25]  =  0.0;                          /* a[4,1] */
		    ia[26]  = 4, ja[26]  = 2, ar[26]  =  0.0;                          /* a[4,2] */
		    ia[27]  = 4, ja[27]  = 3, ar[27]  = -1.0;                          /* a[4,3] */
			ia[28]  = 4, ja[28]  = 4, ar[28]  = -1.0;                          /* a[4,4] */
		    ia[29]  = 4, ja[29]  = 5, ar[29]  =  0.0;                          /* a[4,5] */
		    ia[30]  = 4, ja[30]  = 6, ar[30]  =  0.0;                          /* a[4,6] */
		    ia[31]  = 4, ja[31]  = 7, ar[31]  =  0.0;                          /* a[4,7] */
		    ia[32]  = 4, ja[32]  = 8, ar[32]  =  0.0;                          /* a[4,8] */
  
		   /* Definindo os limitantes da linha 5 */ 
		  glp_set_row_bnds(lp,5,GLP_UP,-100.0,VINH1); 

		  /* Preechimento dos valores da matriz das restrições linha 5 */
		  	ia[33]  = 5, ja[33]  = 1, ar[33]  =  1.0;                          /* a[5,1] */
		    ia[34]  = 5, ja[34]  = 2, ar[34]  =  1.0;                          /* a[5,2] */
		    ia[35]  = 5, ja[35]  = 3, ar[35]  =  0.0;                          /* a[5,3] */
			ia[36]  = 5, ja[36]  = 4, ar[36]  =  0.0;                          /* a[5,4] */
		    ia[37]  = 5, ja[37]  = 5, ar[37]  =  0.0;                          /* a[5,5] */
		    ia[38]  = 5, ja[38]  = 6, ar[38]  =  0.0;                          /* a[5,6] */
		    ia[39]  = 5, ja[39]  = 7, ar[39]  =  0.0;                          /* a[5,7] */
		    ia[40]  = 5, ja[40]  = 8, ar[40]  =  0.0;                          /* a[5,8] */
  
		  /* Definindo os limitantes da linha 6 */ 
		  glp_set_row_bnds(lp,6,GLP_UP,-100.0,VINH2); 

		  /* Preechimento dos valores da matriz das restrições linha 6 */
		  	ia[41]  = 6, ja[41]  = 1, ar[41]  =  0.0;                          /* a[6,1] */
		    ia[42]  = 6, ja[42]  = 2, ar[42]  =  0.0;                          /* a[6,2] */
		    ia[43]  = 6, ja[43]  = 3, ar[43]  =  1.0;                          /* a[6,3] */
			ia[44]  = 6, ja[44]  = 4, ar[44]  =  1.0;                          /* a[6,4] */
		    ia[45]  = 6, ja[45]  = 5, ar[45]  =  0.0;                          /* a[6,5] */
		    ia[46]  = 6, ja[46]  = 6, ar[46]  =  0.0;                          /* a[6,6] */
		    ia[47]  = 6, ja[47]  = 7, ar[47]  =  0.0;                          /* a[6,7] */
		    ia[48]  = 6, ja[48]  = 8, ar[48]  =  0.0;                          /* a[6,8] */

		  /* Restrição : 01 */
		  if (j >= 1){

		   /* Definindo os limitantes da linha 7*/ 
		  glp_set_row_bnds(lp,7,GLP_UP,inf_1[0],-sup_1[0]); 

		  /* Preechimento dos valores da matriz das restrições linha 7 */
		  	ia[49]  = 7, ja[49]  = 1, ar[49]  =  soma_1[1][0];                  /* a[7,1] */
		    ia[50]  = 7, ja[50]  = 2, ar[50]  =  soma_1[2][0];                  /* a[7,2] */
		    ia[51]  = 7, ja[51]  = 3, ar[51]  =  soma_1[3][0];                  /* a[7,3] */
			ia[52]  = 7, ja[52]  = 4, ar[52]  =  soma_1[4][0];                  /* a[7,4] */
		    ia[53]  = 7, ja[53]  = 5, ar[53]  =  soma_1[5][0];                  /* a[7,5] */
		    ia[54]  = 7, ja[54]  = 6, ar[54]  =  soma_1[6][0];                  /* a[7,6] */ 
		    ia[55]  = 7, ja[55]  = 7, ar[55]  = -1.0;                           /* a[7,7] */ 
		    ia[56]  = 7, ja[56]  = 8, ar[56]  =  0.0;                           /* a[7,8] */ 

		  /* Definindo os limitantes da linha 8*/ 
		  glp_set_row_bnds(lp,8,GLP_UP,inf_2[0],-sup_2[0]); 

		  /* Preechimento dos valores da matriz das restrições linha 7 */
		  	ia[57]  = 8, ja[57]  = 1, ar[57]  =  soma_2[1][0];                  /* a[8,1] */
		    ia[58]  = 8, ja[58]  = 2, ar[58]  =  soma_2[2][0];                  /* a[8,2] */
		    ia[59]  = 8, ja[59]  = 3, ar[59]  =  soma_2[3][0];                  /* a[8,3] */
			ia[60]  = 8, ja[60]  = 4, ar[60]  =  soma_2[4][0];                  /* a[8,4] */
		    ia[61]  = 8, ja[61]  = 5, ar[61]  =  soma_2[5][0];                  /* a[8,5] */
		    ia[62]  = 8, ja[62]  = 6, ar[62]  =  soma_2[6][0];                  /* a[8,6] */ 
		    ia[63]  = 8, ja[63]  = 7, ar[63]  =  0.0;                           /* a[8,7] */ 
		    ia[64]  = 8, ja[64]  = 8, ar[64]  = -1.0;                           /* a[8,8] */ 
		  }    

		  /* Restrição : 02 */
		  if (j >= 2){

		   /* Definindo os limitantes da linha 9*/ 
		  glp_set_row_bnds(lp,9,GLP_UP,-100,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 9 */
		  	ia[65]  = 9, ja[65]  = 1, ar[65]  =  soma_1[1][1];                 /* a[9,1] */
		    ia[66]  = 9, ja[66]  = 2, ar[66]  =  soma_1[2][1];                 /* a[9,2] */
		    ia[67]  = 9, ja[67]  = 3, ar[67]  =  soma_1[3][1];                 /* a[9,3] */
			ia[68]  = 9, ja[68]  = 4, ar[68]  =  soma_1[4][1];                 /* a[9,4] */
		    ia[69]  = 9, ja[69]  = 5, ar[69]  =  soma_1[5][1];                 /* a[9,5] */
		    ia[70]  = 9, ja[70]  = 6, ar[70]  =  soma_1[6][1];                 /* a[9,6] */ 
		    ia[71]  = 9, ja[71]  = 7, ar[71]  =  -1.0;                         /* a[9,7] */ 
		    ia[72]  = 9, ja[72]  = 8, ar[72]  =   0.0;                         /* a[9,8] */ 

		  /* Definindo os limitantes da linha 10*/ 
		  glp_set_row_bnds(lp,10,GLP_UP,-100,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 10 */
		    ia[73]  = 10, ja[73]  = 1, ar[73]  =  soma_2[1][1];                 /* a[10,1] */
		    ia[74]  = 10, ja[74]  = 2, ar[74]  =  soma_2[2][1];                 /* a[10,2] */
		    ia[75]  = 10, ja[75]  = 3, ar[75]  =  soma_2[3][1];                 /* a[10,3] */
			ia[76]  = 10, ja[76]  = 4, ar[76]  =  soma_2[4][1];                 /* a[10,4] */
		    ia[77]  = 10, ja[77]  = 5, ar[77]  =  soma_2[5][1];                 /* a[10,5] */
		    ia[78]  = 10, ja[78]  = 6, ar[78]  =  soma_2[6][1];                 /* a[10,6] */ 
		    ia[79]  = 10, ja[79]  = 7, ar[79]  =   0.0;                         /* a[10,7] */ 
		    ia[80]  = 10, ja[80]  = 8, ar[80]  =  -1.0;                         /* a[10,8] */ 
		  	
		  }   

		  /* Restrição : 03 */
		  if (j >= 3){

		   /* Definindo os limitantes da linha 11*/ 
		  glp_set_row_bnds(lp,11,GLP_UP,inf_1[1],-sup_1[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 11 */
		    ia[81]  = 11, ja[81]  = 1, ar[81]  =  soma_2[1][2];                 /* a[11,1] */
		    ia[82]  = 11, ja[82]  = 2, ar[82]  =  soma_2[2][2];                 /* a[11,2] */
		    ia[83]  = 11, ja[83]  = 3, ar[83]  =  soma_2[3][2];                 /* a[11,3] */
			ia[84]  = 11, ja[84]  = 4, ar[84]  =  soma_2[4][2];                 /* a[11,4] */
		    ia[85]  = 11, ja[85]  = 5, ar[85]  =  soma_2[5][2];                 /* a[11,5] */
		    ia[86]  = 11, ja[86]  = 6, ar[86]  =  soma_2[6][2];                 /* a[11,6] */ 
		    ia[87]  = 11, ja[87]  = 7, ar[87]  =  -1.0;                         /* a[11,7] */ 
		    ia[88]  = 11, ja[88]  = 8, ar[88]  =   0.0;                         /* a[11,8] */ 


		  /* Definindo os limitantes da linha 12*/ 
		  glp_set_row_bnds(lp,12,GLP_UP,inf_2[1],-sup_2[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 12 */
		    ia[89]  = 12, ja[89]  = 1, ar[81]  =  soma_2[1][2];                 /* a[11,1] */
		    ia[90]  = 12, ja[90]  = 2, ar[82]  =  soma_2[2][2];                 /* a[11,2] */
		    ia[91]  = 12, ja[91]  = 3, ar[83]  =  soma_2[3][2];                 /* a[11,3] */
			ia[92]  = 12, ja[92]  = 4, ar[84]  =  soma_2[4][2];                 /* a[11,4] */
		    ia[93]  = 12, ja[93]  = 5, ar[85]  =  soma_2[5][2];                 /* a[11,5] */
		    ia[94]  = 12, ja[94]  = 6, ar[86]  =  soma_2[6][2];                 /* a[11,6] */ 
		    ia[95]  = 12, ja[95]  = 7, ar[87]  =   0.0;                         /* a[11,7] */ 
		    ia[96]  = 12, ja[96]  = 8, ar[88]  =  -1.0;                         /* a[11,8] */ 
		  
		  }   

		  /* Restrição : 04 */
		  if (j >= 4){

		   /* Definindo os limitantes da linha 13*/ 
		  glp_set_row_bnds(lp,13,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 13 */
		    ia[97]   = 13, ja[97]  = 1, ar[97]  =  soma_1[1][3];                 /* a[11,1] */
		    ia[98]   = 13, ja[98]  = 2, ar[98]  =  soma_1[2][3];                 /* a[11,2] */
		    ia[99]   = 13, ja[99]  = 3, ar[99]  =  soma_1[3][3];                 /* a[11,3] */
			ia[100]  = 13, ja[100] = 4, ar[100] =  soma_1[4][3];                 /* a[11,4] */
		    ia[101]  = 13, ja[101] = 5, ar[101] =  soma_1[5][3];                 /* a[11,5] */
		    ia[102]  = 13, ja[102] = 6, ar[102] =  soma_1[6][3];                 /* a[11,6] */ 
		    ia[103]  = 13, ja[103] = 7, ar[103] =  -1.0;                         /* a[11,7] */ 
		    ia[104]  = 13, ja[104] = 8, ar[104] =   0.0;                         /* a[11,8] */ 

		  /* Definindo os limitantes da linha 14*/ 
		  glp_set_row_bnds(lp,14,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 14 */
		    ia[105]  = 14, ja[105] = 1, ar[105]  =  soma_2[1][3];                 /* a[11,1] */
		    ia[106]  = 14, ja[106] = 2, ar[106]  =  soma_2[2][3];                 /* a[11,2] */
		    ia[107]  = 14, ja[107] = 3, ar[107]  =  soma_2[3][3];                 /* a[11,3] */
			ia[108]  = 14, ja[108] = 4, ar[108]  =  soma_2[4][3];                 /* a[11,4] */
		    ia[109]  = 14, ja[109] = 5, ar[109]  =  soma_2[5][3];                 /* a[11,5] */
		    ia[110]  = 14, ja[110] = 6, ar[110]  =  soma_2[6][3];                 /* a[11,6] */ 
		    ia[111]  = 14, ja[111] = 7, ar[111]  =   0.0;                         /* a[11,7] */ 
		    ia[112]  = 14, ja[112] = 8, ar[112]  =  -1.0;                         /* a[11,8] */ 
		  }   

	      /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(lp,48 + 8*j + 8*j,ia,ja,ar);

		  /* Resolve o problema */
		  glp_simplex(lp,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  z = glp_get_obj_val(lp);
		  VTH1S1 = glp_get_col_prim(lp,1);
		  VVH1S1 = glp_get_col_prim(lp,2);
		  VTH2S1 = glp_get_col_prim(lp,3);
		  VVH2S1 = glp_get_col_prim(lp,4);
		  G1 = glp_get_col_prim(lp,5);
		  G2 = glp_get_col_prim(lp,6);
		  ALFA1_1 = glp_get_col_prim(lp,7);
		  ALFA1_2 = glp_get_col_prim(lp,8);
		  printf ("Primal interação : %d  \n",j);
		  printf ("z = %g; VTH1S1 = %g; VVH1S1 = %g;VTH2S1 = %g;VVH2S1 = %g; G1 = %g; G2 = %g \n \n", z,VTH1S1,VVH1S1,VTH2S1,VVH2S1,G1,G2); 
			  if (j >= 8){
				  goto start;
		  }

		  }

		// Mostrando a convergência
		 printf("Houve convergência na interação: %d \n",j); 
		 printf("Erro relativo 1 Cenário: %lf\n",fabs(ALFA1_1 - ALFA1_1X));
		 printf("Erro relativo 2 Cenário: %lf\n",fabs(ALFA1_2 - ALFA1_2X));
		 printf("Os pontos ótimos são: \n");
		 printf ("z = %lf \n",z);  
		 printf("VTH1S1 = %lf,VVH1S1 = %lf,VTH2S1 = %lf, VVH2S1 = %lf, G1 = %lf,G2 = %lf \n",VTH1S1,VVH1S1,VTH2S1,VVH2S1,G1,G2);
		 printf("O valor ótimo de z: \n");
		 printf("z = %lf\n \n", z);
		 printf("Valor do custo eperado no estágio 2\n");
		 printf("AlFA = %lf \n",C1*ALFA1_1 + C2*ALFA1_2);
		 printf("ALFA1_1 = %lf\n", ALFA1_1);
		 printf("ALFA1_2 = %lf\n", ALFA1_2);

		 // Gravando os dados no arquivo de VTH1S1
		FILE *arq1;
		arq1 = fopen("VTH1S1.dat","a");
		fprintf(arq1,"%lf \n",(PRODUTIBILIDADE[0]*glp_get_col_prim(lp,1))); 
		fclose(arq1);

		// Gravando os dados no arquivo de VTH2S2 
		FILE *arq2;
		arq2 = fopen("VTH2S1.dat","a");
		fprintf(arq2,"%lf \n",(PRODUTIBILIDADE[1]*glp_get_col_prim(lp,3))); 
		fclose(arq2);

		// Gravando os dados no arquivo de G1
		FILE *arq3;
		arq3 = fopen("G1.dat","a");
		fprintf(arq3,"%lf \n",glp_get_col_prim(lp,5)); 
		fclose(arq3);

		// Gravando os dados no arquivo de G2
		FILE *arq4;
		arq4 = fopen("G2.dat","a");
		fprintf(arq4,"%lf \n",glp_get_col_prim(lp,6)); 
		fclose(arq4);

		// Gravando os dados do custo
		FILE *arq5;
		arq5 = fopen("custo2.dat","a");
		fprintf(arq5,"%lf \n",C1*ALFA1_1 + C2*ALFA1_2); 
		fclose(arq5);

		// Gravando os dados de geracao
		FILE *arq6;
		arq6 = fopen("geracao.dat","a");
		fprintf(arq6,"%lf \n",PRODUTIBILIDADE[0]*VTH1S1 + PRODUTIBILIDADE[1]*VTH2S1 + G1 + G2); 
		fclose(arq6);

		// Gravando os dados do custo
		FILE *arq7;
		arq7 = fopen("z.dat","a");
		fprintf(arq7,"%lf \n",z); 
		fclose(arq7);


		goto end;

start:
		 /* Atigindo o número de interações */
		 printf("Não houve convergência,número de interações: %d\n",j);
		 printf("Erro para o primeiro Cenário =  %lf,condição de erro: %lf \n \n",fabs(ALFA1_1 - ALFA1_1X),(double)(ERRO));
		 printf("Os pontos são: \n");
		 printf ("z = %lf \n",z);  
		 printf("VTH1S1 = %lf,VVH1S1 = %lf,VTH2S1 = %lf, VVH2S1 = %lf, G1 = %lf,G2 = %lf \n",VTH1S1,VVH1S1,VTH2S1,VVH2S1,G1,G2);
		 printf("O valor do custo futuro ótimo é :\n");
		 printf("Alfa = %lf \n",C1*ALFA1_1 + C2*ALFA1_2);
	
end:
         /* Limpeza */
		 glp_delete_prob(lp);
		 glp_delete_prob(ld_1);
		 glp_delete_prob(ld_2);
		 glp_free_env();

		 		
		}
int main(void){ 

		int d;
		FILE *arq;
		arq = fopen("dados.txt","r");
		fscanf(arq,"%d\n",&d);

		double p;
		FILE *arq2;
		arq2 = fopen("dados2.txt","r");
		fscanf(arq2,"%lf \n",&p);

		double pb;
		FILE *arq3;
		arq3 = fopen("peso.txt","r");
		fscanf(arq3,"%lf \n",&pb);

		PDDE(d,p,pb);
return 0;

} // Fim da main()

