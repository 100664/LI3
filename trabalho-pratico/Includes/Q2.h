#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"
#include "flights.h"
#include "users.h"

// typedef struct vooOUreserva;

int organizarMaisAntigoReservas (gconstpointer a,gconstpointer b);
int organizarMaisAntigoVoos (gconstpointer a,gconstpointer b);

GList* q2_reservas(userInfo* user, int formatado);
GList* q2_voos (userInfo* user, GHashTable* voosTable, int formatado);
GList* q2_voosEreservas (userInfo* user, GHashTable* voosTable, int formatado);
int organizarMaisAntigoVoosEReservas (gconstpointer a,gconstpointer b);
GList* q2_main(GHashTable* userss, char* id, char* a, GHashTable* voosTable, int formatado);
