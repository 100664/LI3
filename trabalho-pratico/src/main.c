#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include "../Includes/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <glib.h>
#include <stdbool.h>
#include "../Includes/parse.h"
#include <sys/resource.h>

int main(int argc, char *argv[]){
    
    if (argv[2] != NULL){
            Catalog* c = parseDataSet(argv[1]);
            calcularQueries(c, argv[2], 0); 
    }
    else{
       menuNosso(argv[1]); 
    }
return 0;
}
