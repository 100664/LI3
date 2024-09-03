#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include "../Includes/Q7.h"
#include <ctype.h> 

struct nomeEatrasos{
    char* nome;
    int medianaAtrasos;
};

int organizarListaQ7 (gconstpointer a,gconstpointer b){
    struct nomeEatrasos* primeiro = (struct nomeEatrasos*)a;
    struct nomeEatrasos* segundo  = (struct nomeEatrasos*)b; 
    if (segundo->medianaAtrasos != primeiro->medianaAtrasos) return segundo->medianaAtrasos - primeiro->medianaAtrasos;
    else return strcmp(primeiro->nome, segundo->nome);
}




void listaDeAtrasos(gpointer key, gpointer value, gpointer user_data) {
    gpointer* informacao = (gpointer*)user_data;
    GList** listaPtr = (GList**)&informacao[0];
    aeroportoInfo* aero = (aeroportoInfo*)value;
    GList* listaAtrasos = getAtrasoSegundos_Aeroporto(aero);
    if (g_list_length(getAtrasos_Aeroporto(aero)) == 0) return;
    GList* curr;
    int totalAtrasos = g_list_length(listaAtrasos);
    int mediana;
    if (totalAtrasos == 0 ){
        struct nomeEatrasos* nEA = malloc(sizeof(struct nomeEatrasos));
        nEA->nome = getNome_Aeroporto(aero);
        nEA->medianaAtrasos = 0;
        *listaPtr = g_list_prepend(*listaPtr, nEA);
    return;

    }

    if (totalAtrasos % 2 != 0) {
        int meio = totalAtrasos / 2;
        curr = g_list_nth(listaAtrasos, meio);
        int* atraso = (int*)curr->data;
        mediana = *atraso;
    } else {
        int meio = totalAtrasos / 2;
        curr = g_list_nth(listaAtrasos, meio-1);

        if (curr->next != NULL) {
            int* atraso = (int*)curr->data;
            int* atraso2 = (int*)curr->next->data;
            mediana = (*atraso + *atraso2) / 2;
        } else {
            printf("Erro Q7.\n");
            mediana = 0;  
        }
    }
    struct nomeEatrasos* nEA = malloc(sizeof(struct nomeEatrasos));
    nEA->nome = getNome_Aeroporto(aero);
    nEA->medianaAtrasos = mediana;
    *listaPtr = g_list_prepend(*listaPtr, nEA);

}


GList* q7_main(GHashTable* aeroportos, char* N, int formatado){

    GList* nomeEosPassageiros = NULL;
    gpointer dateRange[]= {nomeEosPassageiros};
    g_hash_table_foreach(aeroportos, (GHFunc)listaDeAtrasos, &dateRange);
    GList* resultado = NULL;
    dateRange[0] = g_list_sort(dateRange[0], (GCompareFunc)organizarListaQ7);
    GList* curr = dateRange[0];
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        if(i > atoi(N)) break;
        struct nomeEatrasos* nEA = (struct nomeEatrasos*) curr->data;
        char* nome = nEA->nome;
        int mediana = nEA->medianaAtrasos;
        char* buffer = (char*)malloc(100);
        if (formatado && i!=1) sprintf(buffer, "\n--- %d ---\nname: %s\nmedian: %d\n", i, nome, mediana);
        else if (formatado) sprintf(buffer, "--- %d ---\nname: %s\nmedian: %d\n", i, nome, mediana);
        else sprintf(buffer, "%s;%d\n", nome, mediana);
        resultado = g_list_append(resultado, buffer);
        free(nEA->nome);
        free(nEA);
        i++;
    }
    for(; curr != NULL; curr = g_list_next(curr)){
        struct nomeEatrasos* nEA  = (struct nomeEatrasos*) curr->data;
        free(nEA->nome);
        free(nEA);
    }
    g_list_free(dateRange[0]);

    return resultado;
}
