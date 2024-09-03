#include "../Includes/aeroporto.h"

//funções usadas no ficheiro parseFicheiroFlights.c para organizar/colocar as coisas nas gashTables de voos e aeroportos

struct aeroporto {
    char* nome;
    GList* atrasos;
    GList* partidas;
    GList* chegadas;
    GList* atrasoSegundos;
};

aeroportoInfo* createAeroporto(){
    aeroportoInfo* aeroporto = malloc(sizeof(aeroportoInfo));
    aeroporto->nome = NULL;
    aeroporto->atrasos = NULL;
    aeroporto->partidas = NULL;
    aeroporto->chegadas = NULL;
    aeroporto->atrasoSegundos = NULL;
    return aeroporto;
}

void setNome_Aeroporto(aeroportoInfo* aeroporto, char* nome) {
    aeroporto->nome = strdup(nome);
}

void setAtrasos_Aeroporto(aeroportoInfo* aeroporto, GList* atrasos) {
    aeroporto->atrasos = atrasos;
}

void setVoos_Aeroporto(aeroportoInfo* aeroporto, GList* voos) {
    aeroporto->partidas = voos;
}

void setChegadas_Aeroporto(aeroportoInfo* aeroporto, GList* voos) {
    aeroporto->chegadas = voos;
}

void setAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto, GList* atraso){
    aeroporto->atrasoSegundos = atraso;
}

char* getNome_Aeroporto(aeroportoInfo* aeroporto) {
    return strdup(aeroporto->nome);
}

GList* getAtrasos_Aeroporto(aeroportoInfo* aeroporto) {
    return aeroporto->atrasos;
}

GList* getVoos_Aeroporto(aeroportoInfo* aeroporto) {
    return aeroporto->partidas;
}

GList* getChegadas_Aeroporto(aeroportoInfo* aeroporto) {
    return aeroporto->chegadas;
}

GList* getAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto){
    return aeroporto->atrasoSegundos;
}

void addToAtrasos_Aeroporto(aeroportoInfo* aero, vooInfo* voo) {
    aero->atrasos = g_list_prepend(aero->atrasos, voo);
}

void addToVoos_Aeroporto(aeroportoInfo* aero, vooInfo* voo) {
   aero->partidas = g_list_prepend(aero->partidas, voo);
}

void addToChegadas_Aeroporto(aeroportoInfo* aero, vooInfo* voo) {
   aero->chegadas = g_list_prepend(aero->chegadas, voo);
}

void addToAtrasoSegundos_Aeroporto(aeroportoInfo* aeroporto, int* atraso) {
    aeroporto->atrasoSegundos = g_list_prepend(aeroporto->atrasoSegundos, atraso);
}

int organizarMaisRecenteVoo (gconstpointer a,gconstpointer b){
    vooInfo* primeiro = (vooInfo*)a;
    vooInfo* segundo  = (vooInfo*)b;
    return difftime(timegm(getScheduleDepartureDate_Flight(primeiro)), timegm(getScheduleDepartureDate_Flight(segundo)));
}


int organizarListaAtrasos (gconstpointer a,gconstpointer b){
    int* primeiro = (int*)a;
    int* segundo  = (int*)b; 
    return *segundo - *primeiro;
}

// int primeiroElementoNesteAno(GList* lista, int targetYear){
//     GList* curr = lista;
//     int index = 0;
//     while (curr != NULL) {
//         voos* voo = (voos*)curr->data;
//         struct tm* data = getScheduleDepartureDate_Flight(voo);
//         int year = data->tm_year + 1900; 
//         if (year == targetYear) {
//             return index;
//         }
//         curr = g_list_next(curr);
//         index++;
//     }
//     return -1; 
// } INUTIL PQ NÓS USAMOS LIST, SE FOSSE ARRAY ERA TOP, se tivermos tempo vamos implementar

void organizarListasAeroportos (gpointer key, gpointer value, gpointer user_data) {
    aeroportoInfo* aero = (aeroportoInfo*) value;
    aero->atrasos = g_list_sort(aero->atrasos,organizarMaisRecenteVoo);
    aero->chegadas= g_list_sort(aero->chegadas,organizarMaisRecenteVoo);
    aero->partidas    = g_list_sort(aero->partidas,organizarMaisRecenteVoo);
    aero->atrasoSegundos = g_list_sort(aero->atrasoSegundos,organizarListaAtrasos);
}


//dar free na memória da struct aeroportoInfo e das strings que estão lá dentro 

void free_aeroporto_hash_table(GHashTable* hash_table) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        aeroportoInfo* aeroporto = (aeroportoInfo*) value;
        g_free(aeroporto->nome);
        g_list_free(aeroporto->partidas);
        g_list_free(aeroporto->atrasos);
        g_list_free(aeroporto->chegadas);
        for (GList* curr = aeroporto->atrasoSegundos; curr != NULL; curr = g_list_next(curr)) {
            int* atraso = (int*)curr->data;
            free(atraso);
        }
        g_list_free(aeroporto->atrasoSegundos);
        g_free(key);
        g_free(aeroporto);
    }

    g_hash_table_destroy(hash_table);
}
