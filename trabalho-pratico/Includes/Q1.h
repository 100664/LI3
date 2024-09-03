#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"
#include "flights.h"
#include "users.h"


void calcularTotalGasto(gpointer data, gpointer user_data);
GList* q1_user(GHashTable* userInfo,char* id, int formatado);
GList* q1_voo(GHashTable* voos,char* id, int formatado);
GList* q1_reserva(GHashTable* reservas,char* id, int formatado);
GList* q1_main(GHashTable* reservas,GHashTable* voosTable, GHashTable* usersTable ,char* id, int formatado);
