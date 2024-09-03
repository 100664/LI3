#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include "../Includes/users.h"

//funcoes para criar a struct e organizar a GHashTable de userInfo no ficheiro parseFicheiroUsers.c
struct ficheiroUsers {
    char* id; 
    char* nome;
    char* email;
    char* telemovel;
    struct tm* dNascimento; // mês aparece de 0 a 11 em todos os struct tm
    char* sexo;
    char* nPassaporte;
    char* countryCode;
    struct tm* dCriacaoConta;
    char* accountStatus;
    GList* listaVoos;
    GList* listaReservas;
};

userInfo* createUser(){
    userInfo* user = malloc(sizeof(userInfo));
    user->id = NULL;
    user->nome = NULL;
    user->email = NULL;
    user->telemovel = NULL;
    user->dNascimento = NULL;
    user->sexo = NULL;
    user->nPassaporte = NULL;
    user->countryCode = NULL;
    user->dCriacaoConta = NULL;
    user->accountStatus = NULL;
    user->listaVoos = NULL;
    user->listaReservas = NULL;
    return user;
}

void setId_Users(char* id, userInfo* user){
    user->id = strdup(id);
}

void setNome_Users(char* nome, userInfo* user){
    user->nome = strdup(nome);
}

void setEmail_Users(char* email, userInfo* user){
    user->email = strdup(email);
}

void setTelemovel_Users(char* telemovel, userInfo* user){
    user->telemovel = strdup(telemovel);
}

void setDNascimento_Users(char* a, userInfo* user){
    user->dNascimento = malloc(sizeof(struct tm));
    memset(user->dNascimento, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d", user->dNascimento);
}

void setSexo_Users(char* sexo, userInfo* user){
    user->sexo = strdup(sexo);
}

void setNPassaporte_Users(char* nPassaporte, userInfo* user){
    user->nPassaporte = strdup(nPassaporte);
}

void setCountryCode_Users(char* countryCode, userInfo* user){
    user->countryCode = strdup(countryCode);
}

void setDCriacaoConta_Users(char* a, userInfo* user){
    user->dCriacaoConta = malloc(sizeof(struct tm));
    memset(user->dCriacaoConta, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d", user->dCriacaoConta);
}


void setAccountStatus_Users(char* accountStatus, userInfo* user){
    user->accountStatus = strdup(accountStatus);
}

void setListaVoos_Users(GList* listaVoos, userInfo* user){
    user->listaVoos = listaVoos;
}

void setListaReservas_Users(GList* listaReservas, userInfo* user){
    user->listaReservas = listaReservas;
}






char* getId_Users(userInfo* user){
    return strdup(user->id);
}

char* getNome_Users(userInfo* user){
    return strdup(user->nome);
}

char* getEmail_Users(userInfo* user){
    return strdup(user->email);
}

char* getTelemovel_Users(userInfo* user){
    return strdup(user->telemovel);
}

struct tm* getDNascimento_Users(userInfo* user){
    return user->dNascimento;
}

char* getSexo_Users(userInfo* user){
    return strdup(user->sexo);
}

char* getNPassaporte_Users(userInfo* user){
    return strdup(user->nPassaporte);
}

char* getCountryCode_Users(userInfo* user){
    return strdup(user->countryCode);
}


struct tm* getDCriacaoConta_Users(userInfo* user){
    return user->dCriacaoConta;
}


char* getAccountStatus_Users(userInfo* user){
    return strdup(user->accountStatus);
}

GList* getListaVoos_Users(userInfo* user){
    return user->listaVoos;
}

GList* getListaReservas_Users(userInfo* user){
    return user->listaReservas;
}


void addToReservas_Users(userInfo* user, reservations* reserva) {
    user->listaReservas = g_list_prepend(user->listaReservas, reserva);
}

void addToVoos_Users(userInfo* user, char* voo) {
    user->listaVoos = g_list_prepend(user->listaVoos, voo);
}

void freeDaListaVoos(GList* listaVoos){
    GList* curr = listaVoos;
    for (; curr != NULL; curr = g_list_next(curr)) {
        char* voo = (char*) curr->data;
        free(voo);
    }
}

void free_user_hash_table(GHashTable* hash_table) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        userInfo* user = (userInfo*) value;
        free(user->id);
        free(user->nome);
        free(user->email);
        free(user->telemovel);
        free(user->sexo);
        free(user->nPassaporte);
        free(user->countryCode);
        free(user->dCriacaoConta);
        free(user->dNascimento);
        free(user->accountStatus);
        freeDaListaVoos(user->listaVoos);
        g_list_free(user->listaReservas);
        g_list_free(user->listaVoos);
        g_free(key);
        g_free(user);
        

    }
    g_hash_table_destroy(hash_table);
}
