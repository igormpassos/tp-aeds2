#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "exame.h"

TExame *exame(int id, int id_paciente, char *data, char *tipo, char *resultado) {
    TExame *exam = (TExame *) malloc(sizeof(TExame));
    if (exam) memset(exam, 0, sizeof(TExame));
    exam->id = id;
    exam->id_paciente = id_paciente;
    strcpy(exam->data, data);
    strcpy(exam->tipo, tipo);
    strcpy(exam->resultado, resultado);
    return exam;
}

void salvaExame(TExame *exam, FILE *out) {
    fwrite(&exam->id, sizeof(int), 1, out);
    fwrite(&exam->id_paciente, sizeof(int), 1, out);
    fwrite(exam->data, sizeof(char), sizeof(exam->data), out);
    fwrite(exam->tipo, sizeof(char), sizeof(exam->tipo), out);
    fwrite(exam->resultado, sizeof(char), sizeof(exam->resultado), out);
}

TExame *leExame(FILE *in) {
    TExame *exam = (TExame *) malloc(sizeof(TExame));
    if (0 >= fread(&exam->id, sizeof(int), 1, in)) {
        free(exam);
        return NULL;
    }
    fread(&exam->id_paciente, sizeof(int), 1, in);
    fread(exam->data, sizeof(char), sizeof(exam->data), in);
    fread(exam->tipo, sizeof(char), sizeof(exam->tipo), in);
    fread(exam->resultado, sizeof(char), sizeof(exam->resultado), in);
    return exam;
}

void imprimeExame(TExame *exam) {
    printf("**********************************************\n");
    printf("Exame de ID %d\n", exam->id);
    printf("ID Paciente: %d\n", exam->id_paciente);
    printf("Data: %s\n", exam->data);
    printf("Tipo: %s\n", exam->tipo);
    printf("Resultado: %s\n", exam->resultado);
    printf("**********************************************\n");
}

void criarBaseExame(FILE *out, int tam) {
    int vet[tam];
    TExame *exam;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, (tam * 10) / 100);

    printf("\nGerando a base de dados de Exames...\n");

    for (int i = 0; i < tam; i++) {
        exam = exame(vet[i], vet[i], "01/01/2022", "Sangue", "Normal");
        salvaExame(exam, out);
        free(exam);
    }
}

void imprimirBaseExame(FILE *out) {
    printf("\nImprimindo a base de dados de Exames...\n");

    rewind(out);
    TExame *exam;

    while ((exam = leExame(out)) != NULL)
        imprimeExame(exam);

    free(exam);
}
