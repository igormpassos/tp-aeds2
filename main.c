#include <stdio.h>
#include <stdlib.h>
#include "medico.c"
#include "paciente.c"
#include "consulta.c"
#include "exame.c"
#include "buscaSequencial.c"


void salvarLog(const char *entidade, int comparacoes, double tempo) {
    FILE *logFile = fopen("log.txt", "a");
    if (!logFile) {
        perror("Erro ao abrir arquivo de log");
        exit(1);
    }

    fprintf(logFile, "Entidade: %s\n", entidade);
    fprintf(logFile, "Número de comparações: %d\n", comparacoes);
    fprintf(logFile, "Tempo de execução: %lf segundos\n\n", tempo);

    fclose(logFile);
}

int main() {
    FILE *medicoFile = fopen("medicos.dat", "w+b");
    FILE *pacienteFile = fopen("pacientes.dat", "w+b");
    FILE *consultaFile = fopen("consultas.dat", "w+b");
    FILE *exameFile = fopen("exames.dat", "w+b");

    if (!medicoFile || !pacienteFile || !consultaFile || !exameFile) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    //Criando Bases ========================================

    int tamBase = 10;

    criarBaseMedico(medicoFile, tamBase);
    fflush(medicoFile); // Garante que os dados sejam gravados no arquivo antes de imprimir

    criarBasePaciente(pacienteFile, tamBase);
    fflush(pacienteFile);

    criarBaseConsulta(consultaFile, tamBase);
    fflush(consultaFile);

    criarBaseExame(exameFile, tamBase);
    fflush(exameFile);

    //Imprimindo Bases ========================================

    imprimirBaseMedico(medicoFile);
    imprimirBasePaciente(pacienteFile);
    imprimirBaseConsulta(consultaFile);
    imprimirBaseExame(exameFile);


    //Busca Sequencial Medico ========================================

    int cod_busca;
    printf("Digite o CRM: ");
    scanf("%d", &cod_busca);

    int comparacoes;
    clock_t inicio, fim;

    // Busca em uma base de dados ordenada
    inicio = clock();
    TMedico *medEncontrado = buscarMedico(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (medEncontrado) {
        printf("Médico encontrado:\n\n");
        imprimeMedico(medEncontrado);
        free(medEncontrado);
    } else {
        printf("Médico não encontrado.\n\n");
    }

    printf("Número de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Médico", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    //Busca Sequencial Paciente ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    // Busca em uma base de dados ordenada
    inicio = clock();
    TPaciente *pacEncontrado = buscarPaciente(pacienteFile, cod_busca, &comparacoes);
    fim = clock();

    if (pacEncontrado) {
        printf("Paciente encontrado:\n\n");
        imprimePaciente(pacEncontrado);
        free(pacEncontrado);
    } else {
        printf("Paciente não encontrado.\n\n");
    }

    printf("Número de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Paciente", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    //Busca Sequencial Consulta ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    // Busca em uma base de dados ordenada
    inicio = clock();
    TConsulta *consEncontrado = buscarConsulta(consultaFile, cod_busca, &comparacoes);
    fim = clock();

    if (consEncontrado) {
        printf("Consulta encontrado:\n\n");
        imprimeConsulta(consEncontrado);
        free(consEncontrado);
    } else {
        printf("Consulta não encontrado.\n\n");
    }

    printf("Número de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Consulta", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    //Busca Sequencial Exame ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    // Busca em uma base de dados ordenada
    inicio = clock();
    TExame *exaEncontrado = buscarExame(exameFile, cod_busca, &comparacoes);
    fim = clock();

    if (exaEncontrado) {
        printf("Exame encontrado:\n\n");
        imprimeExame(exaEncontrado);
        free(exaEncontrado);
    } else {
        printf("Exame não encontrado.\n\n");
    }

    printf("Número de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Exame", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC);


    fclose(medicoFile);
    fclose(pacienteFile);
    fclose(consultaFile);
    fclose(exameFile);

    return 0;
}
