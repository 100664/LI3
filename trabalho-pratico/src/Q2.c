#include "../Includes/Q2.h"
#include <ctype.h> 


struct vooOUreserva {
    reservations* reserva;
    vooInfo* voo;
    struct tm* date;
};

int organizarMaisAntigoVoos (gconstpointer a,gconstpointer b){
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

int organizarMaisAntigoReservas (gconstpointer a,gconstpointer b){
    reservations* primeiro = (reservations*)a;
    reservations* segundo = (reservations*)b; 

    struct tm* copyA = malloc(sizeof(struct tm));
    memcpy(copyA, getDataInicio_Reservations(primeiro), sizeof(struct tm));
    struct tm* copyB = malloc(sizeof(struct tm));
    memcpy(copyB, getDataInicio_Reservations(segundo), sizeof(struct tm));


    int diferencaTempo = difftime(timegm(copyB), timegm(copyA));
    free(copyA);
    free(copyB);
    if(diferencaTempo != 0) return diferencaTempo;
    char* resID1 = getReservationId_Reservations(primeiro);
    char* resID2 = getReservationId_Reservations(segundo);
    int res = strcmp(resID1 , resID2);
    return res;
}

GList* q2_reservas(userInfo* user, int formatado){
    GList* listaReservas = getListaReservas_Users(user);
    listaReservas = g_list_sort(listaReservas,organizarMaisAntigoReservas);
    GList* curr = listaReservas;
    GList* resultado = NULL;
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        reservations *res = (reservations*) curr->data;
        char* id= getReservationId_Reservations(res);
        struct tm* date = getDataInicio_Reservations(res);
        char *dateInString = dateInStringSimples(date);
        char entry[300];
        if (formatado && i!=1) sprintf(entry, "\n--- %d ---\nid: %s\ndate: %s\n", i, id, dateInString);
        else if (formatado) sprintf(entry, "--- %d ---\nid: %s\ndate: %s\n", i, id, dateInString);
        else sprintf(entry, "%s;%s\n", id, dateInString);
        resultado = g_list_append(resultado, strdup(entry));
        free(dateInString);
        free(id);
        i++;
    }
    setListaReservas_Users(listaReservas,user);
    return resultado;
}

GList* q2_voos (userInfo* user, GHashTable* voosTable, int formatado){
    GList* listaVoos = getListaVoos_Users(user);
    GList* copy = listaVoos;
    GList* curr = NULL;
    GList* head = curr;
    GList* resultado = NULL;
    for (; copy != NULL; copy = g_list_next(copy)) {
        char* vooID = (char*) copy->data;
        vooInfo* voo =  g_hash_table_lookup(voosTable, vooID);
        curr = g_list_prepend(curr, voo);
    }
    curr = g_list_sort(curr,organizarMaisAntigoVoos);
    GList* headtofree = curr;
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        vooInfo* voo = (vooInfo*)curr->data;
        char* id= getVooId_Flight(voo);
        struct tm* date = getScheduleDepartureDate_Flight(voo);
        char *dateInString = dateInStringSimples(date);
        char entry[300];
        if (formatado && i!=1) sprintf(entry, "\n--- %d ---\nid: %s\ndate: %s\n", i, id, dateInString);
        else if (formatado) sprintf(entry, "--- %d ---\nid: %s\ndate: %s\n", i, id, dateInString);
        else sprintf(entry, "%s;%s\n", id, dateInString);
        resultado = g_list_append(resultado, strdup(entry));
        free(dateInString);
        free(id);
        i++;
    }
    g_list_free(head);
    g_list_free(headtofree);
    
    return resultado;
}












int organizarMaisAntigoVoosEReservas (gconstpointer a,gconstpointer b){
    struct vooOUreserva* primeiro = (struct vooOUreserva*)a;
    struct vooOUreserva* segundo  = (struct vooOUreserva*)b; 

    struct tm* copyA = primeiro->date; 
    // primeiro->date->tm_hour=0; primeiro->date->tm_min=0; primeiro->date->tm_sec=0;
    struct tm* copyB = segundo->date; 
    // segundo->date->tm_hour=0; segundo->date->tm_min=0; segundo->date->tm_sec=0;

    int diferencaTempo = difftime(timegm(copyB), timegm(copyA));
    if(diferencaTempo != 0) return diferencaTempo;
    
    char* ID1 = NULL;
    if (primeiro->voo != NULL) ID1 = getVooId_Flight(primeiro->voo);
    else ID1 = getReservationId_Reservations(primeiro->reserva);
    
    char* ID2 = NULL;
    if (segundo->voo != NULL) ID2 = getVooId_Flight(segundo->voo);
    else ID2 = getReservationId_Reservations(segundo->reserva);
    int res = strcmp(ID1 , ID2);
    return res;
}



