#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "users.h"
#include "utils.h"

int ordenadarUsersNomeId (gconstpointer a,gconstpointer b);
void filtrarUsersPrefixo (gpointer key, gpointer value, gpointer user_data);
GList* q9_main(GHashTable* userInfo, char* prefixo, int formatado);