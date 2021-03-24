#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv.h"

int main(int argc, char* argv[]){
    char funcao[500];
    char* expressao;
    float res, aux1;
    int aux2;
    int* pos = (int*)malloc(sizeof(int)*1);

    Arv* arv = arv_cria();
    
    FILE* entrada = fopen("entrada.txt", "r");
    FILE* saida = fopen("saida.txt", "a");

    while(fscanf(entrada, "%s", funcao) == 1){
        expressao = strdup(funcao);

        pos[0] = 0; //Usado para nao perder a posicao quando fizer a recursividade
        arv = arv_insere(arv);
        
        arv = parsing(arv, expressao, pos); //Chama a funcao para transformar a string em arvore
        res = RetornaResultadoConta(arv); //Chama a funcao para calcular a expressao

        aux1 = res; //float   
        aux2 = res; //int

        if(aux1 - aux2 == 0.0){
            fprintf(saida, "%d\n", aux2); //Imprime o resultado da expressao em inteiro
        }else{
            fprintf(saida, "%.2f\n", res); //Imprime o resultado da expressao em float
        }
        
        //Libera a memoria da arvore e do vetor de expressao
        arv_libera(arv); 
        free(expressao); 
    }
    
    //Fecha os arquivos e da free no vetor alocado de posicao
    free(pos);
    fclose(entrada);
    fclose(saida);

    return 0;
}