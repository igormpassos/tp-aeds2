#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encadeamentoExterior.h"
#include "../consulta.h" // Incluído para utilizar a estrutura TConsulta e suas funções auxiliares

// Função de hash simples
int h(int id_consulta, int m) {
    return id_consulta % m;
}

void cria_hash_consulta(char *nome_arquivo_hash, int m) {
    FILE *file = fopen(nome_arquivo_hash, "wb");
    if (file == NULL) {
        perror("Erro ao criar arquivo hash de consultas");
        exit(EXIT_FAILURE);
    }
    
    int i;
    int vazio = -1;
    for (i = 0; i < m; i++) {
        fwrite(&vazio, sizeof(int), 1, file);
    }
    
    fclose(file);
}

int busca_consulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {
    FILE *file_hash = fopen(nome_arquivo_hash, "rb");
    FILE *file_dados = fopen(nome_arquivo_dados, "rb");
    if (file_hash == NULL || file_dados == NULL) {
        perror("Erro ao abrir arquivos");
        exit(EXIT_FAILURE);
    }
    
    int indice = h(id_consulta, m);
    fseek(file_hash, indice * sizeof(int), SEEK_SET);
    int endereco_lista;
    fread(&endereco_lista, sizeof(int), 1, file_hash);
    if (endereco_lista == -1) {
        fclose(file_hash);
        fclose(file_dados);
        return -1; // Consulta não encontrada
    }
    
    fseek(file_dados, endereco_lista, SEEK_SET);
    TConsulta *consulta = leConsulta(file_dados);
    while (consulta != NULL) {
        if (consulta->id == id_consulta) {
            fclose(file_hash);
            fclose(file_dados);
            free(consulta);
            return endereco_lista; // Retorna o endereço onde a consulta foi encontrada
        }
        free(consulta);
        consulta = leConsulta(file_dados);
    }
    
    fclose(file_hash);
    fclose(file_dados);
    return -1; // Consulta não encontrada
}

int insere_consulta(TConsulta *nova_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m) {
    FILE *file_hash = fopen(nome_arquivo_hash, "r+b");
    FILE *file_dados = fopen(nome_arquivo_dados, "ab");
    if (file_hash == NULL || file_dados == NULL) {
        perror("Erro ao abrir arquivos");
        exit(EXIT_FAILURE);
    }
    
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
            if (consulta_existente->id == nova_consulta->id) {
                free(consulta_existente);
                fclose(file_hash);
                fclose(file_dados);
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
    salvaConsulta(nova_consulta, file_dados);
    
    fclose(file_hash);
    fclose(file_dados);
    
    return endereco_lista; // Retorna o endereço onde a consulta foi inserida
}

int exclui_consulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {
    FILE *file_hash = fopen(nome_arquivo_hash, "r+b");
    FILE *file_dados = fopen(nome_arquivo_dados, "r+b");
    if (file_hash == NULL || file_dados == NULL) {
        perror("Erro ao abrir arquivos");
        exit(EXIT_FAILURE);
    }
    
    int indice = h(id_consulta, m);
    fseek(file_hash, indice * sizeof(int), SEEK_SET);
    int endereco_lista;
    fread(&endereco_lista, sizeof(int), 1, file_hash);
    if (endereco_lista == -1) {
        fclose(file_hash);
        fclose(file_dados);
        return -1; // Consulta não encontrada
    }
    
    int endereco_anterior = -1;
    int endereco_atual = endereco_lista;
    fseek(file_dados, endereco_atual, SEEK_SET);
    TConsulta *consulta;
    while ((consulta = leConsulta(file_dados)) != NULL) {
        if (consulta->id == id_consulta) {
            if (endereco_anterior == -1) {
                // Primeiro elemento da lista encadeada
                fseek(file_hash, indice * sizeof(int), SEEK_SET);
                fwrite(&consulta->id, sizeof(int), 1, file_hash); // Atualiza ponteiro no arquivo hash
            } else {
                fseek(file_dados, endereco_anterior, SEEK_SET);
                fwrite(&consulta->id, sizeof(int), 1, file_dados); // Atualiza ponteiro anterior na lista
            }
            // Marca registro como excluído (pode ser reutilizado)
            consulta->id = -1;
            fseek(file_dados, endereco_atual, SEEK_SET);
            salvaConsulta(consulta, file_dados);
            free(consulta);
            fclose(file_hash);
            fclose(file_dados);
            return endereco_lista; // Retorna o endereço onde a consulta foi excluída
        }
        endereco_anterior = endereco_atual;
        endereco_atual = ftell(file_dados);
        free(consulta);
    }
    
    fclose(file_hash);
    fclose(file_dados);
    return -1; // Consulta não encontrada
}
