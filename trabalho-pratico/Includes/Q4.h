#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "users.h"
#include "reservations.h"


int organizarMaisRecente (gconstpointer a,gconstpointer b);
GList* q4_main(GHashTable* hotelTable, char* id, int formatado);