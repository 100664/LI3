#ifndef USERS_H
#define USERS_H


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"
#include "flights.h"


typedef struct ficheiroUsers userInfo;


userInfo* createUser();
// Setters
void setId_Users(char* id, userInfo* user);
void setNome_Users(char* nome, userInfo* user);
void setEmail_Users(char* email, userInfo* user);
void setTelemovel_Users(char* telemovel, userInfo* user);
void setDNascimento_Users(char* dNascimento, userInfo* user);
void setSexo_Users(char* sexo, userInfo* user);
void setNPassaporte_Users(char* nPassaporte, userInfo* user);
void setCountryCode_Users(char* countryCode, userInfo* user);
void setDCriacaoConta_Users(char* dCriacaoConta, userInfo* user);
void setAccountStatus_Users(char* accountStatus, userInfo* user);
void setListaVoos_Users(GList* listaVoos, userInfo* user);
void setListaReservas_Users(GList* listaReservas, userInfo* user);

// Getters
char* getId_Users(userInfo* user);
char* getNome_Users(userInfo* user);
char* getEmail_Users(userInfo* user);
char* getTelemovel_Users(userInfo* user);
struct tm* getDNascimento_Users(userInfo* user);
char* getSexo_Users(userInfo* user);
char* getNPassaporte_Users(userInfo* user);
char* getCountryCode_Users(userInfo* user);
struct tm* getDCriacaoConta_Users(userInfo* user);
char* getAccountStatus_Users(userInfo* user);
GList* getListaVoos_Users(userInfo* user);
GList* getListaReservas_Users(userInfo* user);

void addToReservas_Users(userInfo* user, reservations* reserva);
void addToVoos_Users(userInfo* user, char* voo);
void freeDaListaVoos(GList* listaVoos);
void free_user_hash_table(GHashTable* hash_table);
#endif /* USERS_H */
