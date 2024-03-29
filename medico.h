#ifndef MEDICO_H
#define MEDICO_H

typedef struct {
    int crm;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    char especialidade[50];
} TMedico;

typedef struct {
    TMedico **dados; // Array de ponteiros para TMedico
    int capacidade;
    int tamanho;
} MinHeap;

typedef struct NoArvoreVencedores {
    TMedico *medico;
    int indiceArquivo; // Índice do arquivo de onde o médico veio
} NoArvoreVencedores;


TMedico *medico(int crm, char *nome, char *cpf, char *data_nascimento, char *especialidade);

void salvaMedico(TMedico *med, FILE *out);

TMedico *leMedico(FILE *in);

void imprimeMedico(TMedico *med);

void criarBaseMedico(FILE *out, int tam);

void imprimirBaseMedico(FILE *out);

void shuffle(int *vet, int MAX, int MIN);

void criarBaseMedicoOrdenada(FILE *out, int tam);

void divideAndSort(FILE *in, int blockSize);

void mergeSortedFiles(int numFiles, FILE *out);

#endif
