#pragma once
#include "parseFicheiroReservations.h"
#include "parseFicheiroUsers.h"
#include "parseFicheiroFlights.h"
#include "parseFicheiroPassengers.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include <stdio.h>
#include <stdlib.h>
#include "writeOutput.h"

typedef struct QHelper QueryInfo;

double calculateAverageTime(int query_num, QueryInfo* query_infos);
void calcularQueries(Catalog* catalogo, char* input, int printarTempoExec);
