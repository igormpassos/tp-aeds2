#ifndef LISTA_COMPARTIMENTOS_H
#define LISTA_COMPARTIMENTOS_H

#include "compartimentoHash.h"

typedef struct ListaCompartimentos {
	TCompartimento **lista;
	int qtd;
} ListaCompartimentos;

// Imprime compartimentos
void imprimeCompartimentos(ListaCompartimentos *lc);

// Cria lista de compartimentos. Lembrar de usar libera_compartimentos(compartimentos)
ListaCompartimentos *criaCompartimentos(int qtd, ...);

// Salva lista de compartimentos no arquivo nome_arquivo
void salvaCompartimentos(char *nome_arquivo, ListaCompartimentos *lc);

// Le lista de compartimentos do arquivo nome_arquivo
ListaCompartimentos *leCompartimentos(char *nome_arquivo);

// Compara duas listas de compartimentos
// Retorna 1 se os compartimentos das duas listas forem iguais
// e 0 caso contrario
int cmpCompartimentos(ListaCompartimentos *c1, ListaCompartimentos *c2);

// Desaloca lista de compartimentos
void liberaCompartimentos(ListaCompartimentos *lc);

#endif