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
    fprintf(logFile, "Numero de comparacoes: %d\n", comparacoes);
    fprintf(logFile, "Tempo de execucao: %lf segundos\n\n", tempo);

    fclose(logFile);
}

int main() {
    int comparacoes;
    clock_t inicio, fim;

    FILE *medicoFile = fopen("medicos.dat", "w+b");
    FILE *pacienteFile = fopen("pacientes.dat", "w+b");
    FILE *consultaFile = fopen("consultas.dat", "w+b");
    FILE *exameFile = fopen("exames.dat", "w+b");

    if (!medicoFile || !pacienteFile || !consultaFile || !exameFile) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    //Criando Bases ========================================
    int tamBase = 100000;

    // Define o tamanho do bloco para a divisão e ordenação
    int tamanhoBloco = 100; // Num de registros por bloco

    // Numero de arquivos temporarios criados
    int numArquivosTemporarios = tamBase / tamanhoBloco;

    criarBaseMedico(medicoFile, tamBase);
    fflush(medicoFile); // Garante que os dados sejam gravados no arquivo antes de imprimir

    /**
     * PARTE 2 do trabalho
    */

    /** 
     * -----------------------------------
     * Questao 1
     * -----------------------------------
     */
    if (medicoFile == NULL) {
        perror("Erro ao abrir o arquivo de médicos");
        return 1;
    }

    rewind(medicoFile);
    // Divide e ordena o arquivo de médicos em blocos ordenados salvos em arquivos temporários
    divideAndSort(medicoFile, tamanhoBloco);

    // Fecha o arquivo de entrada
    fclose(medicoFile);

    // Abre o arquivo de saída para a mesclagem final
    FILE *arquivoSaida = fopen("medicos_merged.dat", "wb");
    if (arquivoSaida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    inicio = clock();
    // Mescla os arquivos temporários ordenados em um único arquivo ordenado
    mergeSortedFiles(numArquivosTemporarios, arquivoSaida);
    fim = clock();
    
    salvarLog("Medico (Ordenação em disco)", 0, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    // Fecha o arquivo de saída
    fclose(arquivoSaida);

    /**
     * ------------------------------------
     * Questão 2
     * ------------------------------------
    */
    FILE *in = fopen("medicos.dat", "rb");
    inicio = clock();
    geraParticoesOrdenadasSelecaoNatural(in, MAX_RECORDS_PER_BLOCK);
    fim = clock();
    
    // salvarLog("Medico (Partições ordenadas: Seleção Natural)", 0, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    fclose(in);

    /**
     * -------------------------------------
     * Questão 3
     * -------------------------------------
    */
    FILE *arquivosEntrada[numArquivosTemporarios];
    char nomeArquivo[256];

    for (int i = 0; i < numArquivosTemporarios; i++) {
        sprintf(nomeArquivo, "temp/particao_%d", i);
        arquivosEntrada[i] = fopen(nomeArquivo, "rb");
    }

    FILE *arquivoSaida = fopen("medicos_ordenados.dat", "wb");
    
    inicio = clock();
    intercalaArvoreVencedores(arquivosEntrada, numArquivosTemporarios, arquivoSaida);
    fim = clock();

    salvarLog("Medico (Intercalação: Arvore Binária de Vencedores)", 0, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);
    
    // Fechar arquivos
    for (int i = 0; i < numArquivosTemporarios; i++) {
        fclose(arquivosEntrada[i]);
    }
    fclose(arquivoSaida);

    return 0;

    /**
     * PARTE 1 do trabalho
    */
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

    printf("Numero de comparacoes na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Medico (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Sequencial Paciente ========================================

    printf("\n===== Busca Sequencial Paciente =====\n");
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

    printf("Numero de comparacoes na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Paciente (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Sequencial Consulta ========================================

    printf("\n===== Busca Sequencial Consulta =====\n");
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

    printf("Numero de comparacoes na busca sequencial: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Consulta (Busca Sequencial)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Sequencial Exame ========================================
    printf("\n===== Busca Sequencial Exame =====\n");
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

    printf("Numero de comparacoes na busca sequencial: %d\n", comparacoes);
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

    printf("\n===== Busca Binaria Medico =====\n");
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

    printf("Número de comparacoes na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Medico (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Paciente ========================================
    printf("\n===== Busca Binaria Paciente =====\n");

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

    printf("Número de comparacoes na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Paciente (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Consulta ========================================
    printf("\n===== Busca Binaria Consulta =====\n");
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

    printf("Número de comparacoes na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Consulta (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);

    //Busca Binária Exame ========================================
    printf("\n===== Busca Binaria Exame =====\n");
    printf("Digite o ID: ");
    scanf("%d", &cod_busca);

    inicio = clock();
    TExame *examEncontradoBin = buscarBinariaExame(medicoFile, cod_busca, &comparacoes);
    fim = clock();

    if (examEncontradoBin) {
        printf("Exame encontrado:\n\n");
        imprimeExame(examEncontradoBin);
        free(examEncontradoBin);
    } else {
        printf("Exame não encontrado.\n\n");
    }

    printf("Número de comparacoes na busca binaria: %d\n", comparacoes);
    printf("Tempo de execução: %lf segundos\n", ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    salvarLog("Exame (Busca Binária)", comparacoes, ((double)(fim - inicio)) / CLOCKS_PER_SEC, tamBase);


    //Fechando Arquivos ========================================

    fclose(medicoFile);
    fclose(pacienteFile);
    fclose(consultaFile);
    fclose(exameFile);

    return 0;
}
