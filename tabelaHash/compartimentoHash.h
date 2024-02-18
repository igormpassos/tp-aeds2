#ifndef COMPARTIMENTO_HASH_H
#define COMPARTIMENTO_HASH_H

#include <stdio.h>

typedef struct CompartimentoHash {
	int prox;
} TCompartimento;

// Imprime compartimento hash
void imprimeCompartimento(TCompartimento *compartimento);

// Cria compartimento hash. Lembrar de usar free(compartimento_hash)
TCompartimento *compartimentoHash(int prox);

// Salva compartimento no arquivo out, na posicao atual do cursor
void salvaCompartimento(TCompartimento *compartimento, FILE *out);

// Le um compartimento do arquivo in na posicao atual do cursor
// Retorna um ponteiro para compartimento lido do arquivo
TCompartimento *leCompartimento(FILE *in);

// Compara dois compartimentos
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmpCompartimento(TCompartimento *c1, TCompartimento *c2);

// Retorna tamanho do compartimento hash em bytes
int tamanhoCompartimento();

#endif