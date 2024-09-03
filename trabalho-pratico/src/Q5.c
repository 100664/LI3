#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include "../Includes/Q5.h"
#include <ctype.h> 

int organizarMaisAntigo (gconstpointer a,gconstpointer b){
    vooInfo* primeiro = (vooInfo*)a;
    vooInfo* segundo = (vooInfo*)b; 

    struct tm* copyA = malloc(sizeof(struct tm));
    memcpy(copyA, getScheduleDepartureDate_Flight(primeiro), sizeof(struct tm));
    struct tm* copyB = malloc(sizeof(struct tm));
    memcpy(copyB, getScheduleDepartureDate_Flight(segundo), sizeof(struct tm));


    int diferencaTempo = difftime(timegm(copyB), timegm(copyA));
    free(copyA);
    free(copyB);
    if(diferencaTempo != 0) return diferencaTempo;
    char* vooID1 = getVooId_Flight(primeiro);
    char* vooID2 = getVooId_Flight(segundo);
    int res = strcmp(vooID1 , vooID2);
    return res;
}

GList* q5_main(GHashTable* aeroportos, char* id, char* a, char* b, char* c, char* d, int formatado) {
    
    struct tm* dataA = malloc(sizeof(struct tm));
    memset(dataA, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d", dataA);
    strptime(b, "%H:%M:%S", dataA);

    struct tm* dataB = malloc(sizeof(struct tm));
    memset(dataB, 0, sizeof(struct tm));
    strptime(c, "%Y/%m/%d", dataB);
    strptime(d, "%H:%M:%S", dataB);

    aeroportoInfo* aeroporto = (aeroportoInfo*) g_hash_table_lookup(aeroportos, id);
    if (aeroporto == NULL || g_list_length(getVoos_Aeroporto(aeroporto)) == 0) {
        // printf("aeroporto n existe? %s \n",id);
        return NULL;
    }   

    GList* org = getVoos_Aeroporto(aeroporto);
    GList* iter = org;
    GList* modifiedList = NULL;

    while (iter != NULL) {
        vooInfo* v = (vooInfo*)iter->data;
        struct tm* copyA = malloc(sizeof(struct tm));
        memcpy(copyA, getScheduleDepartureDate_Flight(v), sizeof(struct tm));   

        if (timegm(copyA) >= timegm(dataA) && timegm(copyA) <= timegm(dataB)) {
            modifiedList = g_list_prepend(modifiedList, iter->data);
        }

        GList* next = iter->next;
        iter = next;

        free(copyA);
    }
    free(dataA);
    free(dataB);

    modifiedList = g_list_sort(modifiedList, organizarMaisAntigo);
    GList* curr = modifiedList;
    GList* listaResultado = NULL;
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        vooInfo *voo = (vooInfo*) curr->data;
        char* idVoo =getVooId_Flight(voo), *destination= getDestination_Flight(voo),*airline = getAirline_Flight(voo), *planemodel = getPlaneModel_Flight(voo);
        struct tm*  dataI = getScheduleDepartureDate_Flight(voo);

        char* buffer = (char*)malloc(600);
        if (formatado && i!=1) sprintf(buffer, "\n--- %d ---\nid: %s\nschedule_departure_date: %d/%02d/%02d %02d:%02d:%02d\ndestination: %s\nairline: %s\nplane_model: %s\n", i, idVoo, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataI->tm_hour, dataI->tm_min, dataI->tm_sec ,destination, airline, planemodel);
        else if (formatado) sprintf(buffer, "--- %d ---\nid: %s\nschedule_departure_date: %d/%02d/%02d %02d:%02d:%02d\ndestination: %s\nairline: %s\nplane_model: %s\n", i, idVoo, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataI->tm_hour, dataI->tm_min, dataI->tm_sec ,destination, airline, planemodel);
        else sprintf(buffer, "%s;%d/%02d/%02d %02d:%02d:%02d;%s;%s;%s\n", idVoo, dataI->tm_year+1900, dataI->tm_mon+1, dataI->tm_mday, dataI->tm_hour, dataI->tm_min, dataI->tm_sec ,destination, airline, planemodel);
        i++;
        free(idVoo);
        free(destination);
        free(airline);
        free(planemodel);
        listaResultado = g_list_append(listaResultado, buffer);
    }
    setVoos_Aeroporto(aeroporto, org);
    g_list_free(modifiedList);
    
    return listaResultado;
}
