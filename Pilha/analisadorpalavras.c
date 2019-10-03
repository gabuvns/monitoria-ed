
// Faça um programa que leia tanto frases do teclado quanto números separados por espaço, em seguida separe em duas pilhas as frases e os números,
// E imprima na tela primeiro a pilha de palavras e depois a pilha de numeros (ambos do topo para a base).  
// baseado em um execício da professora Leticia Winkler


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct palavra{
    char* palavra;
    struct palavra* prox;
    struct palavra* ant;

}s_palavra;

typedef struct pilha{
    s_palavra* topo;
    s_palavra* base;
    int tamanho;

}s_pilha;

s_palavra* cria_palavra(){
    s_palavra* palavra = malloc(sizeof(s_palavra));
    palavra->palavra = NULL;
    palavra->prox = NULL;
    palavra->ant = NULL;
    return palavra;
}


void pilha_pop(s_pilha* pilha){

    if(pilha->topo != NULL){
        s_palavra* iterator = pilha->topo;
        if(iterator->ant != NULL){
            iterator->ant->prox = NULL;
            pilha->topo = iterator->ant;
        }

        else{
            pilha->base = NULL;
            pilha->topo = NULL;
        }
        
        pilha->tamanho--;
        if(iterator->palavra != NULL){
            free(iterator->palavra);
        }
        free(iterator);
    }

    else{
        printf("Pilha ja vazia\n");
    }
}

void pilha_limpa(s_pilha* pilha){
    while(pilha->base != NULL){
        pilha_pop(pilha);
    }
    free(pilha);
}

s_pilha* cria_pilha(){
    s_pilha* pilha = malloc(sizeof(s_pilha));
    pilha->base = NULL;
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

char* get_string(){
    char palavra[100];
    scanf("%s", palavra);
    
    char* palavra_aux = malloc(strlen(palavra) + 1);
    strcpy(palavra_aux, palavra);

    return palavra_aux;
}


void add2pilha(s_pilha* pilha, char* uinput){
    if(pilha->base == NULL){
        pilha->base = cria_palavra();
        pilha->topo = pilha->base; 
        pilha->base->palavra = uinput;
    }

    else{
        s_palavra* iterator = pilha->topo;

        s_palavra* palavra_aux = cria_palavra();
        
        pilha->topo = palavra_aux;
        iterator->prox = palavra_aux;
        palavra_aux->palavra = uinput;
        palavra_aux->ant = iterator;
        

    }
    pilha->tamanho++;

}

void adiciona_palavras_pilha(s_pilha* pilha){
    char* uinput = NULL;

    int flag = 0;
    while(!flag){
        uinput = get_string();
        if(strcmp(uinput, "end")){
            add2pilha(pilha,uinput);
        }
        else{ 
            flag = 1;
        }
    }
        
    free(uinput);
    
}

int ehnumero(s_palavra* palavra){
    int flag = 0;
   
    // Verificamos se eh numero utilizando a tabela ascii
    if(palavra->palavra[0] <= 57 && palavra->palavra[0] >= 48){
        flag = 1;
    }

    return flag;
}

void analisa(s_pilha* frase, s_pilha* palavras,s_pilha* numeros){
    s_palavra* iterator = frase->topo;

    while(iterator != NULL){
        if(ehnumero(iterator)){
            add2pilha(numeros, iterator->palavra);
        }
        else{
            add2pilha(palavras, iterator->palavra);
        }

        iterator = iterator->ant; 

    }
}

void print_pilha(s_pilha* pilha){
    if(pilha->base != NULL){
        s_palavra* iterator = pilha->base;    

        while(iterator != NULL){
            printf("%s\n", iterator->palavra);
            iterator = iterator->prox;
        }
    }
}
  
int main(){
    s_pilha* frase = cria_pilha();
    adiciona_palavras_pilha(frase);
  
    s_pilha* palavras = cria_pilha();
    s_pilha* numeros = cria_pilha();

    analisa(frase, palavras, numeros);
   
    printf("Palavras:\n");
    print_pilha(palavras);

    printf("Numeros:\n");
    print_pilha(numeros);

    pilha_limpa(palavras);
    pilha_limpa(numeros);
    pilha_limpa(frase);

}