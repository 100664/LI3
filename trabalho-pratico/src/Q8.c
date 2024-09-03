#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include "../Includes/Q8.h"
#include <ctype.h> 


int calculateNights(struct tm* dateA, struct tm* dateB, struct tm* dateC, struct tm* dateD) {
   
    time_t timeA = timegm(dateA);
    time_t timeB = timegm(dateB);
    time_t timeC = timegm(dateC);
    time_t timeD = timegm(dateD);

    double secondsAtoC = difftime(timeC, timeA);
    double secondsBtoD = difftime(timeD, timeB);
    double secondsBtoC = difftime(timeC, timeB);
    double secondsAtoD = difftime(timeD, timeA);
    double secondsCtoD = difftime(timeD, timeC);

    if(secondsBtoC > 0 || secondsAtoD < 0) return 0;
   
    if(secondsCtoD== 0 && secondsAtoC >= 0 && secondsBtoD <= 0) return 1;


     if(secondsAtoC >= 0 && secondsBtoD < 0){ // INTERVALO está entre as datas
        return((secondsCtoD / (60 * 60 * 24)));
    }
    
    if(secondsAtoC >= 0 && secondsBtoD <= 0){ // INTERVALO está entre as datas
        return((secondsCtoD / (60 * 60 * 24)) +1);
    }
    if(secondsAtoC <= 0 && secondsBtoD >= 0){ //INTERVALO engloba as datas
        return(difftime(timeB,timeA) / (60 * 60 * 24));
    }
    if(secondsAtoC <= 0 && secondsBtoD <= 0){ //INTERVALO Começa antes de A e acaba antes de B
        return(difftime(timeD,timeA) / (60 * 60 * 24)+1);
    }
    if(secondsAtoC >= 0 && secondsBtoD >= 0){ //INTERVALO Começa depois de A e acaba depois de B
        return(difftime(timeB,timeC) / (60 * 60 * 24));
    }    
    return 0;
}


void calcularRevenue(gpointer data, gpointer user_data){
    reservations* res = (reservations*)data;

    gpointer* dateRange = (gpointer*)user_data;
    struct tm* startDate = (struct tm*)dateRange[0];
    struct tm* endDate = (struct tm*)dateRange[1];

    struct tm* copyA = malloc(sizeof(struct tm));
    memcpy(copyA, getDataInicio_Reservations(res), sizeof(struct tm));
    struct tm* copyB = malloc(sizeof(struct tm));
    memcpy(copyB, getDataFim_Reservations(res), sizeof(struct tm));

    int numeroDeNoites = calculateNights(copyA, copyB, startDate, endDate);
    int precoPorNoite = getPricePerNight_Reservations(res);
    *((int*)dateRange[2]) += precoPorNoite * numeroDeNoites;    
    free(copyB);
    free(copyA);
}


GList* q8_main(GHashTable* hoteltable, char* id, char* a , char* b, int formatado){
    hotelInfo* hotel =(hotelInfo*) g_hash_table_lookup(hoteltable, id);


    struct tm* dataA = malloc(sizeof(struct tm));
    memset(dataA, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d", dataA);

    struct tm* dataB = malloc(sizeof(struct tm));
    memset(dataB, 0, sizeof(struct tm));
    strptime(b, "%Y/%m/%d", dataB);
    

    int resultado = 0;
    GList* copy = getReservas_HotelInfo(hotel);
    GList* head = copy;

    gpointer dateRange[] = {dataA, dataB, &resultado};
    g_list_foreach(copy, (GFunc)calcularRevenue, dateRange);
    // g_list_free(copy);       
    char* buffer = (char*)malloc(50);
    if (formatado) sprintf(buffer, "--- 1 ---\nrevenue: %d\n", resultado);
    else sprintf(buffer, "%d\n", resultado);


    free(dataA);
    free(dataB);

    setReservas_HotelInfo(head, hotel);
    return g_list_append(NULL,buffer);
}

