#ifndef ENCADEAMENTO_EXTERIOR_H
#define ENCADEAMENTO_EXTERIOR_H

// Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
// Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
// nome_arquivo_hash: nome do arquivo hash a ser criado
// m: tamanho da tabela hash a ser criada
void cria_hash(char *nome_arquivo_hash, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash) para consulta
// id_consulta: chave da consulta que esta sendo buscado
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados das consultas estao armazenados
// m: tamanho da tabela hash (a função de hash é h(x) = x mod m)
// Retorna o endereco onde a consulta foi encontrado, ou -1 se nao for encontrado
int busca_consulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

// Executa insercao em Arquivos por Encadeamento Exterior (Hash) para consulta
// id_consulta: chave da consulta que esta sendo inserido
// id_medico: id do medico responsavel pela consulta
// id_paciente: id do paciente da consulta
// data: data da consulta
// descricao: descricao da consulta
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados das consultas estao armazenados
// num_registros: numero de registros que ja existem gravados no arquivo
// m: tamanho da tabela hash
// Retorna o endereco onde a consulta foi inserido, ou -1 se nao conseguiu inserir
int insere_consulta(int id_consulta, int id_medico, int id_paciente, char *data, char *descricao, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m);

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash) para consulta
// id_consulta: chave da consulta a ser excluida
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados das consultas estao armazenados
// m: tamanho da tabela hash
// Retorna o endereco da consulta que foi excluido, ou -1 se consulta nao existe
int exclui_consulta(int id_consulta, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

#endif
