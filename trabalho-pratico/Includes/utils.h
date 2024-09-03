// #define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <glib.h>
#include <stdbool.h>

#define diaAtual 1
#define mesAtual 10
#define anoAtual 2023

typedef struct catalog Catalog;

void freeCatalog(Catalog* catalog);
Catalog* createCatalog();
void setUsersTable_Catalog(Catalog* catalog, GHashTable* usersTable);
void setVoosTable_Catalog(Catalog* catalog, GHashTable* voosTable);
void setReservasTable_Catalog(Catalog* catalog, GHashTable* reservasTable);
void setAeroportosTable_Catalog(Catalog* catalog, GHashTable* aeroportosTable);
void setHoteisTable_Catalog(Catalog* catalog, GHashTable* hoteisTable);

GHashTable* getUsersTable_Catalog(Catalog* catalog);
GHashTable* getVoosTable_Catalog(Catalog* catalog);
GHashTable* getReservasTable_Catalog(Catalog* catalog);
GHashTable* getAeroportosTable_Catalog(Catalog* catalog);
GHashTable* getHoteisTable_Catalog(Catalog* catalog);


int organizarMaisRecenteListasDeDatas (gconstpointer a,gconstpointer b);
char* toUppper (char *s);
void escreveFicheiro(GList* lista, char* nomeFicheiro);
void escreveFicheiroToMenu(GList* lista, FILE* ficheiro);
char* toLower (char *s);
int calculateAge(struct tm* birthdate);
char* dateInStringCompleta(struct tm* time);
char* dateInStringSimples(struct tm* time);
int validar_data(char *data);
int validar_data_com_tempo(char *data);
int validar_email(char *email);
int validar_aeroporto(char *aeroporto);
int is_valid_integer(const char* str);
