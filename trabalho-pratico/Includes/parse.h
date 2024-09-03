
#include "parseFicheiroReservations.h"
#include "parseFicheiroUsers.h"
#include "parseFicheiroFlights.h"
#include "parseFicheiroPassengers.h"
#include "calcularQueries.h"
#include <stdio.h>
#include <stdlib.h>
#include "writeOutput.h"

Catalog* parseDataSet(char* caminhoDosFIcheiros);
