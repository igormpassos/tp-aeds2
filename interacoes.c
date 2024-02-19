#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interacoes.h"

// Função para gerar IDs únicos para consultas
int gerarIdConsulta() {
    static int idConsulta = 1;
    return idConsulta++;
}

// Função para gerar IDs únicos para exames
int gerarIdExame() {
    static int idExame = 1;
    return idExame++;
}

void agendarConsulta(FILE *medicoFile, FILE *pacienteFile, FILE *consultaFile, int crmMedico, int idPaciente, FILE *logFile) {
    int comparacoesSeqMedico, comparacoesSeqPaciente;
    clock_t inicioSeqMedico, fimSeqMedico, inicioSeqPaciente, fimSeqPaciente;

    // Busca sequencial para médico
    inicioSeqMedico = clock();
    TMedico *medicoSeq = buscarMedico(medicoFile, crmMedico, &comparacoesSeqMedico);
    fimSeqMedico = clock();

    // Busca sequencial para paciente
    inicioSeqPaciente = clock();
    TPaciente *pacienteSeq = buscarPaciente(pacienteFile, idPaciente, &comparacoesSeqPaciente);
    fimSeqPaciente = clock();

    fprintf(logFile, "\n\nAgendar Consulta:\n");
    fprintf(logFile, "Busca Sequencial - Médico:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesSeqMedico);
    fprintf(logFile, "Tempo de execução: %lf segundos\n", ((double)(fimSeqMedico - inicioSeqMedico)) / CLOCKS_PER_SEC);

    fprintf(logFile, "Busca Sequencial - Paciente:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesSeqPaciente);
    fprintf(logFile, "Tempo de execução: %lf segundos\n\n", ((double)(fimSeqPaciente - inicioSeqPaciente)) / CLOCKS_PER_SEC);

    // Restante do código da função (criar e salvar consulta, etc.)
    if (medicoSeq && pacienteSeq) {
        // Criação da consulta
        TConsulta *novaConsulta = criaConsulta(gerarIdConsulta(), crmMedico, idPaciente, "01/01/2023", "Consulta Agendada");
        salvaConsulta(novaConsulta, consultaFile);
        free(novaConsulta);
        printf("\nConsulta criada.\n");
    }



    // Limpar memória
    if (medicoSeq) free(medicoSeq);
    if (pacienteSeq) free(pacienteSeq);
}

void realizarExame(FILE *pacienteFile, FILE *exameFile, int idPaciente, FILE *logFile) {
    int comparacoesSeqPaciente, comparacoesBinPaciente;
    clock_t inicioSeqPaciente, fimSeqPaciente, inicioBinPaciente, fimBinPaciente;

    // Busca sequencial para paciente
    inicioSeqPaciente = clock();
    TPaciente *pacienteSeq = buscarPaciente(pacienteFile, idPaciente, &comparacoesSeqPaciente);
    fimSeqPaciente = clock();

    // Busca binária para paciente
    inicioBinPaciente = clock();
    TPaciente *pacienteBin = buscarBinariaPaciente(pacienteFile, idPaciente, &comparacoesBinPaciente);
    fimBinPaciente = clock();

    fprintf(logFile, "\n\nRealizar Exame:\n");
    fprintf(logFile, "Busca Sequencial - Paciente:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesSeqPaciente);
    fprintf(logFile, "Tempo de execução: %lf segundos\n", ((double)(fimSeqPaciente - inicioSeqPaciente)) / CLOCKS_PER_SEC);

    fprintf(logFile, "Busca Binária - Paciente:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesBinPaciente);
    fprintf(logFile, "Tempo de execução: %lf segundos\n\n", ((double)(fimBinPaciente - inicioBinPaciente)) / CLOCKS_PER_SEC);

    // Restante do código da função (criar e salvar exame, etc.)
    if (pacienteSeq) {
        // Criação do exame
        TExame *novoExame = exame(gerarIdExame(), pacienteSeq->id, "01/01/2023", "Sangue", "Resultado Pendente");
        salvaExame(novoExame, exameFile);
        free(novoExame);
        printf("\nExame realizado.\n");
    }

    // Limpar memória
    if (pacienteSeq) free(pacienteSeq);
    if (pacienteBin) free(pacienteBin);
}

void visualizarHistoricoMedico(FILE *pacienteFile, FILE *consultaFile, FILE *exameFile, int idPaciente, FILE *logFile) {
    int comparacoesSeqPaciente, comparacoesBinPaciente;
    clock_t inicioSeqPaciente, fimSeqPaciente, inicioBinPaciente, fimBinPaciente;

    // Busca sequencial para paciente
    inicioSeqPaciente = clock();
    TPaciente *pacienteSeq = buscarPaciente(pacienteFile, idPaciente, &comparacoesSeqPaciente);
    fimSeqPaciente = clock();

    // Busca binária para paciente
    inicioBinPaciente = clock();
    TPaciente *pacienteBin = buscarBinariaPaciente(pacienteFile, idPaciente, &comparacoesBinPaciente);
    fimBinPaciente = clock();

    fprintf(logFile, "\n\nVisualizar Histórico Médico:\n");
    fprintf(logFile, "Busca Sequencial - Paciente:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesSeqPaciente);
    fprintf(logFile, "Tempo de execução: %lf segundos\n", ((double)(fimSeqPaciente - inicioSeqPaciente)) / CLOCKS_PER_SEC);

    fprintf(logFile, "Busca Binária - Paciente:\n");
    fprintf(logFile, "Número de comparações: %d\n", comparacoesBinPaciente);
    fprintf(logFile, "Tempo de execução: %lf segundos\n\n", ((double)(fimBinPaciente - inicioBinPaciente)) / CLOCKS_PER_SEC);

    // Restante do código da função (exibir histórico médico, etc.)
    if (pacienteSeq) {
        // Exibir consultas do paciente
        printf("\nConsultas Realizadas:\n");
        rewind(consultaFile);
        TConsulta *consulta;

        while ((consulta = leConsulta(consultaFile)) != NULL) {
            // Verifique se a consulta possui o campo idPaciente
            // e ajuste a condição de comparação conforme necessário
            if (consulta->idPaciente == idPaciente) {
                printf("Data: %s\n", consulta->data);
                printf("Descrição: %s\n\n", consulta->descricao);
            }
            free(consulta);
        }

        // Exibir exames do paciente
        printf("\nExames Realizados:\n");
        rewind(exameFile);
        TExame *exame;

        while ((exame = leExame(exameFile)) != NULL) {
            // Verifique se o exame possui o campo idPaciente
            // e ajuste a condição de comparação conforme necessário
            if (exame->id_paciente == idPaciente) {
                printf("Data: %s\n", exame->data);
                printf("Tipo: %s\n", exame->tipo);
                printf("Resultado: %s\n\n", exame->resultado);
            }
            free(exame);
        }
    }

    // Limpar memória
    if (pacienteSeq) free(pacienteSeq);
    if (pacienteBin) free(pacienteBin);
}
