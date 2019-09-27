/*
Em Manhumirim todos possuiam quartos extremamente organizados, com exceção de um estudante de computação.
ELe tinha muia preguiça de arrumar suas roupas, por isso todo dia que chegava em casa empilhava suas roupas em cima da cadeira.
Um certo dia sua mãe entrou em seu quarto e ficou horrozida com a stiuação, e mandou ele arrumar tudo na hora.

Como ele era um estudante de computação e procrastinava muito, em vez de organizar suas roupas resolveu criar um programa capaz de
mostrar a ordem que as roupas iriam ficam dentro das gavetas, assim como o tempo necessario para organizar tudo.

A entrada consistia nas roupas em cima da cadeira (de baixo para o topo), no formato "tipo cor X", onde X é um inteiro em minutos
de quanto tempo se demora para dobrar a roupa. O programa se encerra ao digitar "end";

A saida consiste nas roupas ja dentro da gaveta (de baixo para o topo), e o tempo total;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct roupa{
    char* tipo;
    char* cor;
    struct roupa* prox;
    struct roupa* ant;
    int tempo;
}s_roupa;

typedef struct pilha{
    s_roupa* base;
    s_roupa* topo;
    int tamanho;
    int tempo_total;

}s_pilha;

void pilha_pop(s_pilha* pilha){
    if(pilha->topo != NULL){
        s_roupa* iterator = pilha->topo;
        if(iterator->ant != NULL){
            iterator->ant->prox = NULL;
            pilha->topo = iterator->ant;
        }

        else{
            pilha->base = NULL;
            pilha->topo = NULL;
        }
        
        pilha->tamanho--;
        pilha->tempo_total = pilha->tempo_total - iterator->tempo;
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

s_roupa* cria_roupa(){
    s_roupa* roupa = malloc(sizeof(s_roupa));
    roupa->tempo = 0;
    roupa->prox = NULL;
    roupa->ant = NULL;
    return roupa;
}

s_pilha* cria_pilha(){
    s_pilha* pilha = malloc(sizeof(s_pilha));
    pilha->base = NULL;
    pilha->topo = NULL;
    pilha->tamanho = 0;
    pilha-> tempo_total = 0;
    return pilha;
}

char* get_string(){
    char roupa[50];
    scanf("%s", roupa);
    
    char* roupa_aux = malloc(strlen(roupa) + 1);
    strcpy(roupa_aux, roupa);

    return roupa_aux;
}

void add2pilha(s_pilha* pilha, int tempo_, char* input_tipo, char* input_cor){
    if(pilha->base == NULL){
        pilha->base = cria_roupa();
        pilha->topo = pilha->base; 
        pilha->base->tempo = tempo_;
        pilha->base->tipo = input_tipo;
        pilha->base->cor = input_cor;
    
    }

    else{
        s_roupa* iterator = pilha->topo;

        s_roupa* roupa_aux = cria_roupa();
        
        pilha->topo = roupa_aux;
        iterator->prox = roupa_aux;

        roupa_aux->ant = iterator;
        roupa_aux->tempo = tempo_;
        roupa_aux->tipo = input_tipo;
        roupa_aux->cor = input_cor;

    }

    pilha->tamanho++;
    pilha->tempo_total += tempo_; 

}

void adiciona_roupa_pilha(s_pilha* pilha){
    char* input_tipo;
    char* input_cor;
    int tempo = 0;
    int flag = 0;
    while(!flag){
        input_tipo = get_string();
        if(strcmp(input_tipo, "end")){
            input_cor = get_string();
            scanf("%d", &tempo);
            add2pilha(pilha, tempo, input_tipo, input_cor);
        }
        else{
            flag = 1;
        }
    }
}

void transfere(s_pilha* cadeira,s_pilha * gaveta){
  if(cadeira->topo != NULL){
        s_roupa* iterator = cadeira->topo;
        while(iterator != NULL){
            
            add2pilha(gaveta, iterator->tempo, iterator->tipo, iterator->cor);

            iterator = iterator ->ant;
            pilha_pop(cadeira);
        }
    }  
}
void print_pilha(s_pilha* pilha){
    s_roupa* aux = pilha->base;
    while(aux != NULL){
        printf("Tipo: %s Cor: %s\n", aux->tipo, aux->cor);
        aux = aux ->prox;
    }
    printf("Total de roupas = %d\nTotal de tempo = %d\n", pilha->tamanho, pilha->tempo_total);
}
int main(){
    s_pilha* cadeira = cria_pilha();
    adiciona_roupa_pilha(cadeira);

    s_pilha* gaveta = cria_pilha();
    transfere(cadeira, gaveta);

    print_pilha(gaveta);

    pilha_limpa(cadeira);
    pilha_limpa(gaveta);
}