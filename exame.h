#ifndef EXAME_H
#define EXAME_H

typedef struct {
    int id;
    int id_paciente;
    char data[11];
    char tipo[50];
    char resultado[200];
} TExame;

TExame *exame(int id, int id_paciente, char *data, char *tipo, char *resultado);

void salvaExame(TExame *exam, FILE *out);

TExame *leExame(FILE *in);

void imprimeExame(TExame *exam);

void criarBaseExame(FILE *out, int tam);

void imprimirBaseExame(FILE *out);

#endif
