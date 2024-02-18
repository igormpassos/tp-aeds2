#include <stdio.h>
#include <stdlib.h>
#include "medico.c"
#include "buscaBinaria.c"
#include "ordenacaoExterna.c"
#include "selecaoPorSubstituicao.c"
#include "intercalacaoOtima.c"
#include <time.h>

void salvarLog(const char *entidade, double tempo, int base)
{
    FILE *logFile = fopen("logParteII.txt", "a");
    if (!logFile)
    {
        perror("Erro ao abrir arquivo de log");
        exit(1);
    }

    fprintf(logFile, "Entidade: %s\n", entidade);
    fprintf(logFile, "Tamanho da base: %d\n", base);
    fprintf(logFile, "Tempo de execucao: %lf segundos\n\n", tempo);
    fprintf(logFile, "=============================================\n\n");

    fclose(logFile);
}

int main()
{
    FILE *medicoFile = fopen("medicos.dat", "w+b");

    if (!medicoFile)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // Criando Base ========================================

    // Teste com diferentes tamanhos de base de dados
    int tamanhos[] = {1000, 5000, 10000};


    for (int i = 0; i < sizeof(tamanhos) / sizeof(tamanhos[0]); i++)
    {
        // Nome do arquivo de acordo com o tamanho da base
        char nomeArquivo[20];
        sprintf(nomeArquivo, "base_%d.dat", tamanhos[i]);

        // Abre o arquivo para leitura e escrita
        FILE *arquivo = fopen(nomeArquivo, "w+b");
        if (!arquivo)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }

        // Gera uma base de dados desordenada
        criarBaseMedico(arquivo, tamanhos[i]);
        fflush(arquivo); // Garante que os dados sejam gravados no arquivo antes de imprimir

        // Executa a ordenação externa (MergeSort)
        printf("\nOrdenação Externa para base de tamanho %d\n", tamanhos[i]);
        clock_t inicioOrdenacaoExterna = clock();
        ordenacaoExterna(arquivo);
        clock_t fimOrdenacaoExterna = clock();

        printf("Medico (Merge Sort): %lf segundos\n", ((double)(fimOrdenacaoExterna - inicioOrdenacaoExterna)) / CLOCKS_PER_SEC);
        salvarLog("Medico (Merge Sort)", ((double)(fimOrdenacaoExterna - inicioOrdenacaoExterna)) / CLOCKS_PER_SEC, tamanhos[i]);

        // Executa a Seleção por Substituição
        printf("\nSeleção por Substituição para base de tamanho %d\n", tamanhos[i]);
        clock_t inicioSelecaoPorSubstituicao = clock();
        selecaoPorSubstituicao(arquivo);
        clock_t fimSelecaoPorSubstituicao = clock();

        printf("Medico (Seleção por Substituição): %lf segundos\n",
               ((double)(fimSelecaoPorSubstituicao - inicioSelecaoPorSubstituicao)) / CLOCKS_PER_SEC);
        salvarLog("Medico (Seleção por Substituição)", ((double)(fimSelecaoPorSubstituicao - inicioSelecaoPorSubstituicao)) / CLOCKS_PER_SEC, tamanhos[i]);

        // Executa a intercalação ótima
        printf("\nIntercalação Ótima para base de tamanho %d\n", tamanhos[i]);
        clock_t inicioIntercalacaoOtima = clock();
        intercalacaoOtima(arquivo, tamanhos[i] / TAM_PARTICAO);
        clock_t fimIntercalacaoOtima = clock();

        printf("Medico (Intercalação Ótima): %lf segundos\n", ((double)(fimIntercalacaoOtima - inicioIntercalacaoOtima)) / CLOCKS_PER_SEC);
        salvarLog("Medico (Intercalação Ótima)", ((double)(fimIntercalacaoOtima - inicioIntercalacaoOtima)) / CLOCKS_PER_SEC, tamanhos[i]);

        // Fecha o arquivo
        fclose(arquivo);
    }


    return 0;
}
