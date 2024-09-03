#include "../Includes/Q9.h"
#include <ctype.h> 



int ordenadarUsersNomeId (gconstpointer a,gconstpointer b){
    userInfo* primeiro = (userInfo*)a;
    userInfo* segundo  = (userInfo*)b;
    char* primeiroNome = getNome_Users(primeiro), *segundoNome = getNome_Users(segundo);
    int x = strcoll(primeiroNome, segundoNome);
    free(primeiroNome);
    free(segundoNome);
    if ( x != 0) return x;

    char* primeiroId = getId_Users(primeiro), *segundoId = getId_Users(segundo);
    int y = strcoll(primeiroId, segundoId);
    free(primeiroId);
    free(segundoId);
    return (y); 
}

void filtrarUsersPrefixo (gpointer key, gpointer value, gpointer user_data) {
    gpointer* informacao = (gpointer*)user_data;
    GList** usersFiltrados = (GList**) informacao[0];
    userInfo* user = (userInfo*) value;
    char* nome_User =getNome_Users(user);
    char* account_status = getAccountStatus_Users(user);
    if (strncmp(nome_User, informacao[1], strlen(informacao[1]))==0 && strcmp(account_status,"active")==0 ) {
       *usersFiltrados= g_list_prepend(*usersFiltrados, user);
    }
    free(nome_User);
    free(account_status);
}




GList* q9_main(GHashTable* usersTable, char* prefixo, int formatado){
    GList* usersFiltrados = NULL;
    gpointer informacao[] = {&usersFiltrados, prefixo};
    g_hash_table_foreach(usersTable, (GHFunc)filtrarUsersPrefixo, informacao);
    usersFiltrados = g_list_sort(usersFiltrados, ordenadarUsersNomeId);
    GList* curr = usersFiltrados;
    GList* listaResultado = NULL;
    int i = 1;
    for (; curr != NULL; curr = g_list_next(curr)) {
        userInfo *user = (userInfo*) curr->data;
        char* nome = getNome_Users(user), *id =getId_Users(user);
        char* buffer = (char*)malloc(100);
        if (formatado && i!=1) sprintf(buffer, "\n--- %d ---\nid: %s\nname: %s\n", i, id, nome);
        else if (formatado) sprintf(buffer, "--- %d ---\nid: %s\nname: %s\n", i, id, nome);
        else sprintf(buffer, "%s;%s\n", id, nome);
        i++;
        free(nome);
        free(id);
        listaResultado = g_list_append(listaResultado, buffer);
    }
    g_list_free(usersFiltrados);
    return listaResultado;
}
