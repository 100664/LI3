#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/parseFicheiroPassengers.h"
#include <ctype.h> 

#include <time.h>

int parsePassengersCsvLine(char* linha, GHashTable* tableusers, GHashTable* voosTable) {

    char* idVoo, *userId;
    char* token;

    token = strsep(&linha, ";");
    if (token == NULL) return 0;
    idVoo = strdup(token);

    token = strsep(&linha, "\n");
    if (token == NULL) return 0;    
    userId = strdup(token);


    vooInfo* voo = (vooInfo*)g_hash_table_lookup(voosTable, idVoo);
    userInfo* userDaReserva = (userInfo*)g_hash_table_lookup(tableusers,userId);
    if (voo != NULL && userDaReserva !=NULL){
        incrementarNumPassageiros(voo);
        addToVoos_Users(userDaReserva,strdup(idVoo));
    } else {
        free(idVoo);
        free(userId);
        return 0;
    }
    free(idVoo);
    free(userId);
    return 1;
}

void separateWordsPassageiros(Catalog* catalogo, char *ficheiro) //"main" do ficheiro parseFicheiroPassengers.c
{
    GHashTable* userInfo= getUsersTable_Catalog(catalogo);
    GHashTable* voos= getVoosTable_Catalog(catalogo); 

    FILE *fp = fopen(ficheiro, "r"); //ficheiro a ler 
    if (fp == NULL) {
        printf("File NUll\n");
    }
    FILE *erros = fopen("Resultados/passengers_errors.csv", "w"); //ficheiro de erros a escrever 
    if (erros == NULL) {
        perror("Error opening file\n");
        return; 
    }

    int i = 1;
    char row[500];
    fgets(row, 500, fp);
    while (fgets(row, 500, fp) != NULL)
    {
        char*linha = strdup(row);
        if (!parsePassengersCsvLine(linha, userInfo,voos)){
            fputs(row,erros);
            // printf("%dLINHA\n",i);
            i++;
            free(linha);
            continue;
        }
        free(linha);
        i++;
    }
    fclose(fp);
    fclose(erros);
}
