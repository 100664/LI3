#include "../Includes/calcularQueries.h"
#include <time.h>
#define MAX_QUERIES 9
/*
calcularQueries que recebe várias estruturas de dados GHashTable contendo informações sobre usuários, reservas, hotéis, 
aeroportos e voos, uma string input contendo o nome do arquivo de entrada e um inteiro teste indicando se estamos
no modo teste. A função é responsável por ler o arquivo de entrada, chamar a função 
writeOutput para processar cada comando e imprimir o tempo de execução de cada comando, se necessário.A função começa 
verificando se as estruturas de dados não estão vazias. Se alguma delas estiver vazia, a função imprime uma mensagem de 
erro e retorna.Em seguida, a função abre o arquivo de entrada e começa a ler cada linha. Para cada linha, a função usa a 
função strtok para separar a linha em tokens usando a quebra de linha como delimitador. Em seguida, a função chama a 
função writeOutput para processar cada token e escrever o resultado em um arquivo de saída.Após chamar a função writeOutput, 
a função calcula o tempo de execução do comando usando a função clock e imprime o tempo de execução, se necessário.
A função continua lendo o arquivo de entrada até o final e, em seguida, fecha o arquivo.
Essa função é útil para ler um arquivo de entrada contendo comandos e processá-los usando a função writeOutput. 
Ela também permite imprimir o tempo de execução de cada comando, o que pode ser útil para fins de depuração e otimização.
*/
struct QHelper{
    double total_time;
    int count;
};

void calcularQueries(Catalog* catalogo, char* input, int teste){

    GHashTable* userInfo= getUsersTable_Catalog(catalogo);
    GHashTable* reservations= getReservasTable_Catalog(catalogo);
    GHashTable* tablehotel= getHoteisTable_Catalog(catalogo);
    GHashTable* aeroportos= getAeroportosTable_Catalog(catalogo);
    GHashTable* voos = getVoosTable_Catalog(catalogo);

    if (g_hash_table_size(userInfo) == 0) {
        printf("The hash table userInfo is empty|Parse\n");
     return;
    }

    if (g_hash_table_size(reservations) == 0) {
        printf("The hash table reservations is empty|Parse\n");
        return;
    }

    if (g_hash_table_size(tablehotel) == 0) {
        printf("The hash table tablehotel is empty|Parse\n");
        return;
    }

    if (g_hash_table_size(aeroportos) == 0) {
        printf("The hash table aeroportos is empty|Parse\n");
        return;
    }

    if (g_hash_table_size(voos) == 0) {
        printf("The hash table voos is empty|Parse\n");
        return;
    }

    if (teste){
        
    }


    char row[300], *token;
    FILE *fp = fopen(input, "r");
    int questao = 1;
    clock_t start_time, end_time;
    QueryInfo query_infos[MAX_QUERIES] = {{0}};
    while (fgets(row, 150, fp) != NULL)
    {
        token = strtok(row, "\n");

        if (token != NULL)
        {
            start_time = clock();
            int query = token[0] - '0';
            int queryHElper = token[1] - '0';
            writeOutput(catalogo, token, questao);
            end_time = clock();

            if (teste){
                double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                if (queryHElper != 0 ) {
                    query_infos[query - 1].total_time += cpu_time_used;
                    query_infos[query - 1].count++;
                }
            }

            questao++;
        }
    }

    fclose(fp);
    
    if (teste)
    {
        double total_time_all_queries = 0;
        for (int i = 0; i < MAX_QUERIES; i++) {
            printf("Tempo médio para a Query %d: %f segundos - %d vezes executada \n\n",   i + 1, calculateAverageTime(i + 1, query_infos), query_infos[i].count);
            total_time_all_queries += query_infos[i].total_time; 
        }
        printf("Calcular as queries demorou: %f segundos\n\n", total_time_all_queries);
    }
    



    

    free_aeroporto_hash_table(aeroportos);
    free_hotel_hash_table(tablehotel);
    free_user_hash_table(userInfo);
    free_voos_hash_table(voos);
    free_reservations_hash_table(reservations);
    freeCatalog(catalogo);
}

double calculateAverageTime(int query_num, QueryInfo* query_infos)
{
    if (query_num >= 1 && query_num <= MAX_QUERIES) {
        double sum = query_infos[query_num - 1].total_time;
        int count = query_infos[query_num - 1].count;

        if (count > 0) {
            return sum / count;
        }
    }

    return 0;
}
