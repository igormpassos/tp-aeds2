#ifndef ENCADEAMENTO_EXTERIOR_H
#define ENCADEAMENTO_EXTERIOR_H

#include "../consulta.h"

// Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
// Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
// nome_arquivo_hash: nome do arquivo hash a ser criado
// m: tamanho da tabela hash a ser criada
void criaHashConsulta(char *nome_arquivo_hash, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash)
// Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
// id_consulta: chave da consulta que esta sendo buscada
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// m: tamanho da tabela hash (a função de hash é h(x) = x mod m
// Retorna o endereco onde a consulta foi encontrado, ou -1 se nao for encontrado
int buscaConsulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

// Executa insercao em Arquivos por Encadeamento Exterior (Hash)
// nova_consulta: consulta a ser inserida
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// num_registros: numero de registros que ja existem gravados no arquivo
// m: tamanho da tabela hash
// Retorna o endereco onde a consulta foi inserida, ou -1 se nao conseguiu inserir
int insereConsulta(TConsulta *nova_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m);

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash)
// id_consulta: chave da consulta a ser excluida
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// m: tamanho da tabela hash
// Retorna o endereco da consulta que foi excluida, ou -1 se consulta nao existe
int excluiConsulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

#endif
