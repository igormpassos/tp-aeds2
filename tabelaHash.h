#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include "consulta.h"

// Estrutura para um nó da lista encadeada
typedef struct Node {
    TConsulta consulta;
    struct Node *next;
} Node;

// Estrutura para um bucket (lista encadeada)
typedef struct {
    Node *head;
} Bucket;

// Tamanho da tabela hash
#define TAM_TABELA 100

// Função de hash (hash division)
int funcaoHash(int id);

// Funções para a tabela hash
TConsulta *buscarConsulta(int id);
void inserirConsulta(TConsulta consulta);
void removerConsulta(int id);
void imprimirTabelaHash();

#endif // TABELAHASH_H_INCLUDED
