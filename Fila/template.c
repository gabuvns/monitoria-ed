#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    struct node* next;
    struct node* prev;
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
    aux->char = NULL;
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

    free(aux);
}

//Adiciona um elemento a fila
void fila_add(s_fila* fila){
    if(fila->frente == NULL){
        fila->frente = cria_node();
        fila->fim = fila->frente; 
    }

    else{
        s_node* iterator = fila->fim;
        s_node* node_aux = cria_node();

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
    s_node* aux = fila->frente;
    int i=0;
    while(aux != NULL){
        printf("%d\n", i);
        aux = aux ->prev;
        i++;
    }
}
int main(){
    s_fila* fila = cria_fila();
    fila_add(fila);
    fila_add(fila);
    fila_add(fila);
    
    print_fila(fila);
    limpa_fila(fila);
}