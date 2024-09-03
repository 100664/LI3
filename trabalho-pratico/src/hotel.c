#include "../Includes/hotel.h"

//funções usadas no ficheiro parseFicheiroHotels.c para organizar/colocar as coisas na gashTable de hoteis

struct hotel {
    char* hotelId;
    char* hotelName;
    int pricePerNight;
    int cityTax;
    int numeroAvaliacoes;
    int avaliacaoTotal;
    GList* reservas;
};

struct hotel* createHotel(){
    struct hotel* hotel = malloc(sizeof(struct hotel));
    hotel->hotelId = NULL;
    hotel->hotelName = NULL;
    hotel->pricePerNight = 0;
    hotel->cityTax = 0;
    hotel->numeroAvaliacoes = 0;
    hotel->avaliacaoTotal = 0;
    hotel->reservas = NULL;
    return hotel;
}


void setHotelId_HotelInfo(char* hotelId, hotelInfo* hotel){
    hotel->hotelId = strdup(hotelId);
}

void setHotelName_HotelInfo(char* hotelName, hotelInfo* hotel){
    hotel->hotelName = strdup(hotelName);
}

void setPricePerNight_HotelInfo(int pricePerNight, hotelInfo* hotel){
    hotel->pricePerNight = pricePerNight;
}

void setCityTax_HotelInfo(int cityTax, hotelInfo* hotel){
    hotel->cityTax = cityTax;
}

void setNumeroAvaliacoes_HotelInfo(int numeroAvaliacoes, hotelInfo* hotel){
    hotel->numeroAvaliacoes = numeroAvaliacoes;
}

void setAvaliacaoTotal_HotelInfo(int avaliacaoTotal, hotelInfo* hotel){
    hotel->avaliacaoTotal = avaliacaoTotal;
}

void setReservas_HotelInfo(GList* reservas, hotelInfo* hotel){
    hotel->reservas = reservas;
}


char* getHotelId_HotelInfo(hotelInfo* hotel){
    return strdup(hotel->hotelId);
}

char* getHotelName_HotelInfo(hotelInfo* hotel){
    return strdup(hotel->hotelName);
}

int getPricePerNight_HotelInfo(hotelInfo* hotel){
    return hotel->pricePerNight;
}

int getCityTax_HotelInfo(hotelInfo* hotel){
    return hotel->cityTax;
}

int getNumeroAvaliacoes_HotelInfo(hotelInfo* hotel){
    return hotel->numeroAvaliacoes;
}

int getAvaliacaoTotal_HotelInfo(hotelInfo* hotel){
    return hotel->avaliacaoTotal;
}

GList* getReservas_HotelInfo(hotelInfo* hotel){
    return hotel->reservas;
}

//

void incrementNumeroAvaliacoes_HotelInfo(hotelInfo* hotel) {
    hotel->numeroAvaliacoes++;
}

void adicionarRatingPeloUser_HotelInfo(hotelInfo* hotel, int rating) {
    hotel->avaliacaoTotal+= rating;
}

void addToReservas_HotelInfo(hotelInfo* hotel, reservations* reserva) {
    hotel->reservas = g_list_prepend(hotel->reservas, reserva);
}

//função para libertar a memória da struct hotelInfo e das strings que estão lá dentro

void free_hotel_hash_table(GHashTable* hash_table) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        hotelInfo* hotel = (hotelInfo*) value;
        g_free(hotel->hotelId);
        g_free(hotel->hotelName);
        
        // GList *current = hotel->reservas;
        // while (current != NULL) {
        //     freeReservations(current->data);
        //     current = current->next;
        // }
        
        g_list_free(hotel->reservas);
        g_free(key);
        g_free(hotel);
    }
    g_hash_table_destroy(hash_table);
}
