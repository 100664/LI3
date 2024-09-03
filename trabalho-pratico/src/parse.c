#include "../Includes/parse.h"
#include <locale.h>

Catalog* parseDataSet(char* caminhoDosFIcheiros){

    setlocale(LC_COLLATE, "en_US.UTF-8"); //para ordenar strings com acentos e cedilhas corretamente (ex: "ç" é ordenado depois de "c")

    clock_t start = clock();
    
    char  path[300]; strcpy(path,  caminhoDosFIcheiros);
    char path1[300]; strcpy(path1, caminhoDosFIcheiros);
    char path2[300]; strcpy(path2, caminhoDosFIcheiros);
    char path3[300]; strcpy(path3, caminhoDosFIcheiros);
    
    strcat(path,  "/users.csv"); 
    strcat(path1, "/reservations.csv");
    strcat(path2, "/flights.csv");
    strcat(path3, "/passengers.csv");

    // printf("DEBUGGING: CAMINHO FICHEIRO:%s\n", path);
    // printf("DEBUGGING: CAMINHO FICHEIRO:%s\n", path1);
    // printf("DEBUGGING: CAMINHO FICHEIRO:%s\n", path2);
    // printf("DEBUGGING: CAMINHO FICHEIRO:%s\n\n", path3);
    
    clock_t separateWordsStart, separateWordsEnd;
    double separateWordsTimeElapsed;

    Catalog* catalogo = createCatalog();
    GHashTable* aeroportosT = getAeroportosTable_Catalog(catalogo);


    separateWordsStart = clock();
    separateWordsUsers(catalogo, path);
    separateWordsEnd = clock();
    separateWordsTimeElapsed = ((double)(separateWordsEnd - separateWordsStart)) / CLOCKS_PER_SEC;
    printf("separateWordsUsers took %f seconds\n", separateWordsTimeElapsed);

    separateWordsStart = clock();
    separateWordsReservas(catalogo, path1);
    separateWordsEnd = clock();
    separateWordsTimeElapsed = ((double)(separateWordsEnd - separateWordsStart)) / CLOCKS_PER_SEC;
    printf("separateWordsReservas took %f seconds\n", separateWordsTimeElapsed);

    separateWordsStart = clock();
    separateWordsVoos(catalogo, path2);
    separateWordsEnd = clock();
    separateWordsTimeElapsed = ((double)(separateWordsEnd - separateWordsStart)) / CLOCKS_PER_SEC;
    printf("separateWordsVoos took %f seconds\n", separateWordsTimeElapsed);

    separateWordsStart = clock();
    separateWordsPassageiros(catalogo, path3);
    separateWordsEnd = clock();
    separateWordsTimeElapsed = ((double)(separateWordsEnd - separateWordsStart)) / CLOCKS_PER_SEC;
    printf("separateWordsPassageiros took %f seconds\n", separateWordsTimeElapsed);

    clock_t organizarStart, organizarEnd;
    organizarStart = clock();
    g_hash_table_foreach(aeroportosT,organizarListasAeroportos,NULL); //novo
    organizarEnd = clock();
    double organizarTimeElapsed = ((double)(organizarEnd - organizarStart)) / CLOCKS_PER_SEC;
    printf("organizarListasAeroportos took %f seconds\n", organizarTimeElapsed);

    clock_t end = clock();
    double time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parsing took: %f segundos\n\n", time_elapsed);

    return catalogo;
}
