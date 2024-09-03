#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include "../Includes/flights.h"

//funcoes para criar a struct e organizar a GHashTable de struct ficheiroVoos no ficheiro parseFicheiroFlights.c 

struct ficheiroVoos {
    char* vooId;
    char* airline;
    char* planeModel;
    int totalSeats; 
    char* origin;
    char* destination;
    struct tm* scheduleDepartureDate;
    struct tm* scheduleArrivalDate;
    struct tm* realDepartureDate;
    struct tm* realArrivalDate;
    char* pilotName;
    char* copilotName;
    int numeroPassageiros;
};


struct ficheiroVoos* createFlight(){
    struct ficheiroVoos* flight = malloc(sizeof(struct ficheiroVoos));
    flight->vooId = NULL;
    flight->airline = NULL;
    flight->planeModel = NULL;
    flight->totalSeats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    flight->scheduleDepartureDate = NULL;
    flight->scheduleArrivalDate = NULL;
    flight->realDepartureDate = NULL;
    flight->realArrivalDate = NULL;
    flight->pilotName = NULL;
    flight->copilotName = NULL;
    flight->numeroPassageiros = 0;
    return flight;
}

void setVooId_Flight(char* vooid, struct ficheiroVoos* flight){
    flight->vooId = strdup(vooid);
}

void setAirline_Flight(char* airline, struct ficheiroVoos* flight){
    flight->airline = strdup(airline);
}

void setPlaneModel_Flight(char* planeModel, struct ficheiroVoos* flight){
    flight->planeModel = strdup(planeModel);
}

void setTotalSeats_Flight(int totalSeats, struct ficheiroVoos* flight){
    flight->totalSeats = totalSeats;
}

void setOrigin_Flight(char* origin, struct ficheiroVoos* flight){
    flight->origin = strdup(origin);
}

void setDestination_Flight(char* destination, struct ficheiroVoos* flight){
    flight->destination = strdup(destination);
}

void setScheduleDepartureDate_Flight(char* a, struct ficheiroVoos* flight){
    flight->scheduleDepartureDate = malloc(sizeof(struct tm));
    memset(flight->scheduleDepartureDate, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d %H:%M:%S", flight->scheduleDepartureDate);
}

void setScheduleArrivalDate_Flight(char* a, struct ficheiroVoos* flight){
    flight->scheduleArrivalDate = malloc(sizeof(struct tm));
    memset(flight->scheduleArrivalDate, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d %H:%M:%S", flight->scheduleArrivalDate);
}

void setRealDepartureDate_Flight(char* a, struct ficheiroVoos* flight){
    flight->realDepartureDate = malloc(sizeof(struct tm));
    memset(flight->realDepartureDate, 0, sizeof(struct tm));
    strptime(a, "%Y/%m/%d %H:%M:%S", flight->realDepartureDate);
}

void setRealArrivalDate_Flight(char* a, struct ficheiroVoos* flight){
    flight->realArrivalDate = malloc(sizeof(struct tm));
    memset(flight->realArrivalDate, 0, sizeof(struct tm));
    strptime( a, "%Y/%m/%d %H:%M:%S", flight->realArrivalDate);
}

void setPilotName_Flight(char* pilotName, struct ficheiroVoos* flight){
    flight->pilotName = strdup(pilotName);
}

void setCopilotName_Flight(char* copilotName, struct ficheiroVoos* flight){
    flight->copilotName = strdup(copilotName);
}


char* getVooId_Flight(struct ficheiroVoos* flight){
    return strdup(flight->vooId);
}

char* getAirline_Flight(struct ficheiroVoos* flight){
    return strdup(flight->airline);
}

char* getPlaneModel_Flight(struct ficheiroVoos* flight){
    return strdup(flight->planeModel);
}

int getTotalSeats_Flight(struct ficheiroVoos* flight){
    return flight->totalSeats;
}

char* getOrigin_Flight(struct ficheiroVoos* flight){
    return strdup(flight->origin);
}

char* getDestination_Flight(struct ficheiroVoos* flight){
    return strdup(flight->destination);
}

struct tm* getScheduleDepartureDate_Flight(struct ficheiroVoos* flight){
    return flight->scheduleDepartureDate;
}

struct tm* getScheduleArrivalDate_Flight(struct ficheiroVoos* flight){
    return flight->scheduleArrivalDate;
}

struct tm* getRealDepartureDate_Flight(struct ficheiroVoos* flight){
    return flight->realDepartureDate;
}

struct tm* getRealArrivalDate_Flight(struct ficheiroVoos* flight){
    return flight->realArrivalDate;
}

char* getPilotName_Flight(struct ficheiroVoos* flight){
    return flight->pilotName;
}

char* getCopilotName_Flight(struct ficheiroVoos* flight){
    return flight->copilotName;
}

void incrementarNumPassageiros(struct ficheiroVoos* flight){
    flight->numeroPassageiros+=1;
}

void freeStructVoos(struct ficheiroVoos* flight){
    free(flight->vooId);
    free(flight->airline);
    free(flight->planeModel);
    free(flight->origin);
    free(flight->destination);
    free(flight->scheduleArrivalDate);
    free(flight->scheduleDepartureDate);
    free(flight->realDepartureDate);
    free(flight->realArrivalDate);
    free(flight->pilotName);
    free(flight->copilotName);
    free(flight);
}

//liberar a memória da GHashTable de struct ficheiroVoos e das strings que estão lá dentro 
void free_voos_hash_table(GHashTable* hash_table) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        struct ficheiroVoos* flight = (struct ficheiroVoos*) value;
        g_free(key);
        freeStructVoos(flight);
    }
    g_hash_table_destroy(hash_table);
}

int getNumPassageiros(struct ficheiroVoos* flight){
    return flight->numeroPassageiros;
}