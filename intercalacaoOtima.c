#include "intercalacaoOtima.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intercalacaoOtima(FILE *arquivo, int numParticoes) {
    // Array para armazenar os índices das partições
    int *indices = (int *)malloc(numParticoes * sizeof(int));

    // Array para armazenar os registros das partições
    TMedico *registros = (TMedico *)malloc(numParticoes * sizeof(TMedico));

    // Inicializa os índices e lê o primeiro registro de cada partição
    for (int i = 0; i < numParticoes; i++) {
        indices[i] = 0;
        fseek(arquivo, i * sizeof(TMedico), SEEK_SET);
        fread(&registros[i], sizeof(TMedico), 1, arquivo);
    }

    // Intercalação ótima
    int posicaoAtual = 0;
    while (1) {
        int menorIndice = -1;

        // Encontra o menor registro dentre os registros atuais
        for (int i = 0; i < numParticoes; i++) {
            if (indices[i] >= 0) {
                if (menorIndice == -1 || registros[i].crm < registros[menorIndice].crm) {
                    menorIndice = i;
                }
            }
        }

        if (menorIndice == -1) {
            // Todos os registros foram processados
            break;
        }

        // Escreve o menor registro no arquivo de saída
        fseek(arquivo, posicaoAtual * sizeof(TMedico), SEEK_SET);
        fwrite(&registros[menorIndice], sizeof(TMedico), 1, arquivo);

        // Lê o próximo registro da partição correspondente
        if (fread(&registros[menorIndice], sizeof(TMedico), 1, arquivo) == 0) {
            // Se a partição está totalmente lida, marca o índice como negativo
            indices[menorIndice] = -1;
        }

        // Atualiza a posição no arquivo de saída
        posicaoAtual++;
    }

    free(indices);
    free(registros);
}
