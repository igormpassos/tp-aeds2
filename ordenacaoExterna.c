#include "ordenacaoExterna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BLOCO 1000  // Tamanho do bloco em número de registros

void intercala(FILE *arquivo, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    TMedico *bloco1 = (TMedico *)malloc(n1 * sizeof(TMedico));
    TMedico *bloco2 = (TMedico *)malloc(n2 * sizeof(TMedico));

    // Leitura dos registros para os blocos
    fseek(arquivo, inicio * sizeof(TMedico), SEEK_SET);
    fread(bloco1, sizeof(TMedico), n1, arquivo);

    fseek(arquivo, (meio + 1) * sizeof(TMedico), SEEK_SET);
    fread(bloco2, sizeof(TMedico), n2, arquivo);

    // Intercalação dos blocos ordenados
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (bloco1[i].crm <= bloco2[j].crm) {
            fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
            fwrite(&bloco1[i], sizeof(TMedico), 1, arquivo);
            i++;
        } else {
            fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
            fwrite(&bloco2[j], sizeof(TMedico), 1, arquivo);
            j++;
        }
        k++;
    }

    // Copia os elementos restantes, se houver
    while (i < n1) {
        fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
        fwrite(&bloco1[i], sizeof(TMedico), 1, arquivo);
        i++;
        k++;
    }

    while (j < n2) {
        fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
        fwrite(&bloco2[j], sizeof(TMedico), 1, arquivo);
        j++;
        k++;
    }

    free(bloco1);
    free(bloco2);
}

void mergeSortExterno(FILE *arquivo, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        // Recursivamente ordena as duas metades
        mergeSortExterno(arquivo, inicio, meio);
        mergeSortExterno(arquivo, meio + 1, fim);

        // Intercala as partes ordenadas
        intercala(arquivo, inicio, meio, fim);
    }
}

void ordenacaoExterna(FILE *arquivo) {
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    int numRegistros = tamanho / sizeof(TMedico);

    // Divisão em blocos, ordenação e fusão
    for (int i = 0; i < numRegistros; i += TAM_BLOCO) {
        int fimBloco = i + TAM_BLOCO - 1;
        if (fimBloco >= numRegistros) {
            fimBloco = numRegistros - 1;
        }

        // Aplica o merge sort externo para cada bloco
        mergeSortExterno(arquivo, i, fimBloco);
    }
}
