#include <stdio.h>
#include <stdlib.h>
#include "medico.c"
#include "paciente.c"
#include "consulta.c"
#include "exame.c"
#include "buscaSequencial.c"
#include "buscaBinaria.c"


void salvarLog(const char *entidade, int comparacoes, double tempo, int base) {
    FILE *logFile = fopen("log.txt", "a");
    if (!logFile) {
        perror("Erro ao abrir arquivo de log");
        exit(1);
    }

    fprintf(logFile, "Entidade: %s\n", entidade);
    fprintf(logFile, "Tamanho da base: %d\n\n", base);
    fprintf(logFile, "Numero de comparações: %d\n", comparacoes);
    fprintf(logFile, "Tempo de execucao: %lf segundos\n\n", tempo);

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

    // imprimirBaseMedico(medicoFile);
    // imprimirBasePaciente(pacienteFile);
    // imprimirBaseConsulta(consultaFile);
    // imprimirBaseExame(exameFile);


    //Busca Sequencial Medico ========================================

    int cod_busca;
    printf("\nDigite o CRM: ");
    scanf("%d", &cod_busca);

    int comparacoes;
    clock_t inicio, fim;

    // Busca em uma base de dados ordenada
    inicio = clock();
    TMedico *medEncontrado = buscarMedico(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (medEncontrado) {
        printf("Medico encontrado:\n\n");
        imprimeMedico(medEncontrado);
        free(medEncontrado);
    } else {
        printf("Medico não encontrado.\n\n");
    }

    printf("Numero de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Medico (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

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

    printf("Numero de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Paciente (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

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

    printf("Numero de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Consulta (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

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

    printf("Numero de comparações na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Exame (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Criando Bases Ordenadas ========================================

    criarBaseMedicoOrdenada(medicoFile, tamBase);
    criarBasePacienteOrdenada(pacienteFile, tamBase);
    criarBaseConsultaOrdenada(consultaFile, tamBase);
    criarBasePacienteOrdenada(exameFile, tamBase);

    //Imprimindo Bases Ordenadas ========================================

    // imprimirBaseMedico(medicoFile);
    // imprimirBasePaciente(pacienteFile);
    // imprimirBaseConsulta(consultaFile);
    // imprimirBaseExame(exameFile);

    //Busca Binária Medico ========================================

    printf("\nDigite o CRM: ");
    scanf("%d", &cod_busca);

    inicio = clock();
    TMedico *medEncontradoBin = buscarBinariaMedico(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (medEncontradoBin) {
        printf("Medico encontrado:\n\n");
        imprimeMedico(medEncontradoBin);
        free(medEncontradoBin);
    } else {
        printf("Medico não encontrado.\n\n");
    }

    printf("Número de comparações na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Medico (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Paciente ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    inicio = clock();
    TMedico *pacEncontradoBin = buscarBinariaPaciente(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (pacEncontradoBin) {
        printf("Paciente encontrado:\n\n");
        imprimePaciente(pacEncontradoBin);
        free(pacEncontradoBin);
    } else {
        printf("Paciente não encontrado.\n\n");
    }

    printf("Número de comparações na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Paciente (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Consulta ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    inicio = clock();
    TMedico *consEncontradoBin = buscarBinariaConsulta(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (consEncontradoBin) {
        printf("Consulta encontrado:\n\n");
        imprimeConsulta(consEncontradoBin);
        free(consEncontradoBin);
    } else {
        printf("Consulta não encontrado.\n\n");
    }

    printf("Número de comparações na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Consulta (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Exame ========================================

    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    inicio = clock();
    TMedico *examEncontradoBin = buscarBinariaExame(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (examEncontradoBin) {
        printf("Exame encontrado:\n\n");
        imprimeExame(examEncontradoBin);
        free(examEncontradoBin);
    } else {
        printf("Exame não encontrado.\n\n");
    }

    printf("Número de comparações na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Exame (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);


    //Fechando Arquivos ========================================

    fclose(medicoFile);
    fclose(pacienteFile);
    fclose(consultaFile);
    fclose(exameFile);

    return 0;
}
