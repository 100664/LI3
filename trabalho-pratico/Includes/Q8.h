#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "utils.h"
#include "reservations.h"

int calculateNights(struct tm* dateA, struct tm* dateB, struct tm* dateC, struct tm* dateD);
void calcularRevenue(gpointer data, gpointer user_data);
GList* q8_main(GHashTable* hoteltable, char* id, char* a , char* b, int formatado);
