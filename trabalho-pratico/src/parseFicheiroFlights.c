#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/parseFicheiroFlights.h"
#include <ctype.h>

#include <time.h>

// Função que verifica se uma string é um inteiro válido ou não (retorna 1 se for válido, 0 caso contrário)
vooInfo* parseFlightsCsvLine(char *linha, GHashTable *aeroportos)
{


    char *token;
    token = strsep(&linha, ";");
    if (strlen(token) == 0)
    {
        return NULL;
    }
    char* vooId = strdup(token);
    token = strsep(&linha, ";");
    if (strlen(token) == 0)
    {
        free(vooId);
        return NULL;
    }
    char* airline = strdup(token);

    token = strsep(&linha, ";");
    if (strlen(token) == 0)
    {
        free(vooId);
        free(airline);
        return NULL;
    }
    char* planeModel = strdup(token);

    token = strsep(&linha, ";");
    if (!is_valid_integer(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        return NULL;
    }
    char* totalSeats = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_aeroporto(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        return NULL;
    }

    token = toUppper(token);
    char* origin = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_aeroporto(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        return NULL;
    }
    token = toUppper(token); //verificar se é aeroporto válido e se é diferente do anterior (origem)
    char* destination = strdup(token);

    char* destinationFLight = strdup(destination);
    char* originFLiiight = strdup(origin);
    if (strcmp(toLower(destinationFLight), toLower(originFLiiight)) == 0) //toLower = string para minusculas
    //verifica se o avião "sai" da origem para um novo destino (se sim cria o voo, se não, dá free a tudo)
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(destinationFLight);
        free(originFLiiight);
        return NULL;
    }
    free(destinationFLight);
    free(originFLiiight);

    token = strsep(&linha, ";");
    if (!validar_data_com_tempo(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        return NULL;
    }
    char* scheduleDepartureDate = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_data_com_tempo(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        return NULL;
    }
    char* scheduleArrivalDate = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_data_com_tempo(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        return NULL;
    }
    char* realDepartureDate = strdup(token);

    token = strsep(&linha, ";");
    if (!validar_data_com_tempo(token))
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        return NULL;
    }
    char* realArrivalDate = strdup(token);
    

    struct tm *partida_est = malloc(sizeof(struct tm));  //hora de partida estimada
    memset(partida_est, 0, sizeof(struct tm));
    strptime( scheduleDepartureDate, "%Y/%m/%d %H:%M:%S", partida_est);
    
    struct tm *chegada_est = malloc(sizeof(struct tm)); //hora de chegada estimada
    memset(chegada_est, 0, sizeof(struct tm));
    strptime( scheduleArrivalDate, "%Y/%m/%d %H:%M:%S", chegada_est);

    struct tm *partida_real = malloc(sizeof(struct tm)); //hora de partida real
    memset(partida_real, 0, sizeof(struct tm));
    strptime( realDepartureDate, "%Y/%m/%d %H:%M:%S", partida_real);

    struct tm *chegada_real = malloc(sizeof(struct tm)); //hora de chegada real
    memset(chegada_real, 0, sizeof(struct tm));
    strptime( realArrivalDate, "%Y/%m/%d %H:%M:%S", chegada_real);

    if (difftime(timegm(partida_est), timegm(chegada_est)) > 0) //verifica se a hora de partida estimada é maior que a hora de chegada estimada (se sim, dá free a tudo)
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        free(realArrivalDate);
        free(chegada_est);
        free(chegada_real);
        free(partida_est);
        free(partida_real);
        return NULL;
    }


    if (difftime(mktime(partida_real), mktime(chegada_real)) > 0)  //verifica se a hora de partida real é maior que a hora de chegada real (se sim, dá free a tudo)
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        free(realArrivalDate);
        free(chegada_est);
        free(chegada_real);
        free(partida_est);
        free(partida_real);
        return NULL;
    }

    free(chegada_est);
    free(chegada_real);
    free(partida_est);
    free(partida_real);

    token = strsep(&linha, ";");
    if (token == NULL || strlen(token) == 0)
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        free(realArrivalDate);
        return NULL;
    }
    char* pilotName = strdup(token);

    token = strsep(&linha, ";");
    if (strcmp(token, "\n") == 0 || strlen(token) == 0 || token[strlen(token) - 1] == '\n') 
    {
        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        free(realArrivalDate);
        free(pilotName);
        return NULL;
    }
    char* copilotName = strdup(token);


    char* origemFLight = strdup(origin);
    aeroportoInfo *aeroporto = (aeroportoInfo *)g_hash_table_lookup(aeroportos, origemFLight);
    char* destinoFlight = strdup(destination);
    aeroportoInfo *aeroportoDestino = (aeroportoInfo *)g_hash_table_lookup(aeroportos, destinoFlight);

    if (aeroporto == NULL)
    {
        //mudar isto para inicialização de um aeroporto
        aeroporto = createAeroporto();
        setVoos_Aeroporto(aeroporto, NULL);
        setAtrasos_Aeroporto(aeroporto, NULL);
        setNome_Aeroporto(aeroporto, origemFLight);
        setChegadas_Aeroporto(aeroporto,NULL);
        setAtrasoSegundos_Aeroporto(aeroporto, NULL);
        //
        g_hash_table_insert(aeroportos, strdup(origin), aeroporto);
    }

    if (aeroportoDestino == NULL)
    {
        //mudar isto para inicialização de um aeroporto
        aeroportoDestino = createAeroporto();
        setVoos_Aeroporto(aeroportoDestino, NULL);
        setAtrasos_Aeroporto(aeroportoDestino, NULL);
        setChegadas_Aeroporto(aeroportoDestino,NULL);
        setNome_Aeroporto(aeroportoDestino, destinoFlight);
        setAtrasoSegundos_Aeroporto(aeroportoDestino, NULL);
        //
        g_hash_table_insert(aeroportos, strdup(destination), aeroportoDestino);
    }

    free(origemFLight);
    free(destinoFlight);

    //
    // put all the strings you dupped into,
    vooInfo* flight = createFlight();
    setVooId_Flight(vooId, flight);
    setAirline_Flight(airline, flight);
    setPlaneModel_Flight(planeModel, flight);
    setTotalSeats_Flight(atoi(totalSeats), flight);
    setOrigin_Flight(origin, flight);
    setDestination_Flight(destination, flight);
    setScheduleDepartureDate_Flight(scheduleDepartureDate, flight);
    setScheduleArrivalDate_Flight(scheduleArrivalDate, flight);
    setRealDepartureDate_Flight(realDepartureDate, flight);
    setRealArrivalDate_Flight(realArrivalDate, flight);
    setPilotName_Flight(pilotName, flight);
    setCopilotName_Flight(copilotName, flight);

    addToChegadas_Aeroporto(aeroportoDestino,flight);
    addToVoos_Aeroporto(aeroporto, flight);

    struct tm *copyA = malloc(sizeof(struct tm));  
    memset(copyA, 0, sizeof(struct tm));
    strptime( realDepartureDate, "%Y/%m/%d %H:%M:%S", copyA);
    
    struct tm *copyB = malloc(sizeof(struct tm));  
    memset(copyB, 0, sizeof(struct tm));
    strptime( scheduleDepartureDate, "%Y/%m/%d %H:%M:%S", copyB);

    int diferenca = difftime(mktime(copyA), mktime(copyB));
    int* dif= (int*)malloc(sizeof(int));;
    *dif = diferenca;
    if (diferenca != 0)
    {
        addToAtrasos_Aeroporto(aeroporto, flight);
    }
    addToAtrasoSegundos_Aeroporto(aeroporto, dif);

    free(copyA);
    free(copyB);

        free(vooId);
        free(airline);
        free(planeModel);
        free(totalSeats);
        free(origin);
        free(destination);
        free(scheduleDepartureDate);
        free(scheduleArrivalDate);
        free(realDepartureDate);
        free(realArrivalDate);
        free(pilotName);
        free(copilotName);

    return flight;
}

void separateWordsVoos(Catalog* catalogo, char *ficheiro) //"main" do parse do ficheiro de voos
{

    GHashTable *hash_voos= getVoosTable_Catalog(catalogo);
    GHashTable *aeroportos = getAeroportosTable_Catalog(catalogo);

    FILE *fp = fopen(ficheiro, "r"); //abre o ficheiro em modo de leitura (r)
    if (fp == NULL)
    {
        printf("File NUll, voos\n");
    }

    FILE *erros = fopen("Resultados/flights_errors.csv", "w"); //cria o ficheiro de erros em modo de escrita (w)
    if (erros == NULL)
    {
        perror("Error opening file\n");
        return;
    }

    char row[500];
    while (fgets(row, 500, fp) != NULL) //enquanto houver linhas para ler no ficheiro de voos (fp)  
    {
        char*linha = strdup(row);
        vooInfo *voos = parseFlightsCsvLine(linha, aeroportos);
        free(linha);
        if (voos == NULL)
        {
            // printf("AQUI: %s\n", row);
            fputs(row, erros);
            continue;
        }
        char* vooid =getVooId_Flight(voos);
        g_hash_table_insert(hash_voos, vooid, voos);
    }
    fclose(fp);
    fclose(erros);
}
