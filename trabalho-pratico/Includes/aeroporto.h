#ifndef AEROPORTO_H
#define AEROPORTO_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "flights.h"

typedef struct aeroporto aeroportoInfo;


aeroportoInfo* createAeroporto();
// Setters
void setNome_Aeroporto(aeroportoInfo* aeroporto, char* nome);
void setAtrasos_Aeroporto(aeroportoInfo* aeroporto, GList* atrasos);
void setVoos_Aeroporto(aeroportoInfo* aeroporto, GList* voos);
void setChegadas_Aeroporto(aeroportoInfo* aeroporto, GList* voos);
void setAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto, GList* atraso);


// Getters
char* getNome_Aeroporto(aeroportoInfo* aeroporto);
GList* getAtrasos_Aeroporto(aeroportoInfo* aeroporto);
GList* getVoos_Aeroporto(aeroportoInfo* aeroporto);
GList* getChegadas_Aeroporto(aeroportoInfo* aeroporto);
GList* getAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto);


void addToAtrasos_Aeroporto(aeroportoInfo* aero, vooInfo* voo);
void addToVoos_Aeroporto(aeroportoInfo* aero, vooInfo* voo);
void addToChegadas_Aeroporto(aeroportoInfo* aero, vooInfo* voo);
void addToAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto, int* atraso);


void free_aeroporto_hash_table(GHashTable* hash_table);

int organizarMaisRecenteVoo(gconstpointer a,gconstpointer b);
void organizarListasAeroportos (gpointer key, gpointer value, gpointer user_data);
int organizarListaAtrasos (gconstpointer a,gconstpointer b);

#endif /* AEROPORTO_H */