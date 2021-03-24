#ifndef Arvore_h
#define Arvore_h

#include <stdio.h>

typedef struct arv Arv;

/*Cria um nó vazio
 * inputs: -
 * output: ponteiro para o Arv alocado
 * pre-condicao: -
 * pos-condicao: arv de retorno existe
 */
Arv* arv_cria();

/*Cria um nó filho e o inicializa 
 * inputs: Arv arv
 * output: ponteiro para o Arv atualizado com o nó inicializado
 * pre-condicao: Arv existe
 * pos-condicao: Arv de retorno existe
 */
Arv* arv_insere (Arv* arv);


/*Libera a memoria da arvore
 * inputs: Arv arv
 * output: ponteiro para o Arv
 * pre-condicao: Arv existe
 * pos-condicao: Arv liberada 
 */
Arv* arv_libera(Arv* arv);

/*Transforma uma string em uma arvore
 * inputs: ponteiro para char da expressao a ser transformada, a arvore e a posicao do vetor expressao
 * output: ponteiro para o Arv definida
 * pre-condicao: expressao existe, arvore existe e posicao é valida
 * pos-condicao: Arv de retorno existe
 */
Arv* parsing(Arv* arv, char* expressao, int* pos);

/*Calcula o valor da expressao representada pela arvore
 * inputs: Arv arv
 * output: inteiro do resultado da expressao
 * pre-condicao: Arv existe
 * pos-condicao: -
 */
float RetornaResultadoConta(Arv* arv);


#endif