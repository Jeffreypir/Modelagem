# Modelamento do Despacho Hidrotérmico

Autor:Jefferson Bezerra dos Santos

Para a utilização do algoritmo do algoritmo é necessário a utilização da biblioteca GLPK  
para Programação Linear. A instalação em distribuiões Debian e Debian baseadas 
é dada por:

			apt install libglpk-dev

como usuário root.   
O linguagem R deve está instalada, além do bash.

### Os principais pontos a serem elencados são:

* O ambiente foi a distribuição Gnu/linux Debian.
* O algoritmo possui comentários para a sua utilização, é necessária a leitura.
* O algoritmo está configurado para gerar as mesmas pastas deste repositório. 
* O arquivo principal é constituido em C.
* O arquivo principal é "energia_bender_shaped.c", gerar os dados.
* O primeiro arquivo auxiliar é feito em shell script, bash.
* O arquivo auxiliar é "energia.sh", criar e formata os arquivos e pastas necessarias.
* O segundo e o terceiro arquivo auxiliar possuem como função criar as figuras em .eps e .pdf.  
* O segundo arquivo é simular.r e o terceiro arquivo é scusto.r 

O segundo e terceiro arquivo podem ser substituídos por outra linguagem para a construção  
das figuras, por exemplo python. Veja a wiki do projeto para maiores detalhes teóricos.

## Observação:

Utilizar uma distribuição Gnu/linux tornará a implementação do algoritmo  mais fácil.
A documentação deste projeto está incompleta, ainda fazendo a documentação.
