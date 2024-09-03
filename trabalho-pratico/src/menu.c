#include "../Includes/menu.h"

#define tamanho_input 1024

int numero_ficheiro;

//função responsável por fazer "o titulo" de cada leitura

int aux_window_creation(WINDOW *window , int x,int y) { //x -> linhas, y -> coluna

    box(window,y,x);
    wattron(window,A_STANDOUT);
    mvwprintw(window,0,4,"Menu Iterativo");
    wattroff(window,A_STANDOUT);
    refresh();
    wrefresh(window); //dar refresh depois de usar a window, pois as mudanças ja vao estar feitas e assim podemos voltar a utilizar aquele pointer para a window
    return 1;
}

//numero de linhas do ficheiro

int number_lines (FILE  *resultadoQUery){
    int pos = 0;
    char aux [1000000];
    while (fgets(aux,1000000,resultadoQUery)){
        pos++;
    }

    if (pos%10 !=0 ) return (pos/10 +1);

   return (pos/10);

}

//função para achar a linha de um ficheiro

void acha_linha (FILE *file , int pos ) {
    char aux [1000000];
    int posicao = 0;
    fseek (file,0,SEEK_SET);
    pos=0 ;
    while(pos<posicao && fgets(aux,1000000,file)) {
    pos++;
    }
}

//função responsavel por fazer a paginação pois à querys com N respostas

void printnew(WINDOW *window, FILE *file, int pos, int pages) {
    fseek(file, 0, SEEK_SET);
    wclear(window);
    wrefresh(window);
    int line = 0, position = 0;
    char aux[20000], p;
    char char_opcao = 'o';

    while (char_opcao != 'q' && char_opcao != 'Q') {
        wclear(window);
        
        // Adicionado: Verifica se há mais linhas antes de imprimir
        int more_lines = 0;
        while ((p = fgetc(file)) != EOF && line < 10) {
            if (p == '\n') {
                line++;
            }
            aux[position] = p;
            position++;
            more_lines = 1;  // Indica que há mais linhas para imprimir
        }
        aux[position] = '\0';

        // Adicionado: Desativa a opção de avançar se não houver mais linhas
        if (!more_lines) {
            char_opcao = getch();
            continue;
        }

        wprintw(window, "%s\n", aux);
        wrefresh(window);
        wprintw(window, "------------------------Página %d-de-%d--------------------------------\n", pos + 1, pages);
        wprintw(window, "P-> Proximo\n");
        wrefresh(window);
        wprintw(window, "A-> Anterior\n");
        wrefresh(window);
        wprintw(window, "Q-> Voltar ao Menu \n");
        wrefresh(window);

        char_opcao = getch();
        wrefresh(window);

        switch (char_opcao) {
            case 'p':
            case 'P':
                if (pos == pages - 1) {
                    fseek(file, -position, SEEK_CUR);
                } else {
                    pos++;
                    fseek(file, -1, SEEK_CUR);
                    wclear(window);
                    wrefresh(window);
                }
                break;

            case 'a':
            case 'A':
                if (pos == 0) {
                    wclear(window);
                    fseek(file, 0, SEEK_SET);
                } else {
                    pos--;
                    acha_linha(file, pos * (10));
                    wclear(window);
                    wrefresh(window);
                }
                break;

            default:
                if (pos == 0) {
                    wclear(window);
                    fseek(file, 0, SEEK_SET);
                } else {
                    fseek(file, -position - 1, SEEK_CUR);
                }
        }
        position = 0;
        line = 0;
    }
}

void printFile(WINDOW *window, FILE *file ) {
    fseek(file, 0, SEEK_SET);  // Reposiciona o ponteiro do arquivo para o início
    
    wclear(window);
    wrefresh(window);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Lê o arquivo por completo
    while ((read = getline(&line, &len, file)) != -1) {
        wprintw(window, "%s", line);
    }

    free(line);  // Libera a memória alocada por getline
    
    // Exibe as informações na janela
    wprintw(window, "------------------------Fim do Arquivo--------------------------------\n");
    wprintw(window, "Q-> Voltar ao Menu\n");
    wrefresh(window);

    // Aguarda uma tecla ser pressionada antes de encerrar
    getch();
}

//caso1 -> query1

