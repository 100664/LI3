#ifndef HOTELS_H
#define HOTELS_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "reservations.h"



typedef struct hotel hotelInfo;


hotelInfo* createHotel();

// Setters
void setHotelId_HotelInfo(char* hotelId, hotelInfo* hotel);
void setHotelName_HotelInfo(char* hotelName, hotelInfo* hotel);
void setPricePerNight_HotelInfo(int pricePerNight, hotelInfo* hotel);
void setCityTax_HotelInfo(int cityTax, hotelInfo* hotel);
void setNumeroAvaliacoes_HotelInfo(int numeroAvaliacoes, hotelInfo* hotel);
void setAvaliacaoTotal_HotelInfo(int avaliacaoTotal, hotelInfo* hotel);
void setReservas_HotelInfo(GList* reservas, hotelInfo* hotel);

// Getters
char* getHotelId_HotelInfo(hotelInfo* hotel);
char* getHotelName_HotelInfo(hotelInfo* hotel);
int getPricePerNight_HotelInfo(hotelInfo* hotel);
int getCityTax_HotelInfo(hotelInfo* hotel);
int getNumeroAvaliacoes_HotelInfo(hotelInfo* hotel);
int getAvaliacaoTotal_HotelInfo(hotelInfo* hotel);
GList* getReservas_HotelInfo(hotelInfo* hotel);


void incrementNumeroAvaliacoes_HotelInfo(hotelInfo* hotel);
void adicionarRatingPeloUser_HotelInfo(hotelInfo* hotel, int rating);
void addToReservas_HotelInfo(hotelInfo* hotel, reservations* reserva);
void removeAllReservations_HotelInfo(hotelInfo* hotel);
void free_hotel_hash_table(GHashTable* hash_table);

#endif /* HOTELS_H */