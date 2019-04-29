/* Modelo para despacho de usinas individualizada 
 * Vamos primeiro definir a função objetvo ou função custo futuro a ser minimizada */

#include <stdio.h>

/* Defindo a função produto */
float prod(float c, float g, float t){ 
	return (c*t)*(g*t);
}

/*Tomemos as seguintes definições:
 * ct é o custo de Geração térmica associado á unidade termoelétrica n do subsistema s, no estágio t (depedendo pode ser dias, meses,etc).
 * gt é o custo de Geração da unidade termoelétrica n do subsistema s, no estágio t (depedendo pode ser dias, meses, etc).
 * cd é o custo de déficit associado ao subsistema.
 * def défcit no estágio t, associado ao subsistema s.
 * nsis número de subsitemas.
 * ngts de unidades termooelétricas do subsitema s.
 */

/* Iniciando a função de custo futuro */
int main(){ 
	float x[] = {1,2,3,4},y[] = {1,1,1,1}, z[] = {2,3,6,9}, w[]= {1,3,5,7};
	int t,soma,i,l,j = sizeof(x)/sizeof(x[0]);;
	printf ("Digite o valor de t(meses) para ser avaliado: ");
	scanf("%d", &l); 
	float valor_final[l]; 
	int vetor[j];
	for (t = 0; t < l; t ++){
		for (i = 0;i < j; i++){
			vetor[i] = prod(x[i],y[i],t) + z[i] + w[i];
		}
	soma = 0;
		for (i = 0; i < j ; i++){
			soma = soma + vetor[i];
		}
	valor_final[t] = soma;
	soma = 0;
	}
	for ( i = 0; i < l ; i++){
		printf ( " %f \n", valor_final[i]);
	}
	return 0;
}

