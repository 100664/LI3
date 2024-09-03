#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <time.h>

typedef struct ficheiroReservations reservations;


reservations* createReserva ();
// Setters
void setReservationId_Reservations(char* reservationId, reservations* reservation);
void setUserId_Reservations(char* userId, reservations* reservation);
void setHotelId_Reservations(char* hotelId, reservations* reservation);
void setHotelName_Reservations(char* hotelName, reservations* reservation);
void setHotelStars_Reservations(int hotelStars, reservations* reservation);
void setCityTax_Reservations(int cityTax, reservations* reservation);
void setDataInicio_Reservations(char* dataInicio, reservations* reservation);
void setDataFim_Reservations(char* dataFim, reservations* reservation);
void setPricePerNight_Reservations(int pricePerNight, reservations* reservation);
void setIncludesBreakfast_Reservations(char* includesBreakfast, reservations* reservation);
void setRatingPeloUser_Reservations(int ratingPeloUser, reservations* reservation);

// Getters
char* getReservationId_Reservations(reservations* reservation);
char* getUserId_Reservations(reservations* reservation);
char* getHotelId_Reservations(reservations* reservation);
char* getHotelName_Reservations(reservations* reservation);
int getHotelStars_Reservations(reservations* reservation);
int getCityTax_Reservations(reservations* reservation);
struct tm* getDataInicio_Reservations(reservations* reservation);
struct tm* getDataFim_Reservations(reservations* reservation);
int getPricePerNight_Reservations(reservations* reservation);
char* getIncludesBreakfast_Reservations(reservations* reservation);
int getRatingPeloUser_Reservations(reservations* reservation);

void freeReservationsList(GList* reservationsList);
void freeReservations (reservations* res);
void free_reservations_hash_table(GHashTable* reservationsHashTable);

#endif /* RESERVATIONS_H */