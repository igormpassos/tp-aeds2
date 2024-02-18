#include "tabelaHash.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void salvarLog(const char *entidade, double tempo, int base)
{
    FILE *logFile = fopen("logParteIII.txt", "a");
    if (!logFile)
    {
        perror("Erro ao abrir arquivo de log");
        exit(1);
    }

    fprintf(logFile, "%s\n", entidade);
    fprintf(logFile, "Tempo de execucao: %lf segundos\n\n", tempo);
    fprintf(logFile, "Tamanho da base: %d\n", base);
    fprintf(logFile, "=============================================\n\n");

    fclose(logFile);
}

// Função para realizar testes de inserção na tabela hash
void testeInserir(int tamanhoBase) {
    clock_t inicio, fim;
    double tempo;

    // Inicializar tabela hash
    for (int i = 0; i < TAM_TABELA; i++) {
        tabelaHash[i].head = NULL;
    }

    // Inserir consultas na tabela hash
    inicio = clock();
    for (int i = 1; i <= tamanhoBase; i++) {
        TConsulta consulta;
        consulta.id = i;
        consulta.id_medico = i + 1000;
        consulta.id_paciente = i + 2000;
        sprintf(consulta.data, "2023-11-20");
        sprintf(consulta.descricao, "Consulta de teste %d", i);

        inserirConsulta(consulta);
    }
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Log de inserção
    salvarLog("Tabela Hash - Inserção", tempo, tamanhoBase);
}

// Função para realizar testes de busca na tabela hash
void testeBuscar(int tamanhoBase, int idBuscar) {
    clock_t inicio, fim;
    double tempo;

    // Buscar consultas na tabela hash
    inicio = clock();
    TConsulta *consulta = buscarConsulta(idBuscar);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Log de busca
    salvarLog("Tabela Hash - Busca", tempo, tamanhoBase);

    // Imprimir dados da consulta encontrada (se houver)
    if (consulta != NULL) {
        printf("\nConsulta encontrada:\n");
        printf("ID: %d\n", consulta->id);
        printf("Médico: %d\n", consulta->id_medico);
        printf("Paciente: %d\n", consulta->id_paciente);
        printf("Data: %s\n", consulta->data);
        printf("Descrição: %s\n\n", consulta->descricao);
    } else {
        printf("\nConsulta não encontrada.\n");
    }
}

// Função para realizar testes de remoção na tabela hash
void testeRemover(int tamanhoBase, int idRemover) {
    clock_t inicio, fim;
    double tempo;

    // Remover consultas na tabela hash
    inicio = clock();
    removerConsulta(idRemover);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Log de remoção
    salvarLog("Tabela Hash - Remoção", tempo, tamanhoBase);
}

int main() {
    int tamanhosBase[] = {5000, 10000, 100000};
    int idBuscar = 500;     // ID para buscar na tabela hash
    int idRemover = 2500;   // ID para remover da tabela hash

    // Executar testes com diferentes tamanhos de base
    for (int i = 0; i < sizeof(tamanhosBase) / sizeof(tamanhosBase[0]); i++) {
        printf("\n### Testes para base de tamanho %d ###\n", tamanhosBase[i]);

        // Teste de inserção
        testeInserir(tamanhosBase[i]);

        // Teste de busca por ID
        testeBuscar(tamanhosBase[i], idBuscar);

        // Teste de remoção por ID
        testeRemover(tamanhosBase[i], idRemover);
    }

    return 0;
}
