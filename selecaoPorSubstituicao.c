#include "selecaoPorSubstituicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PARTICAO 1000  // Tamanho da partição em número de registros

void selecaoPorSubstituicao(FILE *arquivo) {
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    int numRegistros = tamanho / sizeof(TMedico);

    // Número de partições
    int numParticoes = (numRegistros + TAM_PARTICAO - 1) / TAM_PARTICAO;

    // Criar arquivos temporários para as partições ordenadas
    FILE **tempFiles = (FILE **)malloc(numParticoes * sizeof(FILE *));
    char tempFileName[20];

    for (int i = 0; i < numParticoes; i++) {
        sprintf(tempFileName, "temp_particao_%d.dat", i);
        tempFiles[i] = fopen(tempFileName, "w+b");
        if (!tempFiles[i]) {
            perror("Erro ao criar arquivo temporário");
            exit(1);
        }
    }

    // Marca o início de cada partição
    for (int i = 0; i < numParticoes; i++) {
        int fimParticao = i * TAM_PARTICAO + TAM_PARTICAO - 1;
        if (fimParticao >= numRegistros) {
            fimParticao = numRegistros - 1;
        }

        // Mantém a partição ordenada
        for (int j = i * TAM_PARTICAO; j <= fimParticao; j++) {
            for (int k = j + 1; k <= fimParticao; k++) {
                TMedico medicoJ, medicoK;

                // Leitura dos registros
                fseek(arquivo, j * sizeof(TMedico), SEEK_SET);
                fread(&medicoJ, sizeof(TMedico), 1, arquivo);

                fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
                fread(&medicoK, sizeof(TMedico), 1, arquivo);

                // Comparação e troca se necessário
                if (medicoJ.crm > medicoK.crm) {
                    // Troca
                    fseek(arquivo, j * sizeof(TMedico), SEEK_SET);
                    fwrite(&medicoK, sizeof(TMedico), 1, arquivo);

                    fseek(arquivo, k * sizeof(TMedico), SEEK_SET);
                    fwrite(&medicoJ, sizeof(TMedico), 1, arquivo);
                }
            }
        }

        // Salvar a partição ordenada no arquivo temporário
        rewind(arquivo);
        fseek(arquivo, i * TAM_PARTICAO * sizeof(TMedico), SEEK_SET);

        for (int j = 0; j < TAM_PARTICAO; j++) {
            TMedico medico;
            fread(&medico, sizeof(TMedico), 1, arquivo);
            fwrite(&medico, sizeof(TMedico), 1, tempFiles[i]);
        }
    }

    // Fechar os arquivos temporários
    for (int i = 0; i < numParticoes; i++) {
        fclose(tempFiles[i]);
    }

    free(tempFiles);
}