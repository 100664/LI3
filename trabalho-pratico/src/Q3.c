#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/Q3.h"
#include <ctype.h> 
#include "time.h"


GList* q3_main(GHashTable* hoteltable, char* id, int formatado){
    hotelInfo* hotel =(hotelInfo*) g_hash_table_lookup(hoteltable, id);
    int nAval =getNumeroAvaliacoes_HotelInfo(hotel);
    int avalT= getAvaliacaoTotal_HotelInfo(hotel);
    if(hotel == NULL || nAval == 0){
            GList* devolver = g_list_append(NULL, "0\n");
            return devolver;
    }

    double resultado =(avalT/(double)nAval);
        char* buffer = (char*)malloc(100);
    sprintf(buffer, "%.3f", resultado);
    if (formatado) {
        sprintf(buffer, "--- 1 ---\nrating: %.3f\n", resultado);
    }
    else sprintf(buffer, "%.3f\n", resultado);
    GList* lista = g_list_append(NULL, buffer);
    return lista;
}