void query1 (WINDOW* window,int l,int c,GHashTable* reservas,GHashTable* voosTable, GHashTable* usersTable){
    char id[40]; char questaoChar[40];
    //criar a "interface" para a query1
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 1");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l+=2;
    mvwprintw(window,l,c,"ID DO UTILIZADOR, VOO OU RESERVA : ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,id);
    wrefresh(window);
    l+=2;
    aux_window_creation(window,0,0);
    wrefresh (window);
    //criar o ficheiro 
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    FILE *resultadoQuery = fopen(output, "w+");
    GList* token = q1_main(reservas, voosTable, usersTable, id, 1);
    
    escreveFicheiroToMenu(token, resultadoQuery);
    
    //printar a reposta 1
    printFile(window, resultadoQuery);
    fclose(resultadoQuery);
}

//caso2 -> query2

void query2 (WINDOW* window,int l,int c, GHashTable* userss,GHashTable* voosTable){
    char id[40]; char flag[40]; char questaoChar[40]; int help = 0;
//criar a interface para a query2
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 2");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"ID DO UTILIZADOR : ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,id);
    wrefresh(window);
    l++;
    mvwprintw(window,l,c,"FLAG ([reservations/flights/ ]): ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,flag);
    wrefresh(window);
    l=2;
    aux_window_creation(window,0,0);
    wrefresh (window);
//obter as varias respostas em forma  numa GLIST ao executar a Q2
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* resultado = q2_main(userss, id, flag, voosTable, 1);
    FILE *resultadoQuery = fopen(output, "w+");
    //colocar no ficheiro
    escreveFicheiroToMenu(resultado, resultadoQuery);

//dar o print no menu
        help = number_lines(resultadoQuery);
        printnew (window,resultadoQuery ,0,help);  
        fclose(resultadoQuery);

}

//caso3 -> query3

void query3 (WINDOW* window,int l,int c,GHashTable* hoteltable){
    char id[40]; char questaoChar[40]; 
//criar a interface para a query3
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 3");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"ID DO HOTEL: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,id);
    wrefresh(window);
    l+=2;
    aux_window_creation(window,0,0);
    wrefresh (window);
//obter as varias respostas em forma  numa GLIST ao executar a Q3
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* resultado = q3_main(hoteltable,id,1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
   escreveFicheiroToMenu (resultado, resultadoQuery);

 //printar a reposta 3
    printFile(window, resultadoQuery);
    fclose(resultadoQuery);
        
}

//caso4 -> query4

void query4 (WINDOW* window,int l,int c,GHashTable* hotelTable){
    char id[40]; char questaoChar[40]; int help = 0;
//criar a interface para a query4
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 4");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"ID DO HOTEL: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,id);
    wrefresh(window);
    l=2;
    aux_window_creation(window,0,0);
    wrefresh (window);
//obter as varias respostas em forma  numa GLIST ao executar a Q4
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* res = q4_main(hotelTable, id, 1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
    escreveFicheiroToMenu (res, resultadoQuery);
//dar o print no menu
    help = number_lines(resultadoQuery);
    printnew (window,resultadoQuery ,0,help);  
    fclose(resultadoQuery);
}  


//caso5 -> query5

void query5 (WINDOW* window,int l,int c,GHashTable* aeroportos){
    char data1[20], aeroporto[700], data2[20], hora1[20], hora2[20]; char questaoChar[40]; int help = 0;
//criar a interface para a query5
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 5");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;

    mvwprintw(window,l,c,"NOME DO AEROPORTO: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,aeroporto);
    wrefresh(window);
    l++;

    mvwprintw(window,l,c,"DATA DE PARTIDA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,data1);
    wrefresh(window);
    l++;

    mvwprintw(window,l,c,"HORA DE PARTIDA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,hora1);
    wrefresh(window);
    l++;

    mvwprintw(window,l,c,"DATA DE CHEGADA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,data2);
    wrefresh(window);
    l++;

    mvwprintw(window,l,c,"HORA DE CHEGADA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,hora2);
    wrefresh(window);
    l=2;
    aux_window_creation(window,0,0);
    wrefresh (window);

//obter as varias respostas em forma  numa GLIST ao executar a Q5
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* res = q5_main(aeroportos, aeroporto, data1, hora1, data2, hora2,1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
   escreveFicheiroToMenu (res, resultadoQuery);
//printar a reposta 5
    help = number_lines(resultadoQuery);
    printnew (window,resultadoQuery ,0,help);  
    fclose(resultadoQuery);
}

//caso6 -> query6

void query6 (WINDOW* window,int l,int c,GHashTable* aeroportos){
    char ano[20], top[5], questaoChar[40]; int help = 0;
//criar a interface para a query6
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 6");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;

    mvwprintw(window,l,c,"NUMERO DE AEROPORTOS A SEREM LISTADOS: ");
    wrefresh(window);
    l++;
    mvwgetstr(window,l,c,top);
    wrefresh(window);
    l++;

    mvwprintw(window,l,c,"ANO A TER EM CONTA PARA A LISTA: ");
    wrefresh(window);
    l++;
    mvwgetstr(window,l,c,ano);
    wrefresh(window);
    l=2;
    aux_window_creation(window,0,0);
    wrefresh (window);

//obter as varias respostas em forma  numa GLIST ao executar a Q6
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* res = q6_main(aeroportos, ano, top, 1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
    escreveFicheiroToMenu (res, resultadoQuery);
//printar a reposta 6
    help = number_lines(resultadoQuery);
    printnew (window,resultadoQuery ,0,help);  
    fclose(resultadoQuery);
}

//case7 -> query7

void query7 (WINDOW* window,int l,int c,GHashTable* aeroportos){
    char top[5], questaoChar[40]; 
    int help = 0;
//criar a interface para a query7
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 7");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"TAMANHO DA LISTA DE AEROPORTOS: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,top);
    wrefresh(window);
    l++;
    aux_window_creation(window,0,0);
    wrefresh (window);
//obter as varias respostas em forma  numa GLIST ao executar a Q7
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* resultado = q7_main(aeroportos, top, 1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
    escreveFicheiroToMenu (resultado, resultadoQuery);      
//dar o print no menu
        help = number_lines(resultadoQuery);
        printnew (window,resultadoQuery ,0,help);  
        fclose(resultadoQuery); 
}

//caso8 -> query8

void query8 (WINDOW* window,int l,int c,GHashTable* hoteltable){
    char id[20],  data1[20], data2[20]; char questaoChar[40];
//criar a interface para a query8
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 8");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"ID DO HOTEL: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,id);
    wrefresh(window);
    l++;
    mvwprintw(window,l,c,"DATA DE INICIO PARA REFERENCIA NA LISTA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,data1);
    wrefresh(window);
    l++;
    mvwprintw(window,l,c,"DATA DE INICIO PARA REFERENCIA NA LISTA: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,data2);
    wrefresh(window);
    l++;
    aux_window_creation(window,0,0);
    wrefresh (window);

//obter as varias respostas em forma  numa GLIST ao executar a Q8
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* resultado = q8_main(hoteltable, id, data1, data2, 1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
    escreveFicheiroToMenu (resultado, resultadoQuery);
    
//dar o print no menu
    printFile(window, resultadoQuery);
    fclose(resultadoQuery);
}

//caso9 -> query9

void query9 (WINDOW* window,int l,int c,GHashTable* usersTable){
    char prefixo[20]; char questaoChar[40];
    int help = 0;
//criar a interface para a query8
    wclear (window);
    wrefresh (window);
    wattron (window, A_STANDOUT);
    mvwprintw (window,l,c,"ESCOLHEU A QUERY 9");
    wattroff (window, A_STANDOUT);
    wrefresh (window);
    l++;
    mvwprintw(window,l,c,"PREFIXO: ");
    l++;
    wrefresh(window);
    mvwgetstr(window,l,c,prefixo);
    wrefresh(window);
    l++;
    aux_window_creation(window,0,0);
    wrefresh (window);
//obter as varias respostas em forma  numa GLIST ao executar a Q8
    sprintf(questaoChar, "%d", numero_ficheiro);
    char output[200] = "Resultados/command";
    strcat(output, questaoChar);
    strcat(output,"_output.txt");
    numero_ficheiro ++ ;
    GList* resultado = q9_main(usersTable, prefixo, 1);
    FILE *resultadoQuery = fopen(output, "w+");
//colocar no ficheiro
    escreveFicheiroToMenu (resultado, resultadoQuery);
    
//dar o print no menu
        help = number_lines(resultadoQuery);
        printnew (window,resultadoQuery ,0,help);  
        fclose(resultadoQuery);
}

//função principal do menu

int menuNosso (char* path){

    Catalog* catalogo =  parseDataSet(path);
    GHashTable* reservasT =getReservasTable_Catalog(catalogo);
    GHashTable* hoteisT = getHoteisTable_Catalog(catalogo);
    GHashTable* usersT = getUsersTable_Catalog(catalogo);
    GHashTable* voosT = getVoosTable_Catalog(catalogo);
    GHashTable* aeroportosT = getAeroportosTable_Catalog(catalogo);

    int linhas = LINES ,colunas = COLS ,x = 0,y = 0; numero_ficheiro = 1;
    char string_input[100];
    char path_users [tamanho_input], path_passagers [tamanho_input], path_reservations [tamanho_input], path_flights [tamanho_input];

    strcpy(path_users, path);
    strcat(path_users, "/users.csv");
    strcpy(path_passagers, path);
    strcat(path_passagers, "/passengers.csv");
    strcpy(path_reservations, path);
    strcat(path_reservations, "/reservations.csv");
    strcpy(path_flights, path);
    strcat(path_flights, "/flights.csv");

    do{

    initscr();
    raw();

    keypad(stdscr, TRUE);

    WINDOW *window = newwin (linhas,colunas ,x,y);

    wrefresh(window);

    int l = 2;
    int c = 1;

    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| ESCREVA A OPCAO QUE DESEJA SELECIONAR                               |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q1 -> RESUMO DE UM UTILIZADOR, VOO OU RESERVA                       |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q2 -> LISTAR OS VOOS OU RESERVAS DE UM UTILIZADOR                   |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q3 -> APRESENTAR A CLASSIFICACAO MEDIA DE UM HOTEL                  |\n");
    l++;   
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q4 -> LISTAR AS RESERVAS DE UM HOTEL                                |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q5 -> LISTAR OS VOOS COM ORIGEM NUM DADO AEROPORTO                  |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q6 -> LISTAR O TOP N AEROPORTOS COM MAIS PASSAGEIROS                |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q7 -> LISTAR O TOP N AEROPORTOS COM MAIOR MEDIANA DE ATRASOS        |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| Q8 -> APRESENTAR A RECEITA TOTAL DE UM HOTEL ENTRE DUAS DATAS       |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++; 
    mvwprintw(window,l,c,"| Q9 -> LISTAR TODOS OS UTILIZADORES COM UM DADO PREFIXO              |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| X -> SAIR                                                         |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    wrefresh(window);	
    l++; 
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    mvwprintw(window,l,c,"| QUAL A QUERY A SER EXECUTADA :                                      |\n");
    l++;
    mvwprintw(window,l,c,"-----------------------------------------------------------------------\n");
    l++;
    wrefresh(window);
    l++;
    box(window,0,0);
    wattron(window,A_STANDOUT);
    mvwprintw(window,0,4,"Menu Iterativo");
    wattroff(window,A_STANDOUT);
    refresh();
    wrefresh(window);
    mvwgetstr(window,l,c,string_input);
    toUppper(string_input);
    wrefresh(window);  

    if (strcmp (string_input ,"Q1")==0) {
        query1(window,l,c,reservasT,voosT,usersT);
            }
    if (strcmp (string_input ,"Q2")==0) {
        query2(window,l,c,usersT,voosT);
            }
    if (strcmp (string_input ,"Q3")==0) {
        query3(window,l,c,hoteisT);
            }
    if (strcmp (string_input ,"Q4")==0) {
        query4(window,l,c,hoteisT);
            }
    if (strcmp (string_input ,"Q5")==0) {
        query5 (window,l, c, aeroportosT) ;
            }
    if (strcmp (string_input ,"Q6")==0) {
        query6(window,l,c,aeroportosT);
            }
    if (strcmp (string_input ,"Q7")==0) {
        query7(window,l,c,aeroportosT);
            }
    if (strcmp (string_input ,"Q8")==0) {
        query8 (window,l,c,hoteisT);
            }
    if (strcmp (string_input ,"Q9")==0) {
        query9(window,l,c,usersT);
            }
    else{
        wattron(window,A_STANDOUT);
        mvwprintw(window,l,c, "CLICA NUMA TECLA PARA DARES SAIRES DO PROGRAMA!");
        wrefresh(window);
        wattroff(window,A_STANDOUT);
        l++;
        }  
    } 
     while ( strcmp (toUppper(string_input) ,"X") !=0) ;
        getch();
        endwin();
        return 0 ;
}
