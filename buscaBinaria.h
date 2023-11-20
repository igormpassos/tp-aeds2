#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include "medico.h"
#include "paciente.h"
#include "consulta.h"
#include "exame.h"
#include <stdio.h>

TMedico *buscarBinariaMedico(FILE *arquivo, int crm, int *comparacoes);
TPaciente *buscarBinariaPaciente(FILE *arquivo, int id, int *comparacoes);
TConsulta *buscarBinariaConsulta(FILE *arquivo, int id, int *comparacoes);
TExame *buscarBinariaExame(FILE *arquivo, int id, int *comparacoes);

#endif // BUSCABINARIA_H_INCLUDED
