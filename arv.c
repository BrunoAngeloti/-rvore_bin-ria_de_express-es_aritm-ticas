#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.h"

//Struct arv que contem tanto um numero como um operador
struct arv{
    float num;
    char ope;
    struct arv* esq;
    struct arv* dir;
};

//Funcao estatica para verificar se e operador
static int EhOperador(char c){
    if(c == '+' || c == '-' || c == '/' || c == '*'){
        return 1;
    }else{
        return 0;
    }
}

//Funcao estatica para verificar se e numero
static int EhDigito(char c){
    if(c >= '0' && c <='9'){
        return 1;
    }else{
        return 0;
    }
} 

//Cria um nó vazio
Arv* arv_cria(){
    return NULL;
}

//Cria um nó filho e o inicializa 
Arv* arv_insere (Arv* arv){   
    arv = (Arv*)malloc(sizeof(Arv));
    arv->num = -1; //usado -1 para inicializar como padrao
    arv->ope = '\0'; //usado \0 para inicializar como padrao     
    arv->esq = arv->dir = NULL; //define a arv esquerda e direita como nulas
      
    return arv;
}

//Libera a memoria da arvore
Arv* arv_libera(Arv* arv){
    if(arv){
        //libera memoria da arvore esquerda
        arv_libera(arv->esq);
        //libera memoria da arvore direita
        arv_libera(arv->dir);
        //libera memoria da arvore
        free(arv);
    }
    return NULL;
}

//Transforma uma string em uma arvore
Arv* parsing(Arv* arv, char* expressao, int* pos){
    char c = '\0';
    float aux = 0, valorNum = 0;
    
    // Caso seja '(' vai criar seu filho esquerdo e descer ate ele
    if(expressao[pos[0]] == '('){
        arv->esq = arv_insere(arv->esq);
        //Se o proximo char da expressao for um digito, nao desce para seu filho, apenas suba uma posição do vetor
        if(EhDigito(expressao[pos[0]+1])){
            pos[0]++; 
        }else{
            pos[0]++;
            arv->esq = parsing(arv->esq, expressao, pos);  
        }                 
    }
    // Caso seja um operador, atribui o operador ao nó atual, cria um filho a direita e vai até ele
    if(EhOperador(expressao[pos[0]])){
        arv->num = -1;
        arv->ope = expressao[pos[0]];
        pos[0]++;
        arv->dir = arv_insere(arv->dir);
        arv->dir = parsing(arv->dir, expressao, pos);
    }
    // Caso seja um numero, atribui o numero ao nó atual
    if(EhDigito(expressao[pos[0]])){
        //loop usado para transformar todos os digitos em inteiros até o proximo )
        for(pos[0];expressao[pos[0]] != ')';pos[0]++){
            valorNum = (expressao[pos[0]] - '0')+aux; 
            aux = valorNum * 10; 
        }
        arv->num = valorNum;
        arv->ope = '\0';            
    }
    // Caso seja ')' volte ao pai
    if(expressao[pos[0]] == ')'){
        pos[0]++;
        return arv;
    } 
}

//Calcula o valor da expressao representada pela arvore
float RetornaResultadoConta(Arv* arv){
    //Caso ambos sejam nulos, estamos em um nó com um numero, entao retorna o mesmo
    if(!arv->esq && !arv->dir){
        return arv->num;
    }else if(arv->num == -1){
        //Caso o numero seja -1, estamos em um operador, entao atribue o valor da arvore esquerda ao seu numero
        arv->num = RetornaResultadoConta(arv->esq);

        //De acordo com a operacao, faz a conta com o resultado da arvore direita
        if(arv->ope == '+'){
            arv->num = arv->num + RetornaResultadoConta(arv->dir);
        }
        if(arv->ope == '-'){
            arv->num = arv->num - RetornaResultadoConta(arv->dir);
        }
        if(arv->ope == '/'){
            arv->num = arv->num / RetornaResultadoConta(arv->dir);
        }
        if(arv->ope == '*'){
            arv->num = arv->num * RetornaResultadoConta(arv->dir);
        }        
    }
    return arv->num; //Retorna o resultado
}