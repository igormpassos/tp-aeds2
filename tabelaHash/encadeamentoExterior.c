#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encadeamentoExterior.h"
#include "listaCompartimentos.c" // Incluido para gerar hash na funcao criaHashConsulta
#include "compartimentoHash.c" // Incluido para gerar hash na funcao criaHashConsulta
#include "../consulta.c"

// Função de hash simples
int h(int id_consulta, int m) {
    return id_consulta % m;
}

void criaHashConsulta(FILE *file_hash, FILE *file_dados, int m) {
    int vazio = -1;
    TCompartimento **compartimentos = (TCompartimento **)malloc(sizeof(TCompartimento *) * m);
    if (compartimentos == NULL) {
        perror("Erro ao alocar memória para compartimentos");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa os compartimentos com valores padrão
    for (int i = 0; i < m; i++) {
        compartimentos[i] = compartimentoHash(vazio); // Inicializa como vazio
    }

    // Percorre o arquivo de dados e associa a posição de cada registro a um compartimento
    rewind(file_dados);
    TConsulta *consulta;
    int endereco = 0;
    while ((consulta = leConsulta(file_dados)) != NULL) {
        int indice = h(consulta->id, m);
        compartimentos[indice]->prox = endereco; // Associa a posição do registro ao compartimento
        endereco = ftell(file_dados); // Atualiza o endereço para o próximo registro
        free(consulta);
    }

    // Escreve os compartimentos no arquivo de hash
    for (int i = 0; i < m; i++) {
        fwrite(&(compartimentos[i]->prox), sizeof(int), 1, file_hash);
    }

    // Libera a memória alocada para os compartimentos
    for (int i = 0; i < m; i++) {
        free(compartimentos[i]);
    }
    free(compartimentos);
}

int buscaConsulta(int id_consulta, FILE *file_hash, FILE *file_dados, int m) {
    int indice = h(id_consulta, m);
    fseek(file_hash, indice * sizeof(int), SEEK_SET);
    int endereco_lista;
    fread(&endereco_lista, sizeof(int), 1, file_hash);
    if (endereco_lista == -1) {
        return -1; // Consulta não encontrada
    }

    fseek(file_dados, endereco_lista, SEEK_SET);
    TConsulta *consulta = leConsulta(file_dados);
    while (consulta != NULL) {
        if (consulta->id == id_consulta && consulta->ocupado) {
            free(consulta);
            return endereco_lista; // Retorna o endereço onde a consulta foi encontrada
        }
        free(consulta);
        consulta = leConsulta(file_dados);
    }

    return -1; // Consulta não encontrada
}

int insereConsulta(TConsulta *nova_consulta, FILE *file_hash, FILE *file_dados, int num_registros, int m) {
    int indice = h(nova_consulta->id, m);
    fseek(file_hash, indice * sizeof(int), SEEK_SET);
    int endereco_lista;
    fread(&endereco_lista, sizeof(int), 1, file_hash);
    if (endereco_lista == -1) {
        endereco_lista = ftell(file_dados); // Nova consulta, adiciona ao final do arquivo de dados
        fseek(file_hash, indice * sizeof(int), SEEK_SET);
        fwrite(&endereco_lista, sizeof(int), 1, file_hash); // Atualiza endereço no arquivo hash
    } else {
        fseek(file_dados, endereco_lista, SEEK_SET);
        TConsulta *consulta_existente;
        while ((consulta_existente = leConsulta(file_dados)) != NULL) {
            if (consulta_existente->id == nova_consulta->id && consulta_existente->ocupado) {
                free(consulta_existente);
                return -1; // Consulta já existe
            }
            free(consulta_existente);
        }
        // Adiciona ao final da lista encadeada
        fseek(file_dados, 0, SEEK_END);
        endereco_lista = ftell(file_dados);
        fwrite(&endereco_lista, sizeof(int), 1, file_dados);
    }

    // Escreve os dados da consulta no arquivo de dados
    nova_consulta->ocupado = 1; // Define o registro como ocupado
    salvaConsulta(nova_consulta, file_dados);

    return endereco_lista; // Retorna o endereço onde a consulta foi inserida
}

int excluiConsulta(int id_consulta, FILE *file_hash, FILE *file_dados, int m) {
    int indice = h(id_consulta, m);
    fseek(file_hash, indice * sizeof(int), SEEK_SET);
    int endereco_lista;
    fread(&endereco_lista, sizeof(int), 1, file_hash);
    if (endereco_lista == -1) {
        return -1; // Consulta não encontrada
    }

    int endereco_anterior = -1;
    int endereco_atual = endereco_lista;
    fseek(file_dados, endereco_atual, SEEK_SET);
    TConsulta *consulta;
    while ((consulta = leConsulta(file_dados)) != NULL) {
        if (consulta->id == id_consulta && consulta->ocupado) {
            if (endereco_anterior == -1) {
                // Primeiro elemento da lista encadeada
                fseek(file_hash, indice * sizeof(int), SEEK_SET);
                fwrite(&consulta->id, sizeof(int), 1, file_hash); // Atualiza ponteiro no arquivo hash
            } else {
                fseek(file_dados, endereco_anterior, SEEK_SET);
                fwrite(&consulta->id, sizeof(int), 1, file_dados); // Atualiza ponteiro anterior na lista
            }
            // Marca registro como excluído
            consulta->ocupado = 0;
            fseek(file_dados, endereco_atual, SEEK_SET);
            salvaConsulta(consulta, file_dados);
            free(consulta);
            return endereco_lista; // Retorna o endereço onde a consulta foi excluída
        }
        endereco_anterior = endereco_atual;
        endereco_atual = ftell(file_dados);
        free(consulta);
    }

    return -1; // Consulta não encontrada
}