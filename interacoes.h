#ifndef INTERACOES_H    
#define INTERACOES_H

#include "medico.h"
#include "paciente.h"
#include "consulta.h"
#include "exame.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"

#include <stdio.h>
#include <stdlib.h>

void agendarConsulta(FILE *medicoFile, FILE *pacienteFile, FILE *consultaFile, int crmMedico, int idPaciente, FILE *logFile);

void realizarExame(FILE *pacienteFile, FILE *exameFile, int idPaciente, FILE *logFile);

void visualizarHistoricoMedico(FILE *pacienteFile, FILE *consultaFile, FILE *exameFile, int idPaciente, FILE *logFile);

#endif
