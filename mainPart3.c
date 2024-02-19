#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "consulta.h"
#include "tabelaHash/encadeamentoExterior.c"

// Função para salvar o log das operações em um arquivo txt
void salvarLog(char *nome_arquivo, int tamanho_base, char *tipo_operacao, double tempo_execucao) {
    FILE *file = fopen(nome_arquivo, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de log");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Tamanho da base: %d, Tipo de operacao: %s, Tempo de execucao: %.6f segundos\n", tamanho_base, tipo_operacao, tempo_execucao);
    fclose(file);
}

int main() {
    clock_t inicio, fim;
    double tempo_execucao;
    char log_file[] = "logParte3.txt";

    FILE *consultaFile = fopen("consultas.dat", "w+b");
    FILE *hashConsultaFile = fopen("hash_consultas.dat", "w+b");

    if (consultaFile == NULL || hashConsultaFile == NULL) {
        perror("Erro ao abrir os arquivos");
        exit(EXIT_FAILURE);
    }

    // Parametros de configuração ========================================
    int tamBase = 100000;
    int id_busca = 50000;
    int id_exclusao = 33330;

    // Criando bases de dados com diferentes números de registros
    criarBaseConsulta(consultaFile, tamBase);
    fflush(consultaFile); // Garante que os dados sejam gravados no arquivo antes de imprimir
    
    // imprimirBaseConsulta(consultaFile);

    // Criando tabelas hash para as bases de dados
    criaHashConsulta(hashConsultaFile, consultaFile, tamBase);
    fflush(hashConsultaFile); // Garante que os dados sejam gravados no arquivo

    // Realizando operações de busca, inserção e exclusão para cada base de dados
    int endereco;
    TConsulta *nova_consulta;

    // Base de dados com 1000 registros
    printf("Operacoes para a base de dados com %d registros:\n", tamBase);

    inicio = clock();
    endereco = buscaConsulta(id_busca, hashConsultaFile, consultaFile, tamBase);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (endereco != -1)
        printf("Consulta com ID %d encontrada no endereco %d.\n",id_busca, endereco);
    else
        printf("Consulta com ID %d nao encontrada.\n", id_busca);
    salvarLog(log_file, tamBase, "Busca", tempo_execucao);

    inicio = clock();
    nova_consulta = criaConsulta((tamBase+1), 101, 201, "19/02/2024", "Consulta de teste");
    endereco = insereConsulta(nova_consulta, hashConsultaFile, consultaFile, tamBase, tamBase);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (endereco != -1)
        printf("Consulta com ID %d inserida no endereco %d.\n",(tamBase+1), endereco);
    else
        printf("Falha ao inserir consulta com ID %d.\n", (tamBase+1));
    salvarLog(log_file, tamBase, "Inserção", tempo_execucao);

    inicio = clock();
    endereco = excluiConsulta(300, hashConsultaFile, consultaFile, tamBase);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (endereco != -1)
        printf("Consulta com ID %d excluida do endereco %d.\n", id_exclusao, endereco);
    else
        printf("Falha ao excluir consulta com ID %d.\n", id_exclusao);
    salvarLog(log_file, tamBase, "Exclusão", tempo_execucao);


    fclose(consultaFile);

    return 0;
}
