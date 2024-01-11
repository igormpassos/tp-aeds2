#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "medico.h"
#include "<limits.h>"

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

void criarBaseMedicoOrdenada(FILE *out, int tam) {
    TMedico *med;

    printf("\nGerando a base de dados de Médicos Ordenada...\n");

    for (int i = 0; i < tam; i++) {
        med = medico(i, "Médico", "000.000.000-00", "01/01/1980", "Cardiologia");
        salvaMedico(med, out);
        free(med);
    }
}

/**
 * ------------------------------------------
 * PARTE 2 
 * ------------------------------------------
*/

#define MAX_RECORDS_PER_BLOCK 1000
#define TEMP_FILE_PREFIX "temp_"

int compareMedicos(const void *a, const void *b) {
    TMedico *medA = (TMedico *)a;
    TMedico *medB = (TMedico *)b;
    return medA->crm - medB->crm;
}

/**
 * 
 * Função para dividir e ordenar: Esta função lerá o arquivo de médicos em blocos, 
 * ordenará cada bloco na memória e escreverá os blocos ordenados em arquivos 
 * temporários.
*/
void divideAndSort(FILE *in, int blockSize) {
    TMedico medBuffer[blockSize];
    int numMedicos;
    int tempFileCounter = 0;
    char tempFileName[50];

    while (1) {
        numMedicos = 0;
        while (numMedicos < blockSize) {
            TMedico *med = leMedico(in);
            if (med == NULL) {
                break;
            }
            medBuffer[numMedicos++] = *med;
            free(med); // Libera a memória alocada por leMedico
        }

        if (numMedicos == 0) break;

        qsort(medBuffer, numMedicos, sizeof(TMedico), compareMedicos);

        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, tempFileCounter++);
        FILE *tempFile = fopen(tempFileName, "wb");
        for (int i = 0; i < numMedicos; i++) {
            salvaMedico(&medBuffer[i], tempFile);
        }
        fclose(tempFile);

        if (feof(in)) break;
    }
}

/**
 * Função de mesclagem: Esta função mesclará os arquivos temporários 
 * ordenados em um único arquivo ordenado.
*/
void mergeSortedFiles(int numFiles, FILE *out) {
    FILE *tempFiles[numFiles];
    TMedico tempMedicos[numFiles];
    int activeFiles = numFiles;
    char tempFileName[50];

    for (int i = 0; i < numFiles; i++) {
        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, i);
        tempFiles[i] = fopen(tempFileName, "rb");
        if (!leMedico(tempFiles[i])) {
            fclose(tempFiles[i]);
            activeFiles--;
        }
    }

    while (activeFiles > 0) {
        int minIndex = -1;
        TMedico minMedico;
        minMedico.crm = INT_MAX;

        for (int i = 0; i < numFiles; i++) {
            if (tempFiles[i] && tempMedicos[i].crm < minMedico.crm) {
                minMedico = tempMedicos[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            salvaMedico(&minMedico, out);
            if (!leMedico(tempFiles[minIndex])) {
                fclose(tempFiles[minIndex]);
                tempFiles[minIndex] = NULL;
                activeFiles--;
            }
        }
    }

    // Cleanup
    for (int i = 0; i < numFiles; i++) {
        if (tempFiles[i]) fclose(tempFiles[i]);
        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, i);
        remove(tempFileName);
    }
}
