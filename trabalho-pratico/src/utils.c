#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include "../Includes/utils.h"
#include <ctype.h>

struct catalog{
    GHashTable *usersTable;
    GHashTable *voosTable;
    GHashTable *reservasTable;
    GHashTable *aeroportosTable;
    GHashTable *hoteisTable;
};

void freeCatalog(Catalog* catalog){
    free(catalog);
}

struct catalog* createCatalog() {
    struct catalog* newCatalog = malloc(sizeof(struct catalog));
    if (newCatalog != NULL) {
        newCatalog->usersTable = g_hash_table_new(g_str_hash, g_str_equal);
        newCatalog->voosTable = g_hash_table_new(g_str_hash, g_str_equal);
        newCatalog->reservasTable = g_hash_table_new(g_str_hash, g_str_equal);
        newCatalog->aeroportosTable = g_hash_table_new(g_str_hash, g_str_equal);
        newCatalog->hoteisTable = g_hash_table_new(g_str_hash, g_str_equal);
    }
    return newCatalog;
}

void setUsersTable_Catalog(Catalog* catalog, GHashTable* usersTable){
    catalog->usersTable = usersTable;
}

void setVoosTable_Catalog(Catalog* catalog, GHashTable* voosTable){
    catalog->voosTable = voosTable;
}

void setReservasTable_Catalog(Catalog* catalog, GHashTable* reservasTable){
    catalog->reservasTable = reservasTable;
}

void setAeroportosTable_Catalog(Catalog* catalog, GHashTable* aeroportosTable){
    catalog->aeroportosTable = aeroportosTable;
}

void setHoteisTable_Catalog(Catalog* catalog, GHashTable* hoteisTable){
    catalog->hoteisTable = hoteisTable;
}

GHashTable* getUsersTable_Catalog(Catalog* catalog){
    return catalog->usersTable;
}

GHashTable* getVoosTable_Catalog(Catalog* catalog){
    return catalog->voosTable;
}

GHashTable* getReservasTable_Catalog(Catalog* catalog){
    return catalog->reservasTable;
}

GHashTable* getAeroportosTable_Catalog(Catalog* catalog){
    return catalog->aeroportosTable;
}

GHashTable* getHoteisTable_Catalog(Catalog* catalog){
    return catalog->hoteisTable;
}



int organizarMaisRecenteListasDeDatas (gconstpointer a,gconstpointer b){
    struct tm* primeiro = (struct tm*)a;
    struct tm* segundo = (struct tm*)b;
    return difftime(timegm(primeiro), timegm(segundo));
}



void escreveFicheiro(GList* lista, char* nomeFicheiro) {
    FILE* ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL) {
        perror("Error opening file\n");
        return;
    }

    for (GList* iter = lista; iter != NULL; iter = iter->next) {
        char* data = iter->data;
        fprintf(ficheiro, "%s", data);
        free(data);
    }
    g_list_free(lista);
    fclose(ficheiro);
}

void escreveFicheiroToMenu(GList* lista, FILE* ficheiro) {
    if (ficheiro == NULL) {
        perror("Error opening file\n");
        return;
    }

    for (GList* iter = lista; iter != NULL; iter = iter->next) {
        char* data = iter->data;
        fprintf(ficheiro, "%s", data);
        free(data);
    }
    g_list_free(lista);

}


//coloca a primeira letra de cada palavra em maiuscula

char* toUppper (char *s){
    for (int i = 0; i < strlen(s); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

//coloca todas as letras em minuscula

char* toLower (char *s){
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

//função que calcula a idade de uma pessoa

int calculateAge(struct tm* birthdate) {
    struct tm* birthDatee = malloc(sizeof(struct tm));
    birthDatee->tm_year = birthdate->tm_year;
    birthDatee->tm_mon = birthdate->tm_mon;
    birthDatee->tm_mday = birthdate->tm_mday;


    struct tm* current = malloc(sizeof(struct tm));
    current->tm_mon= mesAtual-1;
    current->tm_year=anoAtual;
    current->tm_mday=diaAtual;
    int age = current->tm_year - birthDatee->tm_year - 1900;
    if (current->tm_mon < birthDatee->tm_mon ||
        (current->tm_mon == birthDatee->tm_mon && current->tm_mday < birthDatee->tm_mday)) {
        age--;
    }
    free(birthDatee);
    free(current);

    return age;
}

//função que recebe um ponteiro para uma estrtura sobre o tempo e retorna uma string com a data no formato YYYY/MM/DD HH:MM:SS

char* dateInStringCompleta(struct tm* time){
    char* strTime = malloc(sizeof(char) * 20);
    sprintf(strTime, "%04d/%02d/%02d %02d:%02d:%02d",
    time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
    time->tm_hour, time->tm_min, time->tm_sec);
    return strTime;
}

//função que recebe um ponteiro para uma estrtura sobre o tempo e retorna uma string com a data no formato YYYY/MM/DD

char* dateInStringSimples(struct tm* time){
    char* strTime = malloc(sizeof(char) * 11);
    sprintf(strTime, "%04d/%02d/%02d",
    time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);
    return strTime;    
}

//função que valida se a data é ou não válida

int validar_data(char *data) {
    int ano, mes, dia;
    if (sscanf(data, "%4d/%04d/%04d", &ano, &mes, &dia) != 3) {
        return 0; 
    }

    if (ano < 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0; // Valores fora dos limites permitidos
    }

    return 1; // Data válida
}

//função que valida se a data com tempo é ou não válida

int validar_data_com_tempo(char *data) {
    int ano, mes, dia, hora, minuto, segundo;
    if (sscanf(data, "%4d/%2d/%2d %2d:%2d:%2d", &ano, &mes, &dia, &hora, &minuto, &segundo) != 6) {
        return 0; 
    }

    if (ano < 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31 || 
        hora < 0 || hora > 23 || minuto < 0 || minuto > 59 || segundo < 0 || segundo > 59) {
        return 0; 
    }

    return 1; // Data com tempo válida
}

//função que valida se o email é ou não válido

int validar_email(char *email) {
    char *arroba = strchr(email, '@');
    char *dot = strchr(email, '.');
    if (arroba == NULL || dot == NULL) {
        return 0;
    }
    if (arroba == email + 1 || dot == arroba + 1 || strlen(dot + 1) < 2) {
        return 0;
    }

    return 1; // E-mail válido
}

//função que valida se o número de telemóvel é ou não válido

int validar_aeroporto(char *aeroporto) {
    if (strlen(aeroporto) != 3) {
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        if (!isalpha(aeroporto[i])) {
            return 0;
        }
    }
    return 1; // Aeroporto válido
}

//função que valida se o número de telemóvel é ou não válido

int is_valid_integer(const char* str) {
    if (*str == '\0' || *str == '-') { 
        return 0;
    }

    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0; 
        }
        str++;
    }

    return 1;
}
