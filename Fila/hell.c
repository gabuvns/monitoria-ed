/*
Muitas pessoas se perguntam como é o pós-vida, ou ao menos se ele pelo menos existe.  
Sendo o inferno um dos lugares mais temidos pela humanidade. Pelo menos neste programa o inferno existe sim,
e você vai ser responsável por programá-lo.
Ele se trata de uma fila eterna, e quando o usuario finalmente chega à frente da fila ele é chamado para atravessar a porta, 
e quando faz isso ele volta ao fim da fila.
A cada pessoa chamada todos avançam uma posição, e a pessoa chamada vai para o fim da fila.

A entrada consiste dos nomes das pessoas(somente nomes simples), e de um numero X. O programa
deve ler os nomes até que seja digitado X, onde X é o número de pessoas chamadas.

A saida consiste no nome das  duas pessoas que estarão na frente e no fim da fila. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    struct node* next;
    struct node* prev;
    char* nome;
}s_node;

typedef struct fila{
    s_node* frente;
    s_node* fim;
    int tam;
}s_fila;

s_fila* cria_fila(){
    s_fila* aux = malloc(sizeof(s_fila));
    aux->frente = NULL;
    aux->fim = NULL;
    aux->tam = 0;
    return aux;
}

s_node* cria_node(){
    s_node* aux = malloc(sizeof(s_node));
    aux->next = NULL;
    aux->prev = NULL;
    return aux;
}

// Retira o ultimo elemento da fila
void fila_pop(s_fila* fila){
    s_node* aux = fila->frente;
    fila->tam--;

    if(aux->prev != NULL){
        fila->frente = aux->prev;
        fila->frente->next = NULL;
        if(fila->tam){
            fila->fim = fila->frente;
        }
    }

    else{
        fila->frente = NULL;
        fila->fim = NULL;
    }
    free(aux->nome);
    free(aux);
}

//Adiciona um elemento a fila
void fila_add(s_fila* fila, char* nome){
    if(fila->frente == NULL){
        fila->frente = cria_node();
        fila->fim = fila->frente; 
        fila->frente->nome = nome;
    }

    else{
        s_node* iterator = fila->fim;
        s_node* node_aux = cria_node();
        node_aux->nome = nome;
        iterator->prev = node_aux;

        node_aux->next = iterator;

        fila->fim = node_aux;

    }
    fila->tam++;

}

void limpa_fila(s_fila* fila){
    while(fila->frente != NULL){
        fila_pop(fila);
    }

    free(fila);
}

void print_fila(s_fila* fila){  
    printf("Pessoa da frente: %s\n", fila->frente->nome);
    printf("Pessoa do fim: %s\n", fila->fim->nome);
    
}

char* get_string(){
    char nome[50];
    scanf("%s", nome);
    
    char* nome_aux = malloc(strlen(nome));
    strcpy(nome_aux, nome);

    return nome_aux;
}

int ehnumero(char* nome){
    int flag = 0;
   
    // Verificamos se eh numero utilizando a tabela ascii
    if(nome[0] <= 57 && nome[0] >= 48){
        flag = 1;
    }

    return flag;
}

void move_fila(s_fila* fila){
    s_node* nofrente = fila->frente;
    s_node* nofim = fila->fim;

    if(nofrente->prev != NULL){
        nofrente->next = nofim;

        fila->frente = nofrente->prev;
        fila->fim = nofrente;  

        nofrente->prev = NULL;
        
        nofim->prev = nofrente;
         
    }
}

void processa_fila(s_fila* fila){
    char* input;

    while(!ehnumero(input)){
        input = get_string();

        if(!ehnumero(input)){
            fila_add(fila, input);
        }
    }
    long int chamadas = atol(input);
    free(input);
    
    for(int i = 0; i < chamadas;i++){
        move_fila(fila);
    }

}

int main(){

    s_fila* fila = cria_fila();
    processa_fila(fila);
    
    print_fila(fila);
    limpa_fila(fila);
}