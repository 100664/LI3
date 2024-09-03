#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "users.h"
#include "aeroporto.h"
#include "flights.h"


int organizarListaQ7 (gconstpointer a,gconstpointer b);

void listaDeAtrasos (gpointer key, gpointer value, gpointer user_data);

GList* q7_main(GHashTable* aeroportos, char* N, int formatado);