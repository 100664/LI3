        #include "../Includes/writeOutput.h"

/*
Esta é uma função em C chamada writeOutput que recebe várias estruturas de dados GHashTable contendo informações 
sobre usuários, reservas, hotéis, aeroportos e voos, uma string query contendo uma consulta e um inteiro questao 
indicando o número da questão. A função é responsável por chamar a função apropriada para processar a consulta e 
escrever o resultado em um arquivo de saída.A função começa alocando memória para uma cópia da string query usando 
a função malloc e strcpy. Em seguida, ela usa a função strsep para separar a string em tokens usando o espaço como 
delimitador. O primeiro token é descartado, pois contém o número da questão.A função então verifica o número da questão 
e chama a função apropriada para processar a consulta e escrever o resultado em um arquivo de saída. As funções chamadas 
incluem writeOutputQ1user, writeOutputQ1Voo, writeOutputQ1reserva, writeOutputQ3, writeOutputQ4, writeOutputQ5 e writeOutputQ8, 
que são responsáveis por processar as consultas das questões 1, 3, 4, 5 e 8, respectivamente. As funções writeOutputQ1user, 
writeOutputQ1Voo e writeOutputQ1reserva são usadas para processar consultas específicas da questão 1, enquanto as outras 
funções são usadas para processar consultas específicas de outras questões.Após chamar a função apropriada para processar 
a consulta, a função libera a memória alocada para a cópia da string query e retorna.Esta função é útil para processar 
consultas e escrever os resultados em arquivos de saída para cada questão
*/

