#ifndef CONSULTA_H
#define CONSULTA_H

typedef struct {
    int id;
    int id_medico;
    int id_paciente;
    char data[11];
    char descricao[200];
} TConsulta;

TConsulta *consulta(int id, int id_medico, int id_paciente, char *data, char *descricao);

void salvaConsulta(TConsulta *cons, FILE *out);

TConsulta *leConsulta(FILE *in);

void imprimeConsulta(TConsulta *cons);

void criarBaseConsulta(FILE *out, int tam);

void imprimirBaseConsulta(FILE *out);

void criarBaseConsultaOrdenada(FILE *out, int tam);

#endif
