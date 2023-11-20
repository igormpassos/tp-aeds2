#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

#include "medico.h"
#include "paciente.h"
#include "consulta.h"
#include "exame.h"
#include <stdio.h>

TMedico *buscarMedico(FILE *arquivo, int crm, int *comparacoes);
TPaciente *buscarPaciente(FILE *arquivo, int id, int *comparacoes);
TConsulta *buscarConsulta(FILE *arquivo, int id, int *comparacoes);
TExame *buscarExame(FILE *arquivo, int id, int *comparacoes);

#endif // BUSCASEQUENCIAL_H_INCLUDED
