#include "../Includes/Q6.h"
#include <ctype.h> 

struct nomeEpassageiros{
    char* nome;
    int passageiros;
};





void meterAeroportosNaLista (gpointer key, gpointer value, gpointer user_data) {
    gpointer* informacao = (gpointer*)user_data;
    GList** listaPtr = (GList**)&informacao[0];
    aeroportoInfo* aero = (aeroportoInfo*) value;
    int ano = atoi((char*)informacao[1]); 
    GList* listaVoos = getVoos_Aeroporto(aero);
    GList* curr = listaVoos;
    int totalPassageiros = 0;
    int i = 0;
    // printf("%d tamanho\n", g_list_length(listaVoos));
    for (; curr != NULL; curr = g_list_next(curr)) {
        i++;
        vooInfo *voo = (vooInfo*) curr->data;
        struct tm* date = getScheduleDepartureDate_Flight(voo);
        int anoVoo = date->tm_year + 1900;
        if(anoVoo == ano){
            totalPassageiros += getNumPassageiros(voo);
            continue;
        }
        if(ano < anoVoo) break;
        
    
    }
    listaVoos = getChegadas_Aeroporto(aero);
    curr = listaVoos;
    for (; curr != NULL; curr = g_list_next(curr)) {
        vooInfo *voo = (vooInfo*) curr->data;
        struct tm* date = getScheduleDepartureDate_Flight(voo);
        int anoVoo = date->tm_year + 1900;
        if(anoVoo == ano){
            totalPassageiros += getNumPassageiros(voo);
            continue;
        }
        if(ano < anoVoo) break;

    }

    struct nomeEpassageiros* nomeEospassageiros = malloc(sizeof(struct nomeEpassageiros));
    nomeEospassageiros->nome = getNome_Aeroporto(aero);
    nomeEospassageiros->passageiros = totalPassageiros;

    *listaPtr = g_list_prepend(*listaPtr, nomeEospassageiros);

}

int organizarPorQuemTemMais (gconstpointer a,gconstpointer b){
    struct nomeEpassageiros* primeiro = (struct nomeEpassageiros*)a;
    struct nomeEpassageiros* segundo = (struct nomeEpassageiros*)b; 

    int diferencaPassageiros = segundo->passageiros - primeiro->passageiros;

    if(diferencaPassageiros != 0) return diferencaPassageiros;
    char* ID1 = primeiro->nome;
    char* ID2 = segundo->nome;
    int res = strcmp(ID1 , ID2);
    return res;
}


GList* q6_main(GHashTable* aeroportos, char* ano, char* N, int formatado){
    GList* nomeEosPassageiros = NULL;
    gpointer dateRange[]= {nomeEosPassageiros, ano};
    g_hash_table_foreach(aeroportos, (GHFunc)meterAeroportosNaLista, &dateRange);
    GList* resultado = NULL;
    dateRange[0] = g_list_sort(dateRange[0], (GCompareFunc)organizarPorQuemTemMais);
    GList* curr = dateRange[0];
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        if(i > atoi(N)) break;
        struct nomeEpassageiros* nomeEospassageiross = (struct nomeEpassageiros*) curr->data;
        char* nome = nomeEospassageiross->nome;
        int passageiros = nomeEospassageiross->passageiros;
        char* buffer = (char*)malloc(100);
        if (formatado && i!=1) sprintf(buffer, "\n--- %d ---\nname: %s\npassengers: %d\n", i, nome, passageiros);
        else if (formatado) sprintf(buffer, "--- %d ---\nname: %s\npassengers: %d\n", i, nome, passageiros);
        else sprintf(buffer, "%s;%d\n", nome, passageiros);
        resultado = g_list_append(resultado, buffer);
        free(nomeEospassageiross->nome);
        free(nomeEospassageiross);
        i++;
    }
    for(; curr != NULL; curr = g_list_next(curr)){
        struct nomeEpassageiros* nomeEospassageiross = (struct nomeEpassageiros*) curr->data;
        free(nomeEospassageiross->nome);
        free(nomeEospassageiross);
    }
    g_list_free(dateRange[0]);
    g_list_free(nomeEosPassageiros);

    return resultado;
}