void writeOutput (Catalog* c, char* query,int questao)
{
        GHashTable* userInfo = getUsersTable_Catalog(c);
        GHashTable* reservations = getReservasTable_Catalog(c);
        GHashTable* tablehotel =  getHoteisTable_Catalog(c);
        GHashTable* aeroportos = getAeroportosTable_Catalog(c);
        GHashTable* voos = getVoosTable_Catalog(c);
        char* a = malloc(strlen(query)+1);
        strcpy(a ,query);
        char* a_ptr = a;
        char* helper = strsep(&query, " ");
        helper = strsep(&query, " ");
        if (a[0]=='1'&& a[1] != 'F' && a[1] != '0'){
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q1_main(reservations, voos, userInfo, helper, 0),nomeficheiro);
                free(a_ptr);
                return;
        }

        if (a[0]=='1'&& a[1] == 'F'){
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q1_main(reservations, voos, userInfo, helper, 1),nomeficheiro);
                free(a_ptr);
                return;
        }

        if (a[0]=='2' && a[1]== 'F' ){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* bb = NULL;
                if (helper!= NULL) bb = strdup(helper);
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q2_main(userInfo, aa ,bb, voos,1), nomeficheiro);
                if (bb!= NULL) free(bb);
                free(aa);
                free(a_ptr);
                return;
        }

        if (a[0]=='2' && a[1] != 'F') {
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* bb = NULL;
                if (helper!= NULL) bb = strdup(helper);
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q2_main(userInfo, aa ,bb, voos,0), nomeficheiro);
                if (bb!= NULL) free(bb);
                free(aa);
                free(a_ptr);
                return;
        }

        if (a[0]=='3'&& a[1] == 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q3_main(tablehotel, helper, 1), nomeficheiro);
                free(a_ptr);
                return;
        }
        if (a[0]=='3'&& a[1] != 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q3_main(tablehotel, helper, 0), nomeficheiro);
                free(a_ptr);
                return;
        }
        if (a[0]=='4'&& a[1] != 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q4_main(tablehotel, helper,0),nomeficheiro);
                free(a_ptr);
                return;
        }
        if (a[0]=='4'&& a[1] == 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q4_main(tablehotel, helper,1),nomeficheiro);
                free(a_ptr);
                return;
        }
        if (a[0]=='5'&& a[1] != 'F'){
                char* aa = strdup(helper);
                helper = strsep(&query, "\"");
                helper = strsep(&query, " ");
                char* b = strdup(helper);
                helper = strsep(&query, "\"");
                char* c = strdup(helper);
                helper = strsep(&query, "\"");
                helper = strsep(&query, " ");
                char* d = strdup(helper);
                helper = strsep(&query, "\"" );
                char* e = strdup(helper);
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q5_main(aeroportos, aa,b , c,d,e, 0),nomeficheiro);
                free(aa);
                free(b);
                free(c);
                free(d);
                free(e);
                if(a!= NULL) free(a_ptr);                
                return;
        }
        if (a[0]=='5'&& a[1] == 'F'){
                char* aa = strdup(helper);
                helper = strsep(&query, "\"");
                helper = strsep(&query, " ");
                char* b = strdup(helper);
                helper = strsep(&query, "\"");
                char* c = strdup(helper);
                helper = strsep(&query, "\"");
                helper = strsep(&query, " ");
                char* d = strdup(helper);
                helper = strsep(&query, "\"" );
                char* e = strdup(helper);
        

                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q5_main(aeroportos, aa,b , c,d,e, 1),nomeficheiro);
                free(aa);
                free(b);
                free(c);
                free(d);
                free(e);
                if(a!= NULL) free(a_ptr);

                return;
        }

        if (a[0]=='6' && a[1]!= 'F' ){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* bb = NULL;
                if (helper!= NULL) bb = strdup(helper);
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q6_main(aeroportos, aa ,bb,0), nomeficheiro);
                if (bb!= NULL) free(bb);
                free(aa);
                free(a_ptr);
                return;
        }

        if (a[0]=='6' && a[1]== 'F' ){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* bb = NULL;
                if (helper!= NULL) bb = strdup(helper);
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q6_main(aeroportos, aa ,bb,1), nomeficheiro);
                if (bb!= NULL) free(bb);
                free(aa);
                free(a_ptr);
                return;
        }

        if (a[0]=='7' && a[1]!= 'F' ){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q7_main(aeroportos, aa,0), nomeficheiro);
                free(aa);
                free(a_ptr);
                return;
        }

        if (a[0]=='7' && a[1]== 'F' ){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q7_main(aeroportos, aa,1), nomeficheiro);
                free(aa);
                free(a_ptr);
                return;
        }
        

        if (a[0]=='8'&& a[1] != 'F'){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* b = strdup(helper);
                helper = strsep(&query, "\"");
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q8_main(tablehotel, aa,b , helper, 0),nomeficheiro);
                free(a_ptr);
                free(aa);
                free(b);
                return;
        }
        if (a[0]=='8'&& a[1] == 'F'){
                char* aa = strdup(helper);
                helper = strsep(&query, " ");
                char* b = strdup(helper);
                helper = strsep(&query, "\"");
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                escreveFicheiro(q8_main(tablehotel, aa,b , helper, 1),nomeficheiro);
                free(aa);
                if(a!= NULL) free(a_ptr);
                free(b);
                return;
        }
        if (a[0]=='9'&& a[1] != 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                if (helper[0] == '"') {
                        helper = strsep(&a, "\"");
                        helper = strsep(&a, "\"");
                        escreveFicheiro(q9_main(userInfo, helper, 0),nomeficheiro);
                        free(a_ptr);
                        return;
                }       
                escreveFicheiro(q9_main(userInfo, helper, 0),nomeficheiro);
                free(a_ptr);
                return;
        }

        if (a[0]=='9'&& a[1] == 'F') {
                char nomeficheiro[300];
                sprintf( nomeficheiro,"Resultados/command%d_output.txt", questao);
                if (helper[0] == '"') {
                        helper = strsep(&a, "\"");
                        helper = strsep(&a, "\"");
                        escreveFicheiro(q9_main(userInfo, helper, 1),nomeficheiro);
                        free(a_ptr);
                        return;                }
                else escreveFicheiro(q9_main(userInfo, helper, 1),nomeficheiro);
                free(a_ptr);
                return;
        } else free(a_ptr);

        char ficheirooutput[200];
        sprintf(ficheirooutput, "Resultados/command%d_output.txt", questao);
        FILE *resultadoQuery = fopen(ficheirooutput, "w");
        fclose(resultadoQuery);
        // free(a_ptr);
}
