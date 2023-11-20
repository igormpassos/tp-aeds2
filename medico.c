#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "medico.h"

TMedico *medico(int crm, char *nome, char *cpf, char *data_nascimento, char *especialidade) {
    TMedico *med = (TMedico *) malloc(sizeof(TMedico));
    if (med) memset(med, 0, sizeof(TMedico));
    med->crm = crm;
    strcpy(med->nome, nome);
    strcpy(med->cpf, cpf);
    strcpy(med->data_nascimento, data_nascimento);
    strcpy(med->especialidade, especialidade);
    return med;
}

void salvaMedico(TMedico *med, FILE *out) {
    fwrite(&med->crm, sizeof(int), 1, out);
    fwrite(med->nome, sizeof(char), sizeof(med->nome), out);
    fwrite(med->cpf, sizeof(char), sizeof(med->cpf), out);
    fwrite(med->data_nascimento, sizeof(char), sizeof(med->data_nascimento), out);
    fwrite(med->especialidade, sizeof(char), sizeof(med->especialidade), out);
}

TMedico *leMedico(FILE *in) {
    TMedico *med = (TMedico *) malloc(sizeof(TMedico));
    if (0 >= fread(&med->crm, sizeof(int), 1, in)) {
        free(med);
        return NULL;
    }
    fread(med->nome, sizeof(char), sizeof(med->nome), in);
    fread(med->cpf, sizeof(char), sizeof(med->cpf), in);
    fread(med->data_nascimento, sizeof(char), sizeof(med->data_nascimento), in);
    fread(med->especialidade, sizeof(char), sizeof(med->especialidade), in);
    return med;
}

void imprimeMedico(TMedico *med) {
    printf("**********************************************\n");
    printf("Médico de CRM %d\n", med->crm);
    printf("Nome: %s\n", med->nome);
    printf("CPF: %s\n", med->cpf);
    printf("Data de Nascimento: %s\n", med->data_nascimento);
    printf("Especialidade: %s\n", med->especialidade);
    printf("**********************************************\n");
}

void criarBaseMedico(FILE *out, int tam) {
    int vet[tam];
    TMedico *med;

    for(int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, (tam * 10) / 100);

    printf("\nGerando a base de dados de Médicos...\n");

    for (int i = 0; i < tam; i++) {
        med = medico(vet[i], "Médico", "000.000.000-00", "01/01/1980", "Cardiologia");
        salvaMedico(med, out);
        free(med);
    }
}

void imprimirBaseMedico(FILE *out) {
    printf("\nImprimindo a base de dados de Médicos...\n");

    rewind(out);
    TMedico *med;

    while ((med = leMedico(out)) != NULL)
        imprimeMedico(med);

    free(med);
}

void shuffle(int *vet, int MAX, int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}
