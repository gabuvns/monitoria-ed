/*
Você é um aluno de computação muito ocupado, e por causa disso tem dificuldade de organizar suas tarefas,
com isso em mente, resolveu criar um programa que organize suas atividades.

A entrada consiste do nome da tarefa seguida de um numero de sua prioridade (sendo 1 o mais prioritário).
O programa encerra quando é digitado "end";

A saida consiste da fila ordenada primeiramente em prioridade, seguido por ordem de inserção.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    char* palavra;
    int prioridade;
    struct node* next;
    struct node* prev;
}s_node;

typedef struct fila{
    s_node* frente;
    s_node* fim;
    int tam;
}s_fila;

int ehnumero(char* nome){
    int flag = 0;
   
    // Verificamos se eh numero utilizando a tabela ascii
    if(nome[0] <= 57 && nome[0] >= 48){
        flag = 1;
    }

    return flag;
}

char* get_string(){
    char palavra[100];
    scanf("%s", palavra);
    
    char* palavra_aux = malloc(strlen(palavra)+1);
    strcpy(palavra_aux, palavra);

    return palavra_aux;
}

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

    free(aux->palavra);
    free(aux);
}

//Adiciona um elemento a fila
void fila_add(s_fila* fila, int uprioridade, char* palavra){
    if(fila->frente == NULL){
        fila->frente = cria_node();
        fila->fim = fila->frente; 
        fila->frente->prioridade = uprioridade;
        fila->frente->palavra = palavra; 

    }

    else{
        s_node* iterator = fila->frente;
        s_node* node_aux = cria_node();
        node_aux->prioridade = uprioridade;
        node_aux->palavra = palavra; 
    
        if(iterator->prioridade > uprioridade){
            fila->frente = node_aux;
            node_aux->prev = iterator;
    

        }

        else{
            if(iterator->prev != NULL){
                while(iterator->prioridade < uprioridade && iterator->prev != NULL){
                    iterator = iterator-> prev;
                }
                iterator->prev = node_aux;
                node_aux->next = iterator;
                fila->fim = node_aux;
            }

            else{
                iterator->prev = node_aux;
                node_aux->next = iterator;
                fila->fim = node_aux;
            }   
        }
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
        printf("Atividade: %s Prioridade: #%d\n",aux->palavra, aux->prioridade);
        aux = aux ->prev;
        i++;
    }
}

void processa_fila(s_fila* fila){
    char* uinput;
    int uprioridade = 0;
    
    do{
        uinput = get_string();

        if(strcmp(uinput,"end")){
            scanf("%d", &uprioridade);
            fila_add(fila, uprioridade, uinput);
        }
    
    }while(strcmp(uinput,"end"));
    free(uinput);



}

int main(){
    s_fila* fila = cria_fila();
    processa_fila(fila);
    
    print_fila(fila);
    printf("tamanho fila = %d\n", fila->tam);
    limpa_fila(fila);
}