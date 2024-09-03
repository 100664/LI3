#pragma once
#include "users.h"
#include "hotel.h"
#include "utils.h"

reservations* parseReservationsCsvLine(char* linha, GHashTable* users, GHashTable* hotel);

void separateWordsReservas(Catalog* catalogo, char *ficheiro);
