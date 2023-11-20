#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    int id;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    char endereco[100];
} TPaciente;

TPaciente *paciente(int id, char *nome, char *cpf, char *data_nascimento, char *endereco);

void salvaPaciente(TPaciente *pac, FILE *out);

TPaciente *lePaciente(FILE *in);

void imprimePaciente(TPaciente *pac);

void criarBasePaciente(FILE *out, int tam);

void imprimirBasePaciente(FILE *out);

#endif
