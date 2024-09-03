#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "parse.h"


int aux_window_creation(WINDOW *window , int x,int y);

void acha_linha (FILE *file , int pos );

int number_lines (FILE  *resultadoQUery);

void printnew(WINDOW *window,FILE *file ,int pos,int pages);

void printFile(WINDOW *window, FILE *file);

void query1 (WINDOW* window,int l,int c,GHashTable* reservas,GHashTable* voosTable, GHashTable* usersTable);

void query2 (WINDOW* window,int l,int c, GHashTable* userss,GHashTable* voosTable);

void query3 (WINDOW* window,int l,int c,GHashTable* hoteltable);

void query4 (WINDOW* window,int l,int c,GHashTable* hotelTable);

void query5 (WINDOW* window,int l,int c,GHashTable* aeroportos);

void query6 (WINDOW* window,int l,int c,GHashTable* aeroportos);

void query7 (WINDOW* window,int l,int c,GHashTable* aeroportos);

void query8 (WINDOW* window,int l,int c,GHashTable* hoteltable);

void query9 (WINDOW* window,int l,int c,GHashTable* usersTable);

int menuNosso(char* path);
