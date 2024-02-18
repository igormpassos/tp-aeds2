#ifndef CONSULTA_H
#define CONSULTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int idMedico;
    int idPaciente;
    char data[11];
    char descricao[200];
    int ocupado; // Flag para indicar se o registro está ocupado ou não
} TConsulta;

TConsulta *criaConsulta(int id, int idMedico, int idPaciente, char *data, char *descricao);

void salvaConsulta(TConsulta *consulta, FILE *out);

TConsulta *leConsulta(FILE *in);

void imprimeConsulta(TConsulta *consulta);

void criarBaseConsulta(FILE *out, int tam);

void imprimirBaseConsulta(FILE *out);

void criarBaseConsultaOrdenada(FILE *out, int tam);

#endif
