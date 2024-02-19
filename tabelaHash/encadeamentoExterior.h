#ifndef ENCADEAMENTO_EXTERIOR_H
#define ENCADEAMENTO_EXTERIOR_H

#include <stdio.h>
#include "../consulta.h" // Importe o cabeçalho da sua estrutura de consulta aqui

// Função de hash
int h(int id_consulta, int m);

// Cria uma tabela hash vazia de tamanho m no arquivo especificado
void criaHashConsulta(FILE *file_hash, FILE *file_dados, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash)
// Retorna o endereço onde a consulta foi encontrada, ou -1 se não encontrada
int buscaConsulta(int id_consulta, FILE *file_hash, FILE *file_dados, int m);

// Executa inserção em Arquivos por Encadeamento Exterior (Hash)
// Retorna o endereço onde a consulta foi inserida, ou -1 se falhar
int insereConsulta(TConsulta *nova_consulta, FILE *file_hash, FILE *file_dados, int num_registros, int m);

// Executa exclusão em Arquivos por Encadeamento Exterior (Hash)
// Retorna o endereço onde a consulta foi excluída, ou -1 se não encontrada
int excluiConsulta(int id_consulta, FILE *file_hash, FILE *file_dados, int m);

#endif