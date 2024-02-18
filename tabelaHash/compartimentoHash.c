#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "compartimentoHash.h"


void imprime_compartimento(TCompartimento *compartimento){
	printf("%d\n", compartimento->prox);
}

TCompartimento *compartimento_hash(int prox){
	TCompartimento *compartimento = (TCompartimento *) malloc(sizeof(TCompartimento));
	compartimento->prox = prox;
	return compartimento;
}


void salva_compartimento(TCompartimento *compartimento, FILE *out){
	fwrite(&compartimento->prox, sizeof(int), 1, out);
}

TCompartimento *le_compartimento(FILE *in){
	TCompartimento *compartimento = (TCompartimento *) malloc(sizeof(TCompartimento));
	if (0 >= fread(&compartimento->prox, sizeof(int), 1, in)) {
		free(compartimento);
		return NULL;
	}
	return compartimento;
}

int cmp_compartimento(TCompartimento *c1, TCompartimento *c2){
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->prox != c2->prox) {
		return 0;
	}
	return 1;
}

int tamanho_compartimento(){
	return sizeof(int); // prox
}