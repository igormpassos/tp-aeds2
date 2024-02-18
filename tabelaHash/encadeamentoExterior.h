#ifndef ENCADEAMENTO_EXTERIOR_H
#define ENCADEAMENTO_EXTERIOR_H

// Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
// Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
// nome_arquivo_hash: nome do arquivo hash a ser criado
// m: tamanho da tabela hash a ser criada
void cria_hash(char *nome_arquivo_hash, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash)
// Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
// cod_cli: chave da consulta que esta sendo buscado
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// m: tamanho da tabela hash (a função de hash é h(x) = x mod m
// Retorna o endereco onde a consulta foi encontrado, ou -1 se nao for encontrado
int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

// Executa insercao em Arquivos por Encadeamento Exterior (Hash)
// cod_cli: chave da consulta que esta sendo inserido
// nome_cli: nome da consulta a ser inserido
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// num_registros: numero de registros que ja existem gravados no arquivo
// Retorna o endereco onde a consulta foi inserido, ou -1 se nao conseguiu inserir
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m);

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash)
// cod_cli: chave da consulta a ser excluido
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// Retorna o endereco da consulta que foi excluido, ou -1 se cliente nao existe
int exclui(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

#endif