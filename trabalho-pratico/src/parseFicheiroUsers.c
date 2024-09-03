#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/parseFicheiroUsers.h"
#include <ctype.h> 

#include <time.h>


userInfo* parseUsersCsvLine(char* linha) {


    char* token = strsep(&linha, ";");
    if(strlen(token)==0) {
        return NULL;
    }
    char* id = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(id);
        return NULL;
    }
    char* nome = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_email(token)) {
        free(id);
        free(nome);
        return NULL;
    }
    char* email = strdup(token);
    

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        return NULL;
    }
    char* telemovel = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_data(token)) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        return NULL;
    }
    char* dNascimento = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        return NULL;
    }
    char* sexo = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        return NULL;
    }
    char* nPassaporte = strdup(token);

    token = strsep(&linha, ";");
    if (strlen(token)!= 2) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        return NULL;
    }
    char* countryCode = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        return NULL;
    }

    token = strsep(&linha, ";");
    if(!validar_data_com_tempo(token)) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        return NULL;
    }
    char* dCriacaoConta = strdup(token);

    struct tm* dCriacao =  malloc(sizeof(struct tm));
    memset(dCriacao, 0, sizeof(struct tm));
    strptime(dCriacaoConta, "%Y/%m/%d", dCriacao);

    struct tm* dataNascimento = malloc(sizeof(struct tm));
    memset(dataNascimento, 0, sizeof(struct tm));
    strptime(dNascimento, "%Y/%m/%d", dataNascimento);

    if (difftime(mktime(dataNascimento),mktime(dCriacao)) >0){
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dataNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        free(dCriacaoConta);
        free(dCriacao);
        free(dNascimento);
        return NULL;
    }
    free(dCriacao);
    free(dataNascimento);

    token = strsep(&linha, ";");
    
    if(strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        free(dCriacaoConta);
        return NULL;
    }

    token = strsep(&linha, "\n");
    if(token == NULL || strlen(token)==0) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        free(dCriacaoConta);
        return NULL;
    }
    token = toLower (token);
    if  ((strcmp("active", token)!=0) && (strcmp("inactive",token)!=0) ) {
        free(id);
        free(nome);
        free(email);
        free(telemovel);
        free(dNascimento);
        free(sexo);
        free(nPassaporte);
        free(countryCode);
        free(dCriacaoConta);
        return NULL;
    }
    char* accountStatus = strdup(token);

    userInfo* user = createUser();
    setId_Users(id, user);    
    setNome_Users(nome, user);
    setEmail_Users(email, user);
    setTelemovel_Users(telemovel, user);
    setDNascimento_Users(dNascimento, user);
    setSexo_Users(sexo, user);
    setNPassaporte_Users(nPassaporte, user);
    setCountryCode_Users(countryCode, user);
    setDCriacaoConta_Users(dCriacaoConta, user);
    setAccountStatus_Users(accountStatus, user);

    free(id);
    free(nome);
    free(email);
    free(telemovel);
    free(dNascimento);
    free(sexo);
    free(nPassaporte);
    free(countryCode);
    free(dCriacaoConta);
    free(accountStatus);

    return user;
}




void separateWordsUsers(Catalog* catalogo, char *ficheiro) //"main" do parse do ficheiro de userInfo
{
    FILE *fp = fopen(ficheiro, "r");//abre o ficheiro em modo de leitura (r)
    if (fp == NULL) {
        printf("File NUll\n");
    }

    FILE *erros = fopen("Resultados/users_errors.csv", "w");//cria o ficheiro de erros em modo de escrita (w)
    if (erros == NULL) {
        perror("Error opening file\n");
        return; 
    }

    GHashTable* hash_users = getUsersTable_Catalog(catalogo);

    char row[500];
    while (fgets(row, 500, fp) != NULL)
    {
        char *linha = strdup(row);
        userInfo* user = parseUsersCsvLine(linha);
        free(linha);
        if (user == NULL) {
            fputs(row,erros);
            continue;
        }
        // printf("%d linha\n",i);
        char* userid = getId_Users(user);
        g_hash_table_insert(hash_users, userid, user);
    }
    fclose(erros);
    fclose(fp);
}
