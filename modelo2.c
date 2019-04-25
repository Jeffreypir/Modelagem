/* Modelo para despacho de usinas individualizada 
 * Vamos primeiro definir a função objetvo ou função custo futuro a ser minimizada */

#include <stdio.h>

/* Defindo a função produto */
int prod(int ct, int gt){ 
	return ct*gt;
}

/* Defindo uma função auxiliar para encontra o menor número de um vetor */
int menor(int *x){
	 int i,menor = x[0];
	 for (i = 0; i < 4; i++){
	 	if(menor <= x[i]){
			menor = menor;
		}else{
			menor = x[i];
		}
	}
	return menor;
}
/*Tomemos as seguintes definições:
 * ct é o custo de Geração térmica associado á unidade termoelétrican n do subsistema s, no estágio t
 * gt é o custo de Geração da unidade termelétrica n do subsitema s, no estágio t
 * cd é o custo de déficit associado ao subsistema
 * def défcit no estágio t, associado ao subsistema s
 * nsis número de subsitemas 
 * ngts de unidades termooelétricas do subsitema s
 */

/* Iniciando a função de custo futuro */
int main(){ 
	int  x[] = {1,2,3,4},y[] = {1,1,1,1}, z[] = {0,0,0,0}, w[]= {0,0,0,0},i,menor,vetor[4],soma;
	for (i = 0;i < sizeof(x)/sizeof(x[0]); i++){
		vetor[i] = prod(x[i],y[i]) + z[i] + w[i];
	}
	for (i = 0; i < sizeof(x)/sizeof(x[0]); i++){
		printf ("%d \n oioioi ", vetor[i]);
	}
	return 0;
}


