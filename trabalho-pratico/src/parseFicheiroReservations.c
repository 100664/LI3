#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/parseFicheiroReservations.h"
#include <ctype.h> 
#include <math.h>

#include <time.h>

reservations* parseReservationsCsvLine(char* linha, GHashTable* tableusers, GHashTable* tablehotel) {

    char* token;

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        return NULL;
    }

    char* reservationId = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(reservationId);
        return NULL;
    }
    char* userId = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(reservationId);
        free(userId);
        return NULL;
    }
    char* hotelId = strdup(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(reservationId);
        free(userId);
        free(hotelId);
        return NULL;
    }
    char* hotelName = strdup(token);

    token = strsep(&linha, ";");
    float stars = atof(token);
    if ( (fmod(stars, 1.0) != 0) || stars < 1 || stars > 5 || (!is_valid_integer(token))) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        return NULL;
    }    

    token = strsep(&linha, ";");
    float taxX = atof(token);
    if ( (fmod(taxX, 1.0) != 0) || taxX < 0 || (!is_valid_integer(token))) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        return NULL;
    }
    int tax = atoi(token);

    token = strsep(&linha, ";");
    if(strlen(token)==0) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        return NULL;
    }

    token = strsep(&linha, ";");
    if (!validar_data(token)) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        return NULL;
    }
    char* dataInicio = strdup(token);    

    token = strsep(&linha, ";");
    if (!validar_data(token)) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        return NULL;
    }
    char* dataFim = strdup(token);

    struct tm* dInicio= malloc(sizeof(struct tm));
    memset(dInicio, 0, sizeof(struct tm));
    strptime(dataInicio, "%Y/%m/%d", dInicio);

    struct tm* dFim =  malloc(sizeof(struct tm));
    memset(dFim, 0, sizeof(struct tm));
    strptime(dataFim, "%Y/%m/%d", dFim);

    if (difftime(timegm(dInicio),timegm(dFim)) >0){
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        free(dataFim);

        free(dInicio);
        free(dFim);
        return NULL;
    }
    free(dInicio);
    free(dFim);

    token = strsep(&linha, ";");
    float ppn = atof(token);
    if ( (fmod(ppn, 1.0) != 0) || ppn < 1 || (!is_valid_integer(token))) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        free(dataFim);
        return NULL;
    }
    int pricePerNight = atoi(token);
    
    token = strsep(&linha, ";");
    toLower(token);
    if (
        strcmp(token, "f") == 0 ||
        strcmp(token, "false") == 0 ||
        strcmp(token, "0") == 0 ||
        strcmp(token, "") == 0 ||
        token == NULL ||
        strlen(token)==0
        ) 
    token = "False";
    
    else if (strcmp(token, "t") == 0 ||
        strcmp(token, "true") == 0 ||
        strcmp(token, "1") == 0)
        token = "True";
    
    else {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        free(dataFim);
        return NULL;
    }
    char* includesBreakfast = strdup(token);

    token = strsep(&linha, ";");

    token = strsep(&linha, ";");
    float ratingPU = atof(token);
    if ( (fmod(ratingPU, 1.0) != 0) || ppn < 1 || ratingPU >5 || (!is_valid_integer(token))) {
        free(reservationId);
        free(userId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        free(dataFim);
        free(includesBreakfast);
        return NULL;
    }
    int ratinguser= atoi(token);
    token = strsep(&linha, ";");

    if (!g_hash_table_contains(tableusers, userId)){
        free(userId);
        free(reservationId);
        free(hotelId);
        free(hotelName);
        free(dataInicio);
        free(dataFim);
        free(includesBreakfast);
        return NULL;
    }
    reservations* reserva =  createReserva();
    setReservationId_Reservations(reservationId, reserva);
    setUserId_Reservations(userId, reserva);
    setHotelId_Reservations(hotelId, reserva);
    setHotelName_Reservations(hotelName, reserva);
    setHotelStars_Reservations(stars, reserva);
    setCityTax_Reservations(tax, reserva);
    setDataInicio_Reservations(dataInicio, reserva);
    setDataFim_Reservations(dataFim, reserva);
    setPricePerNight_Reservations(pricePerNight, reserva);
    setIncludesBreakfast_Reservations(includesBreakfast, reserva);
    setRatingPeloUser_Reservations(ratinguser, reserva);
    

    userInfo* userDaReserva = (userInfo*)g_hash_table_lookup(tableusers,userId);
    if (userDaReserva !=NULL){
        addToReservas_Users(userDaReserva, reserva);
    } else {
        return NULL;
    }
    char* hotelId2 = strdup(hotelId);
    hotelInfo* hotel = (hotelInfo*) g_hash_table_lookup(tablehotel, hotelId2);
    char* nomeHotel2 = strdup(hotelName);
    if (hotel == NULL){
        hotel = createHotel();
        setReservas_HotelInfo(NULL, hotel);
        setAvaliacaoTotal_HotelInfo(0, hotel);
        setNumeroAvaliacoes_HotelInfo(0, hotel);
        setPricePerNight_HotelInfo(getPricePerNight_Reservations(reserva), hotel);
        setCityTax_HotelInfo(getCityTax_Reservations(reserva), hotel);
        setHotelId_HotelInfo(hotelId2, hotel);
        setHotelName_HotelInfo(nomeHotel2, hotel);
        g_hash_table_insert(tablehotel, getHotelId_HotelInfo(hotel), hotel);
    }
    free(hotelId2);
    free(nomeHotel2);
    
    addToReservas_HotelInfo(hotel, reserva);
    incrementNumeroAvaliacoes_HotelInfo(hotel);
    adicionarRatingPeloUser_HotelInfo(hotel,ratinguser);


    free(reservationId);
    free(userId);
    free(hotelId);
    free(hotelName);
    free(dataInicio);
    free(dataFim);
    free(includesBreakfast);
    
    return reserva;
}

void separateWordsReservas(Catalog* catologo, char *ficheiro) //"main" do parse do ficheiro de reservas
{
    FILE *fp = fopen(ficheiro, "r"); //abre o ficheiro em modo de leitura (r)
    if (fp == NULL) {
        printf("File NUll\n");
    }

    FILE *erros = fopen("Resultados/reservations_errors.csv", "w"); //cria o ficheiro de erros em modo de escrita (w)
    if (erros == NULL) {
        perror("Error opening file\n");
        return; 
    }
    int i = 1;
    char row[500];

    GHashTable* userInfo = getUsersTable_Catalog(catologo);
    GHashTable* tablehotel = getHoteisTable_Catalog(catologo);
    GHashTable* hash_reservas = getReservasTable_Catalog(catologo);
    
    while (fgets(row, 500, fp) != NULL)
    {
        char* linha = strdup(row);
        reservations *reservas = parseReservationsCsvLine(linha, userInfo, tablehotel);
        free(linha);
        if (reservas==NULL) {
            fputs(row,erros);
            // printf("%dLINHA\n",i);
            i++;
            continue;
        }
        i++;
        char* idRES = getReservationId_Reservations(reservas);
        g_hash_table_insert(hash_reservas,  idRES, reservas);
    }
    fclose(fp);
    fclose(erros);
    // printf("Done separateWordsReservas, tamanho:%d\n", g_hash_table_size(hash_reservas));
}
