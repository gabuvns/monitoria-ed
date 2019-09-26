/*
Um pequeno dono de uma loja de eletrônicos - um pouco pilantra por sinal-, queria realizar um sorteio 
em sua loja, como não queria contratar um desenvolvedor por achar ser muito caro,
resolver fazer um acordo com seu sobrinho que estuda na unb:

O sobrinho teria que criar um programa capaz de realizar o sorteio, em troca ele iria 
receber 100 reais. Como o sobrinho não era bobo nem nada e já sabia que seu tio era meio caloteiro,
resolveu se preparar, se certificou que caso ele não fosse pago ele iria PRIMEIRO remover metade das pessoas
da lista do sorteio (arredondando o número para baixo) para somente em seguida fazer o sorteio. 
Caso ele fosse pago o sorteio iria ocorrer normalmente. 

O tio no fim das contas não era tão maldoso, apenas um pouco apaixonado por números,
iria pagar seu sobrinho normalmente somente se a soma do número de letras em todos os nomes participantes
fosse divisivel por 3.

Por não ter conhecimento da função rand() e ser apaixonado por numeros assim como seu tio,
resolveu criar o seguinte algoritmo para realizar o sorteio:

O iterador deveria percorrer X nós da lista, onde X é definido como sendo 
a soma do número de letras de todos os nomes.

A entrada é composta pelo nomes dos participantes (que possuem no máximo 14 letras sem espaços), sendo que o primeiro nome é sempre o do sobrinho, e
deve ser interrompida ao digitar o número 0. 

A saida consiste no nome do ganhador.

obs: sabemos que pelo menos 4 pessoas participaram do sorteio (incluindo o sobrinho).


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct pessoa{
    char *nome;
    struct pessoa* prox;
    int tam_nome;
}s_pessoa;

typedef struct lista {
    s_pessoa* inicial;
    s_pessoa* final;
    int tamanho;
}s_lista;

s_lista* cria_lista(){
    s_lista* aux = malloc(sizeof(s_lista));
    aux->inicial = NULL;
    aux->tamanho = 0;
    return aux;
}

s_pessoa* cria_pessoa(char* nome){
    s_pessoa* aux = malloc(sizeof(s_pessoa));
    aux->nome = nome;
    aux->prox = NULL;
    int i = 0;
    
    while(*nome != '\0'){
        i++;
        nome++;
    }

    aux->tam_nome = i;
    return aux;
}

void print_lista(s_lista* lista){
    s_pessoa* iterator = lista->inicial;
    char * aux;
    for(int i = 0;i < lista->tamanho-1;i++){
        aux = iterator->nome;
        iterator = iterator->prox;
        printf("Nome: %s\n", aux);

    }
}

//Inserimos os nomes na lista
void preenche_lista(s_lista* lista){
    char aux[15];

    while(aux[0] != '0'){
        scanf("%s", aux);
        
        if(aux[0] != '0'){
            char* ptr = malloc(15);
            strcpy(ptr, aux);
            
            if(lista->inicial == NULL){
                lista->inicial = cria_pessoa(ptr);
                
            }

            else{
                s_pessoa* aux = lista->inicial;

                while(aux->prox != NULL){
                    aux = aux->prox;
                }
                aux->prox = cria_pessoa(ptr);
            }
            lista->tamanho++;
        }
        else{
            s_pessoa* iterator = lista->inicial;
            while(iterator->prox != NULL){
                iterator = iterator->prox;
            }
            lista->final = iterator;
            iterator->prox = lista->inicial;
        }      
    }
}
// Percorremos a lista para conseguir o total de letras
int get_total_letras(s_lista* lista){
    s_pessoa* aux = lista->inicial;
    int tamanho = 0;

    for(int i = 0; i < lista->tamanho; i++){  
        tamanho = tamanho + aux->tam_nome;
        aux = aux->prox;
    }

    return tamanho;
}

void reduz_lista(s_lista* lista){
    int new_tam = lista->tamanho/2;

    s_pessoa* iterator = lista->inicial;
    s_pessoa* prev;
    
    for(int i = 1; i < new_tam; i++){
        for(int i = 0; i < lista->tamanho;i++){      
            prev = iterator;
            iterator = iterator->prox;
        }

        prev->prox = NULL;          
        lista->tamanho--;
        iterator = iterator ->prox;
    }
    free(iterator->prox);
    iterator->prox = NULL;

}

void realiza_sorteio(s_lista* lista){

    s_pessoa* vencedor;
    int tot_letras = get_total_letras(lista);
    
    //Verificamos se o sobrinho vai ser pago ou nao
    if(tot_letras % 3 == 0){
        //sorteio normal
        int tot_letras = get_total_letras(lista);

        s_pessoa* iterator = lista->inicial;

        for(int i = 0; i < tot_letras-1;i++){
            iterator = iterator->prox;
        }
        vencedor = iterator;
    }

    else{
        // Sobrinho tem mais chances
        reduz_lista(lista);
        s_pessoa* iterator = lista->inicial;
        for(int i = 0; i < tot_letras/2;i++){
            if(iterator->prox != NULL){
                iterator = iterator->prox;
            }
        }
        vencedor = iterator;
    }
    char* aux_print = vencedor->nome; 

    printf("Vencedor: %s\n", aux_print);

}

int main(){

    s_lista* lista = cria_lista();
    preenche_lista(lista);
    realiza_sorteio(lista);

    
    return 0;
}