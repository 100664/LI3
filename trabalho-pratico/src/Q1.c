#include "../Includes/Q1.h"
#include <ctype.h> 


void calcularTotalGasto(gpointer data, gpointer user_data){
    reservations* res = (reservations*)data;
    struct tm* copyA = malloc(sizeof(struct tm));
    memcpy(copyA, getDataInicio_Reservations(res), sizeof(struct tm));
    struct tm* copyB = malloc(sizeof(struct tm));
    memcpy(copyB, getDataFim_Reservations(res), sizeof(struct tm));

    int tax = getCityTax_Reservations(res);
    int numeroDeNoites = difftime(mktime(copyB), mktime(copyA))/ (60 * 60 * 24);
    int precoPorNoite = getPricePerNight_Reservations(res);
    double total_price = (double)precoPorNoite * (double)numeroDeNoites + (precoPorNoite * numeroDeNoites * 0.01) * tax;
    *((double*)user_data) += total_price;
    free(copyA);
    free(copyB);
}


GList* q1_user(GHashTable* usersTable,char* id, int formatado){

    userInfo* user = g_hash_table_lookup(usersTable, id);
    if (user == NULL){
        return NULL;
    }
    char* status = getAccountStatus_Users(user);
    if (strcmp(status, "inactive")== 0) {
        free(status);
        return NULL;
    }
    char* nome = getNome_Users(user);
    char* sexo = getSexo_Users(user);
    char* countryCode = getCountryCode_Users(user);
    char* passaporte = getNPassaporte_Users(user);
    struct tm* birthDateUser = malloc(sizeof(struct tm));
    memcpy(birthDateUser, getDNascimento_Users(user), sizeof(struct tm));
    int idade = calculateAge(birthDateUser);
    GList* voos = getListaVoos_Users(user);
    int numeroVoos = g_list_length(voos);
    GList* reservas = getListaReservas_Users(user);
    GList* copy = reservas;
    int numeroReservas = g_list_length(reservas);
    double totalGasto =0;
    g_list_foreach(copy, (GFunc)calcularTotalGasto, &totalGasto);
    setListaReservas_Users(copy, user);
    
    char* oqueimprimir = malloc(sizeof(char)*500);
    if (formatado) sprintf(oqueimprimir, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n", nome, sexo, idade, countryCode, passaporte,numeroVoos, numeroReservas,totalGasto);
    else sprintf(oqueimprimir, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", nome, sexo, idade,countryCode, passaporte, numeroVoos, numeroReservas, totalGasto);

    free(status);
    free(nome); 
    free(sexo); 
    free(countryCode); 
    free(passaporte);
    free(birthDateUser);

    GList* resultado = NULL;
    resultado = g_list_append(resultado, oqueimprimir);
    return resultado;
}


GList* q1_voo(GHashTable* voosTable,char* id, int formatado){

    vooInfo* voo  = g_hash_table_lookup(voosTable, id);

    if (voo == NULL){
        return NULL;
    }
    char* companhia = getAirline_Flight(voo);
    char* aviao = getPlaneModel_Flight(voo);
    char* origem = getOrigin_Flight(voo);
    char* destino= getDestination_Flight(voo);
    
    struct tm* partida_est = malloc(sizeof(struct tm));
    memcpy(partida_est, getScheduleDepartureDate_Flight(voo), sizeof(struct tm));
    struct tm* chegada_est = malloc(sizeof(struct tm));
    memcpy(chegada_est, getScheduleArrivalDate_Flight(voo), sizeof(struct tm));
    struct tm* partida_real =  malloc(sizeof(struct tm));
    memcpy(partida_real, getRealDepartureDate_Flight(voo), sizeof(struct tm));

    int numPass = getNumPassageiros(voo);


    int tempoAtrasado = difftime(mktime(partida_real), mktime(partida_est));
    memcpy(partida_est, getScheduleDepartureDate_Flight(voo), sizeof(struct tm));
    memcpy(partida_real, getRealDepartureDate_Flight(voo), sizeof(struct tm));

    char* oqueimprimir = malloc(sizeof(char)*500);
    if (formatado) sprintf(oqueimprimir, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %02d/%02d/%02d %02d:%02d:%02d\nschedule_arrival_date: %02d/%02d/%02d %02d:%02d:%02d\npassengers: %d\ndelay: %d\n", companhia, aviao, origem, destino, partida_est->tm_year+1900, 1+ partida_est->tm_mon, partida_est->tm_mday, partida_est->tm_hour, partida_est->tm_min, partida_est->tm_sec,    chegada_est->tm_year+1900, 1+ chegada_est->tm_mon, chegada_est->tm_mday, chegada_est->tm_hour, chegada_est->tm_min, chegada_est->tm_sec, numPass, tempoAtrasado);
    else sprintf(oqueimprimir, "%s;%s;%s;%s;%02d/%02d/%02d %02d:%02d:%02d;%02d/%02d/%02d %02d:%02d:%02d;%d;%d\n", companhia, aviao, origem, destino, partida_est->tm_year+1900, 1+ partida_est->tm_mon, partida_est->tm_mday, partida_est->tm_hour, partida_est->tm_min, partida_est->tm_sec,    chegada_est->tm_year+1900, 1+ chegada_est->tm_mon, chegada_est->tm_mday, chegada_est->tm_hour, chegada_est->tm_min, chegada_est->tm_sec, numPass, tempoAtrasado);
    

    free(companhia);
    free(aviao);
    free(origem);
    free(destino);
    free(partida_est);
    free(partida_real);
    free(chegada_est);

    GList* resultado = NULL;
    resultado = g_list_append(resultado, oqueimprimir); 
    return resultado;
}

GList* q1_reserva (GHashTable* reservas,char* id, int formatado){
    reservations* res  = g_hash_table_lookup(reservas, id);

    if (reservas == NULL){
        return NULL;
    }

    char* idHotel = getHotelId_Reservations(res);
    char* nome= getHotelName_Reservations(res);
    int estrelas=getHotelStars_Reservations(res);
    struct tm* dataI =  malloc(sizeof(struct tm));
    memcpy(dataI, getDataInicio_Reservations(res), sizeof(struct tm)); 
    
    struct tm* dataF = malloc(sizeof(struct tm));
    memcpy(dataF, getDataFim_Reservations(res), sizeof(struct tm)); 

    char* peqAlmoco =getIncludesBreakfast_Reservations(res);
    int numeroDeNoites = difftime(mktime(dataF), mktime(dataI))/(60*60*24);
    memcpy(dataI, getDataInicio_Reservations(res), sizeof(struct tm)); 
    memcpy(dataF, getDataFim_Reservations(res), sizeof(struct tm)); 
    int precoPorNoite = getPricePerNight_Reservations(res);
    int tax =getCityTax_Reservations(res);
    double precoTotal = (double)precoPorNoite * (double)numeroDeNoites + (precoPorNoite * numeroDeNoites * 0.01) * tax;

    char* oqueimprimir = malloc(sizeof(char)*500);
    if (formatado) sprintf(oqueimprimir, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %d\nbegin_date: %02d/%02d/%02d\nend_date: %02d/%02d/%02d\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",idHotel,nome,estrelas,dataI->tm_year+1900,1+dataI->tm_mon,dataI->tm_mday, 1900+dataF->tm_year,1+ dataF->tm_mon, dataF->tm_mday,peqAlmoco, numeroDeNoites, precoTotal);
    else sprintf(oqueimprimir, "%s;%s;%d;%02d/%02d/%02d;%02d/%02d/%02d;%s;%d;%.3f\n",idHotel,nome,estrelas,dataI->tm_year+1900,1+dataI->tm_mon,dataI->tm_mday, 1900+dataF->tm_year,1+ dataF->tm_mon, dataF->tm_mday,peqAlmoco, numeroDeNoites, precoTotal);
    free(idHotel);
    free(nome);
    free(dataF);
    free(dataI);
    free(peqAlmoco);
 
    GList* resultado = NULL;
    resultado = g_list_append(resultado, oqueimprimir);
    return resultado;
}


GList* q1_main(GHashTable* reservas,GHashTable* voosTable, GHashTable* usersTable ,char* id, int formatado){

    if (g_hash_table_contains(usersTable,id)){
        return q1_user(usersTable, id, formatado);
    } 
    if (g_hash_table_contains(voosTable,id)){
        return q1_voo(voosTable, id, formatado);
    } 
    if (g_hash_table_contains(reservas,id)){
        return q1_reserva(reservas, id, formatado);
    } 
    return NULL;
}