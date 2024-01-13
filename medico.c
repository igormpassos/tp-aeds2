#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
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
#define TEMP_FILE_PREFIX "temp/temp_"

int compareMedicos(const void *a, const void *b) {
    TMedico *medA = (TMedico *)a;
    TMedico *medB = (TMedico *)b;
    return medA->crm - medB->crm;
}

/**
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

        if (numMedicos == 0) {
            printf("Nenhum medico lido, terminando a criacao de arquivos temporarios.\n");
            break;
        }

        printf("Processando %d medicos...\n", numMedicos);
        qsort(medBuffer, numMedicos, sizeof(TMedico), compareMedicos);

        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, tempFileCounter++);
        printf("Criando arquivo temporario: %s\n", tempFileName);

        FILE *tempFile = fopen(tempFileName, "wb");
        if (tempFile == NULL) {
            perror("Erro ao abrir arquivo temporario");
            exit(EXIT_FAILURE); // Ou lide com o erro de forma adequada
        }

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
    TMedico *tempMedicos[numFiles]; // Array de ponteiros para TMedico
    int activeFiles = numFiles;
    char tempFileName[50];

    // Inicializa os arquivos temporários e lê o primeiro elemento de cada um
    for (int i = 0; i < numFiles; i++) {
        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, i);
        tempFiles[i] = fopen(tempFileName, "rb");
        tempMedicos[i] = leMedico(tempFiles[i]);
        if (tempMedicos[i] == NULL) {
            fclose(tempFiles[i]);
            tempFiles[i] = NULL;
            activeFiles--;
        }
    }

    while (activeFiles > 0) {
        int minIndex = -1;
        TMedico *minMedico = NULL;

        // Encontra o menor médico entre os primeiros de cada arquivo
        for (int i = 0; i < numFiles; i++) {
            if (tempFiles[i] && (minMedico == NULL || tempMedicos[i]->crm < minMedico->crm)) {
                minMedico = tempMedicos[i];
                minIndex = i;
            }
        }

        // Salva o menor médico encontrado no arquivo de saída
        if (minIndex != -1) {
            salvaMedico(minMedico, out);
            free(tempMedicos[minIndex]); // Libera a memória alocada por leMedico

            // Lê o próximo médico do arquivo
            tempMedicos[minIndex] = leMedico(tempFiles[minIndex]);
            if (tempMedicos[minIndex] == NULL) {
                fclose(tempFiles[minIndex]);
                tempFiles[minIndex] = NULL;
                activeFiles--;
            }
        }
    }

    // Limpeza final
    for (int i = 0; i < numFiles; i++) {
        if (tempMedicos[i]) free(tempMedicos[i]);
        if (tempFiles[i]) fclose(tempFiles[i]);
        sprintf(tempFileName, "%s%d", TEMP_FILE_PREFIX, i);
        remove(tempFileName);
    }
}

MinHeap *criaMinHeap(int capacidade) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->dados = (TMedico **)malloc(capacidade * sizeof(TMedico *));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    return heap;
}

void insereHeap(MinHeap *heap, TMedico *med) {
    if (heap->tamanho == heap->capacidade) return; // Heap cheio

    heap->dados[heap->tamanho] = med;
    int i = heap->tamanho;
    heap->tamanho++;

    // Restaura a propriedade do min-heap
    while (i != 0 && heap->dados[(i - 1) / 2]->crm > heap->dados[i]->crm) {
        TMedico *temp = heap->dados[(i - 1) / 2];
        heap->dados[(i - 1) / 2] = heap->dados[i];
        heap->dados[i] = temp;
        i = (i - 1) / 2;
    }
}

TMedico *removeMin(MinHeap *heap) {
    if (heap->tamanho <= 0) return NULL;
    if (heap->tamanho == 1) {
        heap->tamanho--;
        return heap->dados[0];
    }

    TMedico *raiz = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;

    // Restaura a propriedade do min-heap
    int i = 0;
    while (i < heap->tamanho) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int menor = i;

        if (esq < heap->tamanho && heap->dados[esq]->crm < heap->dados[menor]->crm) menor = esq;
        if (dir < heap->tamanho && heap->dados[dir]->crm < heap->dados[menor]->crm) menor = dir;

        if (menor != i) {
            TMedico *temp = heap->dados[i];
            heap->dados[i] = heap->dados[menor];
            heap->dados[menor] = temp;
            i = menor;
        } else {
            break;
        }
    }

    return raiz;
}

void liberaHeap(MinHeap *heap) {
    free(heap->dados);
    free(heap);
}

// Função para gerar partições ordenadas de seleção natural
void geraParticoesOrdenadasSelecaoNatural(FILE *in, int tamanhoBloco) {
    MinHeap *heap = criaMinHeap(tamanhoBloco);
    int numParticao = 0;
    char nomeArquivo[256];
    FILE *out = NULL;
    TMedico *med;

    while ((med = leMedico(in)) != NULL) {
        insereHeap(heap, med);

        if (heap->tamanho == tamanhoBloco) {
            sprintf(nomeArquivo, "temp/particao_%d", numParticao++);
            out = fopen(nomeArquivo, "wb");

            while (heap->tamanho > 0) {
                med = removeMin(heap);
                salvaMedico(med, out);
                free(med);
            }

            fclose(out);
        }
    }

    // Processa quaisquer elementos restantes no heap
    if (heap->tamanho > 0) {
        sprintf(nomeArquivo, "temp/particao_%d", numParticao);
        out = fopen(nomeArquivo, "wb");

        while (heap->tamanho > 0) {
            med = removeMin(heap);
            salvaMedico(med, out);
            free(med);
        }

        fclose(out);
    }

    liberaHeap(heap);
}

void intercalaArvoreVencedores(FILE **arquivosEntrada, int numArquivos, FILE *arquivoSaida) {
    MinHeap *heap = criaMinHeap(numArquivos);
    NoArvoreVencedores *nos = malloc(numArquivos * sizeof(NoArvoreVencedores));

    // Inicializa a árvore de vencedores com o primeiro elemento de cada arquivo
    for (int i = 0; i < numArquivos; i++) {
        TMedico *med = leMedico(arquivosEntrada[i]);
        if (med != NULL) {
            nos[i].medico = med;
            nos[i].indiceArquivo = i;
            insereHeap(heap, &nos[i]);
        }
    }

    // Intercalação principal
    while (heap->tamanho > 0) {
        NoArvoreVencedores *vencedor = removeMin(heap);
        salvaMedico(vencedor->medico, arquivoSaida);

        // Lê o próximo médico do arquivo vencedor
        TMedico *proximoMed = leMedico(arquivosEntrada[vencedor->indiceArquivo]);
        if (proximoMed != NULL) {
            vencedor->medico = proximoMed;
            insereHeap(heap, vencedor);
        }
    }

    // Limpeza
    free(nos);
    liberaHeap(heap);
}
