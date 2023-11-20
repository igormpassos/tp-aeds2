#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "consulta.h"

TConsulta *consulta(int id, int id_medico, int id_paciente, char *data, char *descricao) {
    TConsulta *cons = (TConsulta *) malloc(sizeof(TConsulta));
    if (cons) memset(cons, 0, sizeof(TConsulta));
    cons->id = id;
    cons->id_medico = id_medico;
    cons->id_paciente = id_paciente;
    strcpy(cons->data, data);
    strcpy(cons->descricao, descricao);
    return cons;
}

void salvaConsulta(TConsulta *cons, FILE *out) {
    fwrite(&cons->id, sizeof(int), 1, out);
    fwrite(&cons->id_medico, sizeof(int), 1, out);
    fwrite(&cons->id_paciente, sizeof(int), 1, out);
    fwrite(cons->data, sizeof(char), sizeof(cons->data), out);
    fwrite(cons->descricao, sizeof(char), sizeof(cons->descricao), out);
}

TConsulta *leConsulta(FILE *in) {
    TConsulta *cons = (TConsulta *) malloc(sizeof(TConsulta));
    if (0 >= fread(&cons->id, sizeof(int), 1, in)) {
        free(cons);
        return NULL;
    }
    fread(&cons->id_medico, sizeof(int), 1, in);
    fread(&cons->id_paciente, sizeof(int), 1, in);
    fread(cons->data, sizeof(char), sizeof(cons->data), in);
    fread(cons->descricao, sizeof(char), sizeof(cons->descricao), in);
    return cons;
}

void imprimeConsulta(TConsulta *cons) {
    printf("**********************************************\n");
    printf("Consulta de ID %d\n", cons->id);
    printf("ID Médico: %d\n", cons->id_medico);
    printf("ID Paciente: %d\n", cons->id_paciente);
    printf("Data: %s\n", cons->data);
    printf("Descrição: %s\n", cons->descricao);
    printf("**********************************************\n");
}

void criarBaseConsulta(FILE *out, int tam) {
    int vet[tam];
    TConsulta *cons;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, (tam * 10) / 100);

    printf("\nGerando a base de dados de Consultas...\n");

    for (int i = 0; i < tam; i++) {
        cons = consulta(vet[i], vet[i], vet[i], "01/01/2022", "Consulta de Rotina");
        salvaConsulta(cons, out);
        free(cons);
    }
}

void imprimirBaseConsulta(FILE *out) {
    printf("\nImprimindo a base de dados de Consultas...\n");

    rewind(out);
    TConsulta *cons;

    while ((cons = leConsulta(out)) != NULL)
        imprimeConsulta(cons);

    free(cons);
}

void criarBaseConsultaOrdenada(FILE *out, int tam) {
    TConsulta *cons;

    printf("\nGerando a base de dados de Consultas Ordenada...\n");

    for (int i = 0; i < tam; i++) {
        cons = consulta(i, i, i, "01/01/2022", "Consulta de Rotina");
        salvaConsulta(cons, out);
        free(cons);
    }
}