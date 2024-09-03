#include "../Includes/Q4.h"
#include <ctype.h> 

int organizarMaisRecente (gconstpointer a,gconstpointer b){
    reservations* primeiro = (reservations*)a;
    reservations* segundo = (reservations*)b;

    struct tm* copyA = malloc(sizeof(struct tm));
    memcpy(copyA, getDataInicio_Reservations(primeiro), sizeof(struct tm));
    struct tm* copyB = malloc(sizeof(struct tm));
    memcpy(copyB, getDataInicio_Reservations(segundo), sizeof(struct tm));


    int diferencaTempo = difftime(mktime(copyA), mktime(copyB));
    free(copyA);
    free(copyB);
    if(diferencaTempo != 0) {
        return -diferencaTempo;
    }
    char* resID1 = getReservationId_Reservations(primeiro);
    char* resID2 = getReservationId_Reservations(segundo);
    int result = strcmp(resID1, resID2);
    free(resID1);
    free(resID2);
    return result;
}


GList* q4_main(GHashTable* hotelTable, char* id, int formatado){
    hotelInfo* hotel = (hotelInfo*) g_hash_table_lookup(hotelTable, id);
    if(hotel == NULL ){
        printf("hotel == null\n");
        return NULL;
    }
    if (g_list_length(getReservas_HotelInfo(hotel )) == 0){
        return NULL;
    }
    GList* resultado= getReservas_HotelInfo(hotel);
    resultado = g_list_sort(resultado, organizarMaisRecente);
    setReservas_HotelInfo(resultado,hotel);

    GList *curr = resultado;
    int i=1;
    GList* listaDeResultados = NULL;
    for (; curr != NULL; curr = g_list_next(curr)) {
        reservations *res = (reservations*) curr->data;
        char* idReserva =getReservationId_Reservations(res), *user_id = getUserId_Reservations(res);
        int rating = getRatingPeloUser_Reservations(res), precoPorNoite = getPricePerNight_Reservations(res);
        struct tm* dataI = malloc(sizeof(struct tm));
        memcpy(dataI, getDataInicio_Reservations(res), sizeof(struct tm));
        struct tm* dataF = malloc(sizeof(struct tm));
        memcpy(dataF, getDataFim_Reservations(res), sizeof(struct tm));
        
        int numeroDeNoites = difftime(mktime(dataF), mktime(dataI))/ (60 * 60 * 24);
        int cityTax = getCityTax_Reservations(res);
        double total_price = (double)precoPorNoite * (double)numeroDeNoites + ((double)precoPorNoite * (double)numeroDeNoites / 100) *(double)cityTax ;  //preço_por_noite × número_de_noites + (preço_por_noite×número_de_noites /100) * cityTax;
        char* buffer = (char*)malloc(600);
        if (formatado && i!=1) sprintf(buffer, "\n--- %d ---\nid: %s\nbegin_date: %d/%02d/%02d\nend_date: %d/%02d/%02d\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n", i, idReserva, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataF->tm_year+1900, dataF->tm_mon+1, dataF->tm_mday, user_id, rating, total_price);
        else if (formatado) sprintf(buffer, "--- %d ---\nid: %s\nbegin_date: %d/%02d/%02d\nend_date: %d/%02d/%02d\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n", i, idReserva, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataF->tm_year+1900, dataF->tm_mon+1, dataF->tm_mday, user_id, rating, total_price);
        else sprintf(buffer, "%s;%d/%02d/%02d;%d/%02d/%02d;%s;%d;%.3f\n", idReserva, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataF->tm_year+1900, dataF->tm_mon+1, dataF->tm_mday, user_id, rating, total_price);
        i++;
        free(dataI);
        free(idReserva);
        free(user_id);
        free(dataF);
        listaDeResultados = g_list_append(listaDeResultados,buffer);
    }
    return listaDeResultados;
}
