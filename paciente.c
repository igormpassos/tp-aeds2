#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "paciente.h"

TPaciente *paciente(int id, char *nome, char *cpf, char *data_nascimento, char *endereco) {
    TPaciente *pac = (TPaciente *) malloc(sizeof(TPaciente));
    if (pac) memset(pac, 0, sizeof(TPaciente));
    pac->id = id;
    strcpy(pac->nome, nome);
    strcpy(pac->cpf, cpf);
    strcpy(pac->data_nascimento, data_nascimento);
    strcpy(pac->endereco, endereco);
    return pac;
}

void salvaPaciente(TPaciente *pac, FILE *out) {
    fwrite(&pac->id, sizeof(int), 1, out);
    fwrite(pac->nome, sizeof(char), sizeof(pac->nome), out);
    fwrite(pac->cpf, sizeof(char), sizeof(pac->cpf), out);
    fwrite(pac->data_nascimento, sizeof(char), sizeof(pac->data_nascimento), out);
    fwrite(pac->endereco, sizeof(char), sizeof(pac->endereco), out);
}

TPaciente *lePaciente(FILE *in) {
    TPaciente *pac = (TPaciente *) malloc(sizeof(TPaciente));
    if (0 >= fread(&pac->id, sizeof(int), 1, in)) {
        free(pac);
        return NULL;
    }
    fread(pac->nome, sizeof(char), sizeof(pac->nome), in);
    fread(pac->cpf, sizeof(char), sizeof(pac->cpf), in);
    fread(pac->data_nascimento, sizeof(char), sizeof(pac->data_nascimento), in);
    fread(pac->endereco, sizeof(char), sizeof(pac->endereco), in);
    return pac;
}

void imprimePaciente(TPaciente *pac) {
    printf("**********************************************\n");
    printf("Paciente de ID %d\n", pac->id);
    printf("Nome: %s\n", pac->nome);
    printf("CPF: %s\n", pac->cpf);
    printf("Data de Nascimento: %s\n", pac->data_nascimento);
    printf("Endereço: %s\n", pac->endereco);
    printf("**********************************************\n");
}

void criarBasePaciente(FILE *out, int tam) {
    int vet[tam];
    TPaciente *pac;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, (tam * 10) / 100);

    printf("\nGerando a base de dados de Pacientes...\n");

    for (int i = 0; i < tam; i++) {
        pac = paciente(vet[i], "Paciente", "000.000.000-00", "01/01/1980", "Endereço do Paciente");
        salvaPaciente(pac, out);
        free(pac);
    }
}

void imprimirBasePaciente(FILE *out) {
    printf("\nImprimindo a base de dados de Pacientes...\n");

    rewind(out);
    TPaciente *pac;

    while ((pac = lePaciente(out)) != NULL)
        imprimePaciente(pac);

    free(pac);
}

void criarBasePacienteOrdenada(FILE *out, int tam) {
    TPaciente *pac;

    printf("\nGerando a base de dados de Pacientes Ordenada...\n");

    for (int i = 0; i < tam; i++) {
        pac = paciente(i, "Paciente", "000.000.000-00", "01/01/1980", "Endereço do Paciente");
        salvaPaciente(pac, out);
        free(pac);
    }
}