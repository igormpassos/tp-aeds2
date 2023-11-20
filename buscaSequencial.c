#include "buscaSequencial.h"
#include <stdio.h>
#include <stdlib.h>

TMedico *buscarMedico(FILE *arquivo, int crm, int *comparacoes) {
    TMedico *resultado = (TMedico *)malloc(sizeof(TMedico));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    rewind(arquivo);

    while (fread(resultado, sizeof(TMedico), 1, arquivo)) {
        (*comparacoes)++;
        if (resultado->crm == crm) {
            return resultado;
        }
    }

    free(resultado);
    return NULL;
}

TPaciente *buscarPaciente(FILE *arquivo, int id, int *comparacoes) {
    TPaciente *resultado = (TPaciente *)malloc(sizeof(TPaciente));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    rewind(arquivo);

    while (fread(resultado, sizeof(TPaciente), 1, arquivo)) {
        (*comparacoes)++;
        if (resultado->id == id) {
            return resultado;
        }
    }

    free(resultado);
    return NULL;
}

TConsulta *buscarConsulta(FILE *arquivo, int id, int *comparacoes) {
    TConsulta *resultado = (TConsulta *)malloc(sizeof(TConsulta));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    rewind(arquivo);

    while (fread(resultado, sizeof(TConsulta), 1, arquivo)) {
        (*comparacoes)++;
        if (resultado->id == id) {
            return resultado;
        }
    }

    free(resultado);
    return NULL;
}

TExame *buscarExame(FILE *arquivo, int id, int *comparacoes) {
    TExame *resultado = (TExame *)malloc(sizeof(TExame));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    rewind(arquivo);

    while (fread(resultado, sizeof(TExame), 1, arquivo)) {
        (*comparacoes)++;
        if (resultado->id == id) {
            return resultado;
        }
    }

    free(resultado);
    return NULL;
}