GList* q2_voosEreservas (userInfo* user, GHashTable* voosTable, int formatado){


    GList* listaVoos = getListaVoos_Users(user);
    GList* copy = listaVoos;
    GList* listaVOosOFC = NULL;
    GList* head = listaVOosOFC;
    for (; copy != NULL; copy = g_list_next(copy)) {
        char* vooID = (char*) copy->data;
        vooInfo* voo =  g_hash_table_lookup(voosTable, vooID);
        listaVOosOFC = g_list_prepend(listaVOosOFC, voo);
    }
    listaVOosOFC = g_list_sort(listaVOosOFC,organizarMaisAntigoVoos);
    GList* headtofree = listaVOosOFC;

    GList* listaReservas = getListaReservas_Users(user);
    GList* curr = NULL;
    listaReservas = g_list_sort(listaReservas,organizarMaisAntigoReservas);
    
    GList* copy2 = listaReservas;
    GList* resultado = NULL;
    for (; listaVOosOFC != NULL; listaVOosOFC = g_list_next(listaVOosOFC)) {
        struct vooOUreserva* voosEReservas = malloc(sizeof(struct vooOUreserva));
        vooInfo* voo =  (vooInfo*) listaVOosOFC->data;
        voosEReservas->voo = voo;
        voosEReservas->reserva= NULL;
        voosEReservas->date= malloc(sizeof(struct tm));
        memcpy(voosEReservas->date, getScheduleDepartureDate_Flight(voo), sizeof(struct tm));
        curr = g_list_prepend(curr, voosEReservas);
    }

    g_list_free(headtofree);
    for (; copy2 != NULL; copy2 = g_list_next(copy2)) {
        struct vooOUreserva* voosEReservas = malloc(sizeof(struct vooOUreserva));
        reservations *res = (reservations*) copy2->data;
        voosEReservas->voo = NULL;
        voosEReservas->reserva= res;
        voosEReservas->date= malloc(sizeof(struct tm));
        memcpy(voosEReservas->date, getDataInicio_Reservations(res), sizeof(struct tm));
        curr = g_list_prepend(curr, voosEReservas);
    }


    curr = g_list_sort(curr,organizarMaisAntigoVoosEReservas);
    headtofree = curr;
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        struct vooOUreserva* element = (struct vooOUreserva*)curr->data;
        if (element->voo!= NULL){
            vooInfo* voo = (vooInfo*)element->voo;
            char* id= getVooId_Flight(voo);
            struct tm* date = getScheduleDepartureDate_Flight(voo);
            char *dateInString = dateInStringSimples(date);
            char entry[300];
            if (formatado && i!=1) sprintf(entry, "\n--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, id, dateInString);
            else if (formatado) sprintf(entry, "--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, id, dateInString);
            else sprintf(entry, "%s;%s;flight\n", id, dateInString);
            resultado = g_list_append(resultado, strdup(entry));
            free(dateInString);
            free(id);
            i++;
        }
        else{
            reservations *res = (reservations*)element->reserva;
            char* id= getReservationId_Reservations(res);
            struct tm* date = getDataInicio_Reservations(res);
            char *dateInString = dateInStringSimples(date);
            char entry[300];
            if (formatado && i!=1) sprintf(entry, "\n--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, id, dateInString);
            else if (formatado) sprintf(entry, "--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, id, dateInString);
            else sprintf(entry, "%s;%s;reservation\n", id, dateInString);
            resultado = g_list_append(resultado, strdup(entry));
            free(dateInString);
            free(id);
            i++;
        }   
                free(element->date);
                free(element);

    }

    setListaReservas_Users(listaReservas,user);
    g_list_free(head);
    g_list_free(headtofree);
    
    return resultado;
}



GList* q2_main(GHashTable* userss, char* id, char* a, GHashTable* voosTable, int formatado){

    userInfo* user = (userInfo*)g_hash_table_lookup(userss, id);
    
    if (user == NULL) return NULL;
    
    char *accountStatus = toUppper(getAccountStatus_Users(user));
    if (strcmp(accountStatus, "ACTIVE") != 0){
        free(accountStatus);
        return NULL;
    }
    free(accountStatus);
    if ( a ==  NULL){
    } else
    if (strcmp(toUppper(a),"FLIGHTS") == 0){
        GList* xd= q2_voos(user,voosTable,formatado);
        return xd;
    } else if (strcmp(toUppper(a),"RESERVATIONS") == 0){
        GList* dx= q2_reservas(user,formatado);
        return dx;
    } 
    return q2_voosEreservas(user,voosTable,formatado);
}

