#include "buscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>

TMedico *buscarBinariaMedico(FILE *arquivo, int crm, int *comparacoes) {
    TMedico *resultado = (TMedico *)malloc(sizeof(TMedico));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    int inicio = 0, fim, meio;
    fseek(arquivo, 0, SEEK_END);
    fim = ftell(arquivo) / sizeof(TMedico) - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TMedico), SEEK_SET);
        fread(resultado, sizeof(TMedico), 1, arquivo);
        (*comparacoes)++;

        if (resultado->crm == crm) {
            return resultado;
        } else if (resultado->crm < crm) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    free(resultado);
    return NULL;
}

TPaciente *buscarBinariaPaciente(FILE *arquivo, int id, int *comparacoes) {
    TPaciente *resultado = (TPaciente *)malloc(sizeof(TPaciente));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    int inicio = 0, fim, meio;
    fseek(arquivo, 0, SEEK_END);
    fim = ftell(arquivo) / sizeof(TPaciente) - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TPaciente), SEEK_SET);
        fread(resultado, sizeof(TPaciente), 1, arquivo);
        (*comparacoes)++;

        if (resultado->id == id) {
            return resultado;
        } else if (resultado->id < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    free(resultado);
    return NULL;
}

TConsulta *buscarBinariaConsulta(FILE *arquivo, int id, int *comparacoes) {
    TConsulta *resultado = (TConsulta *)malloc(sizeof(TConsulta));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    int inicio = 0, fim, meio;
    fseek(arquivo, 0, SEEK_END);
    fim = ftell(arquivo) / sizeof(TConsulta) - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TConsulta), SEEK_SET);
        fread(resultado, sizeof(TConsulta), 1, arquivo);
        (*comparacoes)++;

        if (resultado->id == id) {
            return resultado;
        } else if (resultado->id < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    free(resultado);
    return NULL;
}

TExame *buscarBinariaExame(FILE *arquivo, int id, int *comparacoes) {
    TExame *resultado = (TExame *)malloc(sizeof(TExame));
    if (resultado == NULL) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    *comparacoes = 0;
    int inicio = 0, fim, meio;
    fseek(arquivo, 0, SEEK_END);
    fim = ftell(arquivo) / sizeof(TExame) - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TExame), SEEK_SET);
        fread(resultado, sizeof(TExame), 1, arquivo);
        (*comparacoes)++;

        if (resultado->id == id) {
            return resultado;
        } else if (resultado->id < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    free(resultado);
    return NULL;
}
