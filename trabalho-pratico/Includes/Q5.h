#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "aeroporto.h"

int organizarMaisAntigo (gconstpointer a,gconstpointer b);
GList* q5_main(GHashTable* aeroportos, char* id, char* a, char* b, char* c, char* d, int formatado);