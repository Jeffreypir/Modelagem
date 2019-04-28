/* Modelo para despacho de usinas individualizada 
 * Vamos primeiro definir a função objetvo ou função custo futuro a ser minimizada */

#include <stdio.h>

/* Defindo a função produto */
int prod(int c, int g, int t){ 
	return (c*t)*(g*t);
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
 * ct é o custo de Geração térmica associado á unidade termoelétrican n do subsistema s, no estágio t (depedendo pode ser dias, meses,etc).
 * gt é o custo de Geração da unidade termelétrica n do subsistema s, no estágio t (depedendo pode ser dias, meses, etc).
 * cd é o custo de déficit associado ao subsistema.
 * def défcit no estágio t, associado ao subsistema s.
 * nsis número de subsitemas.
 * ngts de unidades termooelétricas do subsitema s.
 */

/* Iniciando a função de custo futuro */
int main(){ 
	int x[] = {1,2,3,4},y[] = {1,1,1,1}, z[] = {2,3,6,9}, w[]= {1,3,5,7},i,l,menor,vetor[4], soma, t;
	printf (" Digite o valor de t(meses) para ser avaliado: ");
	scanf("%d", &l); 
	int fim[l];
	for (t = 0; t < l; t ++){
		for (i = 0;i < sizeof(x)/sizeof(x[0]); i++){
			vetor[i] = prod(x[i],y[i],t) + z[i] + w[i];
		}
	soma = 0;
		for (i = 0; i < sizeof(x)/sizeof(x[0]) ; i++){
			soma = soma + vetor[i];
		}
	fim[t] = soma;
	soma = 0;
	}
	for ( i = 0; i < l; i++){
		printf ( " %d \n", fim[i]);
	}
	return 0;
}


