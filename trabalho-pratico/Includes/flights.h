#ifndef FLIGHTS_H
#define FLIGHTS_H


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct ficheiroVoos vooInfo;

vooInfo* createFlight();
void incrementarNumPassageiros(vooInfo* flight);
void setVooId_Flight(char* vooid, vooInfo* flight);
void setAirline_Flight(char* airline, vooInfo* flight);
void setPlaneModel_Flight(char* planeModel, vooInfo* flight);
void setTotalSeats_Flight(int totalSeats, vooInfo* flight);
void setOrigin_Flight(char* origin, vooInfo* flight);
void setDestination_Flight(char* destination, vooInfo* flight);
void setScheduleDepartureDate_Flight(char* a, vooInfo* flight);
void setScheduleArrivalDate_Flight(char* a, vooInfo* flight);
void setRealDepartureDate_Flight(char* a, vooInfo* flight);
void setRealArrivalDate_Flight(char* a, vooInfo* flight);
void setPilotName_Flight(char* pilotName, vooInfo* flight);
void setCopilotName_Flight(char* copilotName, vooInfo* flight);
void setNotes_Flight(char* notes, vooInfo* flight);

char* getVooId_Flight(vooInfo* flight);
char* getAirline_Flight(vooInfo* flight);
char* getPlaneModel_Flight(vooInfo* flight);
int getTotalSeats_Flight(vooInfo* flight);
char* getOrigin_Flight(vooInfo* flight);
char* getDestination_Flight(vooInfo* flight);
struct tm* getScheduleDepartureDate_Flight(vooInfo* flight);
struct tm* getScheduleArrivalDate_Flight(vooInfo* flight);
struct tm* getRealDepartureDate_Flight(vooInfo* flight);
struct tm* getRealArrivalDate_Flight(vooInfo* flight);
char* getPilotName_Flight(vooInfo* flight);
char* getCopilotName_Flight(vooInfo* flight);
char* getNotes_Flight(vooInfo* flight);
int getNumPassageiros(vooInfo* flight);

void freeStructVoos(vooInfo* vooInfo);
void free_voos_hash_table(GHashTable* hash_table);

#endif /* FLIGHTS_H */