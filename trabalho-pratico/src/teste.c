#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <glib.h>
#include <stdbool.h>
#include "../Includes/parse.h"
#include <sys/resource.h>

//funções que verificam se está tudo a aser bem feito (compara o ficheiro resposta, como o ficheiro de output do programa)

void compareFiles(const char* file1, const char* file2, int command) {
    FILE *f1, *f2;
    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");

    if (f1 == NULL) {
        printf("%s não existe\n", file1);
        return;
    }

    if ( f2 == NULL) {
        printf("%s não existe\n", file2);
        return;
    }

    char line1[1000], line2[1000];
    int lineNum = 1;
    int different = 0;

    while (fgets(line1, sizeof(line1), f1) != NULL && fgets(line2, sizeof(line2), f2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            different = 1;
            break;
        }
        lineNum++;
    }

    if (different || fgets(line1, sizeof(line1), f1) != NULL || fgets(line2, sizeof(line2), f2) != NULL) {
        printf("COMMAND%d:Files DIFFER!! at line %d\n",command, lineNum);
    } 

    fclose(f1);
    fclose(f2);
}

//conta o numero de linhas de um ficheiro (para saber quantos comandos foram executados) 

int countLines(const char* filename) { 
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}

int main(int argc, char *argv[]){ //main extra para ver se está tudo a ser bem feito
    
    if (argc < 4 ){
        printf("Argumentos inválidos\n");
        return 1;
    }

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
   

    
    clock_t start = clock();
        Catalog* c  =  parseDataSet(argv[1]);
        calcularQueries(c, argv[2], 1); 
    clock_t end = clock();
    double time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    int lines = countLines(argv[2]);
    int j = 1;
    for(j=1; j <= lines; j++){
        char a[200];
        sprintf(a, "Resultados/command%d_output.txt", j);;
        char b[200], helper[100];
        sprintf(helper, "/command%d_output.txt", j);
        strcpy(b, argv[3]);
        strcat(b, helper);
        compareFiles(a,b, j);
    }



    printf("--------\nPrograma demorou: %f segundos a executar\n", time_elapsed);
    printf("Memória máxima usada pelo programa: %ld KB\n --------\n", usage.ru_maxrss);
    
return 0;
}
