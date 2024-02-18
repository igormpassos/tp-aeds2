#include "tabelaHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Bucket tabelaHash[TAM_TABELA];

// Função de hash simples (divisão)
int funcaoHash(int id) {
    return id % TAM_TABELA;
}

// Função para buscar uma consulta na tabela hash
TConsulta *buscarConsulta(int id) {
    int indice = funcaoHash(id);

    Node *atual = tabelaHash[indice].head;
    while (atual != NULL) {
        if (atual->consulta.id == id) {
            return &(atual->consulta);
        }
        atual = atual->next;
    }

    return NULL; // Consulta não encontrada
}

// Verifica se a consulta ja existe na lista encadeada
int consultaExiste(int indice, int id) {
    Node *current = tabelaHash[indice].head;
    while (current != NULL) {
        if (current->consulta.id == id) {
            return 1; // Encontrado
        }
        current = current->next;
    }
    return 0; // Não encontrado
}

// Função para inserir uma consulta na tabela hash
void inserirConsulta(TConsulta consulta) {
    int indice = funcaoHash(consulta.id);

    // Verificar se a consulta já existe
    if (consultaExiste(indice, consulta.id)) {
        printf("Consulta com id %d ja existe.\n", consulta.id);
        return; // Não insere se já existir
    }

    Node *novoNode = (Node *)malloc(sizeof(Node));
    if (novoNode == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    // Adiciona dados da consulta
    novoNode->consulta = consulta;

    // Referencia o cabeçalho da lista ao nó criado (Nó criado aponta pra cabeça da lista) 
    novoNode->next = tabelaHash[indice].head;
    
    // Atualiza o cabeçalho da lista com o nó criado (Insere no início)
    tabelaHash[indice].head = novoNode;
}

// Função para remover uma consulta da tabela hash
void removerConsulta(int id) {
    int indice = funcaoHash(id);

    // Inicializa o ponteiro 'atual' para percorrer a lista e 'anterior' como NULL
    Node *atual = tabelaHash[indice].head;
    Node *anterior = NULL;

    // Percorre a lista até encontrar a consulta com o id fornecido ou chegar ao final da lista
    while (atual != NULL && atual->consulta.id != id) {
        anterior = atual; // Mantém o nó anterior
        atual = atual->next; // Vai para o próximo nó
    }

    // Verifica se a consulta não foi encontrada na lista
    if (atual == NULL) {
        // Consulta não encontrada
        return;
    }

    // Se 'anterior' ainda é NULL, significa que a consulta a ser removida é a primeira da lista
    if (anterior == NULL) {
        // Atualiza o cabeçalho da lista para o próximo elemento, removendo o primeiro
        tabelaHash[indice].head = atual->next;
    } else {
        // Remove a consulta da lista ligando o nó anterior ao próximo do nó 'atual'
        anterior->next = atual->next;
    }

    // Libera memória alocada para atual
    free(atual);
}

// Função para imprimir a tabela hash
void imprimirTabelaHash() {
    printf("\nTabela Hash:\n");
    for (int i = 0; i < TAM_TABELA; i++) {
        printf("[%d]: ", i);

        Node *atual = tabelaHash[i].head;
        while (atual != NULL) {
            printf("ID: %d, Médico: %d, Paciente: %d, Data: %s, Descrição: %s -> ",
                   atual->consulta.id, atual->consulta.id_medico, atual->consulta.id_paciente,
                   atual->consulta.data, atual->consulta.descricao);
            atual = atual->next;
        }

        printf("NULL\n");
    }
}
