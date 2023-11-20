#include <stdio.h>
#include <stdlib.h>
#include "medico.c"
#include "paciente.c"
#include "consulta.c"
#include "exame.c"

int main() {
    FILE *medicoFile = fopen("medicos.dat", "w+b");
    FILE *pacienteFile = fopen("pacientes.dat", "w+b");
    FILE *consultaFile = fopen("consultas.dat", "w+b");
    FILE *exameFile = fopen("exames.dat", "w+b");

    if (!medicoFile || !pacienteFile || !consultaFile || !exameFile) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    int tamBase = 10;

    criarBaseMedico(medicoFile, tamBase);
    fflush(medicoFile); // Garante que os dados sejam gravados no arquivo antes de imprimir

    criarBasePaciente(pacienteFile, tamBase);
    fflush(pacienteFile);

    criarBaseConsulta(consultaFile, tamBase);
    fflush(consultaFile);

    criarBaseExame(exameFile, tamBase);
    fflush(exameFile);

    imprimirBaseMedico(medicoFile);
    imprimirBasePaciente(pacienteFile);
    imprimirBaseConsulta(consultaFile);
    imprimirBaseExame(exameFile);

    fclose(medicoFile);
    fclose(pacienteFile);
    fclose(consultaFile);
    fclose(exameFile);

    return 0;
}
