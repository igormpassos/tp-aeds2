#include "consulta.h"

TConsulta *criaConsulta(int id, int idMedico, int idPaciente, char *data, char *descricao) {
    TConsulta *consulta = (TConsulta *) malloc(sizeof(TConsulta));
    if (consulta == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    consulta->id = id;
    consulta->idMedico = idMedico;
    consulta->idPaciente = idPaciente;
    strcpy(consulta->data, data);
    strcpy(consulta->descricao, descricao);
    consulta->ocupado = 1; // Define o registro como ocupado
    return consulta;
}

void salvaConsulta(TConsulta *consulta, FILE *out) {
    fwrite(consulta, sizeof(TConsulta), 1, out);
}

TConsulta *leConsulta(FILE *in) {
    TConsulta *consulta = (TConsulta *) malloc(sizeof(TConsulta));
    if (consulta == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    if (fread(consulta, sizeof(TConsulta), 1, in) != 1) {
        free(consulta);
        return NULL;
    }
    return consulta;
}

void imprimeConsulta(TConsulta *consulta) {
    printf("**********************************************\n");
    printf("Consulta de ID %d\n", consulta->id);
    printf("ID Médico: %d\n", consulta->idMedico);
    printf("ID Paciente: %d\n", consulta->idPaciente);
    printf("Data: %s\n", consulta->data);
    printf("Descrição: %s\n", consulta->descricao);
    printf("Ocupado: %d\n", consulta->ocupado);
    printf("**********************************************\n");
}

void criarBaseConsulta(FILE *out, int tam) {
    TConsulta *consulta;
    for (int i = 0; i < tam; i++) {
        consulta = criaConsulta(i + 1, (i + 1) * 10, (i + 1) * 100, "01/01/2022", "Consulta de Rotina");
        salvaConsulta(consulta, out);
        free(consulta);
    }
}

void imprimirBaseConsulta(FILE *out) {
    rewind(out);
    TConsulta *consulta;
    while ((consulta = leConsulta(out)) != NULL) {
        imprimeConsulta(consulta);
        free(consulta);
    }
}

void criarBaseConsultaOrdenada(FILE *out, int tam) {
    TConsulta *consulta;
    for (int i = 0; i < tam; i++) {
        consulta = criaConsulta(i, i * 10, i * 100, "01/01/2022", "Consulta de Rotina");
        salvaConsulta(consulta, out);
        free(consulta);
    }
}