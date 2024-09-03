#pragma once
#include "users.h"
#include "aeroporto.h"


int parsePassengersCsvLine(char* linha, GHashTable* tableusers, GHashTable* voos);

void separateWordsPassageiros(Catalog* catalogo, char *ficheiro);
