/*******************************************************************************
 *	center.c
 *		Centraliza o texto do arquivo dado na entrada e imprime no arquivo
 *		passado como argumento.
 ******************************************************************************/

/* Includes & Macros */
#include <stdio.h>
#include "buffer.h"

/*	escreve():
 *		Escreve no arquivo e imprime erros.
 */
int escreve(FILE *output, char *buffer, int n, int c,
			char *argv[], int line, int branco) {
	
	int inicio = 0;
	int fim = n - 1;
	/* descarta espaços no começo */
	for (int i = 0; i < n; i++) {
		if (buffer[i] != 32) {
			inicio = i;
			break;
		}
	}
	/* descarta espaços no fim */
	for (int i = n - 1; n >= 0; i--) {
		if (buffer[i] != 32) {
			fim = i;
			break;
		}
	}
	
	/* linha em branco (inicio == fim) */
	if (inicio == fim) {
		/* não imprime duas linhas em branco repetidas */
		if (branco == 1) return 0;
		fprintf(output, "\n");
		return 1;
	}
	/* linha maior que c */
	else if (fim - inicio > c) {
		for (int i = inicio; i < fim + 1; i++)
			fprintf(output, "%c", buffer[i]);
		fprintf(stderr, "center: %s: line %d: line too long\n", argv[1], line);
		return 0;
	}
	/* o resto */
	else {
		int resto = c - (fim - inicio);
		for (int i = 0; i <= resto / 2; i++) fprintf(output, " ");
		for (int i = inicio; i < fim + 1; i++)
			fprintf(output, "%c", buffer[i]);
		return 0;
	}
}

/*	main():
 *		Recebe os argumentos de entrada e faz o loop passando para escreve()
 *		as instruções necessárias para gravar o arquivo.
 */
int main(int argc, char *argv[]) {
	/* declaração e inicialização das variáveis */
	Buffer *b = buffer_create(sizeof(char));
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	int c = atoi(argv[3]);
	char *buffer;
	int line = 1;
	
	/* leitura das linhas */
	int n = read_line(input, b);
	while (n != 0) {
		buffer = (char*) b -> data;
		int branco = escreve(output, buffer, n, c, argv, line, branco);
		n = read_line(input, b);
		line++;
	}

	return 0;
}
