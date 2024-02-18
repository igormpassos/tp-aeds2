#ifndef LISTA_COMPARTIMENTOS_H
#define LISTA_COMPARTIMENTOS_H

#include "compartimentoHash.h"

typedef struct ListaCompartimentos {
	TCompartimento **lista;
	int qtd;
} ListaCompartimentos;

// Imprime compartimentos
void imprime_compartimentos(ListaCompartimentos *lc);

// Cria lista de compartimentos. Lembrar de usar libera_compartimentos(compartimentos)
ListaCompartimentos *cria_compartimentos(int qtd, ...);

// Salva lista de compartimentos no arquivo nome_arquivo
void salva_compartimentos(char *nome_arquivo, ListaCompartimentos *lc);

// Le lista de compartimentos do arquivo nome_arquivo
ListaCompartimentos *le_compartimentos(char *nome_arquivo);

// Compara duas listas de compartimentos
// Retorna 1 se os compartimentos das duas listas forem iguais
// e 0 caso contrario
int cmp_compartimentos(ListaCompartimentos *c1, ListaCompartimentos *c2);

// Desaloca lista de compartimentos
void libera_compartimentos(ListaCompartimentos *lc);

#endif