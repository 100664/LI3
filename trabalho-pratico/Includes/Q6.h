#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "users.h"
#include "aeroporto.h"
#include "flights.h"


void meterAeroportosNaLista (gpointer key, gpointer value, gpointer user_data);
int organizarPorQuemTemMais (gconstpointer a,gconstpointer b);
GList* q6_main(GHashTable* aeroportos, char* ano, char* N, int formatado);
