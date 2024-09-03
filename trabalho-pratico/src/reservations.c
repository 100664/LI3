#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/reservations.h"
#include <ctype.h> 

//funções para criar e libertar memória de uma reserva 
struct ficheiroReservations {
    char* reservationId;
    char* userId;
    char* hotelId;
    char* hotelName;
    int hotelStars;
    int cityTax;
    struct tm* dataInicio;
    struct tm* dataFim;
    int pricePerNight;
    char* includesBreakfast;
    int ratingPeloUser;
};

reservations* createReserva (){
    reservations* reserva = malloc(sizeof(struct ficheiroReservations));
    reserva->reservationId = NULL;
    reserva->userId = NULL;
    reserva->hotelId = NULL;
    reserva->hotelName = NULL;
    reserva->hotelStars = 0;
    reserva->cityTax = 0;
    reserva->dataInicio = NULL;
    reserva->dataFim = NULL;
    reserva->pricePerNight = 0;
    reserva->includesBreakfast = NULL;
    reserva->ratingPeloUser = 0;
    return reserva;
}

void setReservationId_Reservations(char* reservationId, reservations* reservation){
    reservation->reservationId = strdup(reservationId);
}

void setUserId_Reservations(char* userId, reservations* reservation){
    reservation->userId = strdup(userId);
}

void setHotelId_Reservations(char* hotelId, reservations* reservation){
    reservation->hotelId = strdup(hotelId);
}

void setHotelName_Reservations(char* hotelName, reservations* reservation){
    reservation->hotelName = strdup(hotelName);
}

void setHotelStars_Reservations(int hotelStars, reservations* reservation){
    reservation->hotelStars = hotelStars;
}

void setCityTax_Reservations(int cityTax, reservations* reservation){
    reservation->cityTax = cityTax;
}

void setDataInicio_Reservations(char* dataInicio, reservations* reservation){
    reservation->dataInicio = malloc(sizeof(struct tm));
    memset(reservation->dataInicio, 0, sizeof(struct tm));
    strptime(dataInicio, "%Y/%m/%d", reservation->dataInicio);
}

void setDataFim_Reservations(char* dataFim, reservations* reservation){
    reservation->dataFim = malloc(sizeof(struct tm));
    memset(reservation->dataFim, 0, sizeof(struct tm));
    strptime(dataFim, "%Y/%m/%d", reservation->dataFim);
}

void setPricePerNight_Reservations(int pricePerNight, reservations* reservation){
    reservation->pricePerNight = pricePerNight;
}

void setIncludesBreakfast_Reservations(char* includesBreakfast, reservations* reservation){
    reservation->includesBreakfast = strdup(includesBreakfast);
}

void setRatingPeloUser_Reservations(int ratingPeloUser, reservations* reservation){
    reservation->ratingPeloUser = ratingPeloUser;
}


char* getReservationId_Reservations(reservations* reservation){
    return strdup(reservation->reservationId);
}

char* getUserId_Reservations(reservations* reservation){
    return strdup(reservation->userId);
}

char* getHotelId_Reservations(reservations* reservation){
    return strdup(reservation->hotelId);
}

char* getHotelName_Reservations(reservations* reservation){
    return strdup(reservation->hotelName);
}

int getHotelStars_Reservations(reservations* reservation){
    return reservation->hotelStars;
}

int getCityTax_Reservations(reservations* reservation){
    return reservation->cityTax;
}


struct tm* getDataInicio_Reservations(reservations* reservation){
    return reservation->dataInicio;
}

struct tm* getDataFim_Reservations(reservations* reservation){
    return reservation->dataFim;
}

int getPricePerNight_Reservations(reservations* reservation){
    return reservation->pricePerNight;
}

char* getIncludesBreakfast_Reservations(reservations* reservation){
    return strdup(reservation->includesBreakfast);
}

int getRatingPeloUser_Reservations(reservations* reservation){
    return reservation->ratingPeloUser;
}



void freeReservationsList(GList* reservationsList) {
    GList* current = reservationsList;
    while (current != NULL) {
        reservations* reservation = (reservations*)current->data;
        freeReservations(reservation);
        current = g_list_next(current);
    }
    g_list_free(reservationsList);
}


void freeReservations (reservations* res){
    if (res == NULL) return;
    if (res->reservationId != NULL) free(res->reservationId);
    if (res->userId != NULL) free(res->userId);
    if (res->hotelId != NULL) free(res->hotelId);
    if (res->hotelName != NULL) free(res->hotelName);
    if (res->dataInicio != NULL) free(res->dataInicio);
    if (res->dataFim != NULL) free(res->dataFim);
    if (res->includesBreakfast != NULL) free(res->includesBreakfast);
    free(res);
}

void free_reservations_hash_table(GHashTable* reservationsHashTable) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, reservationsHashTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        reservations* reservation = (reservations*) value;
        g_free(key);
        freeReservations(reservation);
        
    }

    g_hash_table_destroy(reservationsHashTable);
}
