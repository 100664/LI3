#pragma once
#include "users.h"
#include "aeroporto.h"
#include "utils.h"


vooInfo* parseFlightsCsvLine(char* linha, GHashTable* a);
void separateWordsVoos(Catalog* catalogo, char *ficheiro);