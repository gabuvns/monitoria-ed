/*
Na pequena cidade de Manhumirim muitas pessoas vão a academia, entretanto, como Manhumirim é muito pequena
ela possui apenas uma academia. Por causa disso ela fica muito cheia e consequentemente uma bagunça.
O estande de anilhas nunca ficava organizado e por isso da muito trabalho para pegar todos os pesos.

Com o intuito de demonstrar  para os marombeiros a importância de se ter uma academia organizada
um dos professores desta academia pediu para você criar um sistema que registre a quantidade de anilhas que devem ser retirados
antes de pegar uma anilha específico.

A entrada do programa consiste no peso das anilhas que estão inseridas em uma fileira do estande,
ao se digitar 0 o programa deve interromper as adições e o próximo numero a ser digitado vai ser 
o peso procurado.

A saida consiste na quantidade e nos pesos retirados até se encontrar o peso procurado. 
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct anilha{
    struct anilha* prox;
    struct anilha* ant;
    int peso;

}s_anilha;

typedef struct pilha{
    s_anilha* base;
    s_anilha* topo;
    int tamanho;
    int peso_total;
}s_pilha;

// Inicializamos a pilha vazia
s_pilha* pilha_cria(){
    s_pilha* pilha = malloc(sizeof(s_pilha));
    pilha->base = NULL;
    pilha->topo = NULL;
    pilha->tamanho = 0;
    pilha->peso_total = 0;
    return pilha;

}
// Criamos uma anilha vazia
s_anilha* anilha_cria(){
    s_anilha* anilha = malloc(sizeof(anilha));
    anilha->prox = NULL;
    anilha->ant = NULL;
    anilha->peso = 0;
    return anilha; 
}

// Funcao para retirar sempre o elemento do topo
void pilha_pop(s_pilha* pilha){
    if(pilha->topo != NULL){
        s_anilha* iterator = pilha->topo;
        if(iterator->ant != NULL){
            iterator->ant->prox = NULL;
            pilha->topo = iterator->ant;
        }

        else{
            pilha->base = NULL;
            pilha->topo = NULL;
        }
        
        pilha->tamanho--;
        pilha->peso_total = pilha->peso_total - iterator->peso;
        free(iterator);
    }

    else{
        printf("Pilha ja vazia\n");
    }
}
// Adicionamos o elemento a pilha
void add2pilha(s_pilha* pilha, int uinput){
    if(pilha->base == NULL){
        pilha->base = anilha_cria();
        pilha->topo = pilha->base; 
        pilha->base->peso = uinput;
    }

    else{
        s_anilha* iterator = pilha->topo;

        s_anilha* anilha_aux = anilha_cria();
        
        pilha->topo = anilha_aux;
        iterator->prox = anilha_aux;

        anilha_aux->ant = iterator;
        anilha_aux->peso = uinput;

    }

    pilha->tamanho++;
    pilha->peso_total = pilha->peso_total + uinput;
}

// Buscamos o elemento desejado
void pilha_busca(s_pilha* pilha, int uinput){
    s_anilha* iterator = pilha->topo;
    int rm_anilhas = 0;
    int rm_peso = 0;
    while(iterator->peso !=  uinput){
        printf("Peso retirado: %d\n", iterator->peso);

        rm_peso += iterator->peso; 
        rm_anilhas++;

        pilha_pop(pilha);
        iterator = iterator->ant;
    }
    printf("Anilhas retiradas: %d\nPeso retirado: %d\n", rm_anilhas, rm_peso);

}
// Funcao que adiciona os elementos a pilha
void pilha_enche(s_pilha* pilha){
    int  uinput = -1;
    int flag = 0;
    while(uinput != 0 && flag == 0){
        if(flag == 0){
            scanf("%d", &uinput);

            //Adiciona anilhas ao estande enquanto != 0
            if(uinput != 0){
                add2pilha(pilha, uinput);
            }

            //Realiza a busca final
            else{
                scanf("%d", &uinput);
                pilha_busca(pilha, uinput);
                flag = 1;
            }
        
        }
    }

}

void pilha_print(s_pilha* pilha){
    s_anilha* iterator = pilha->topo;
    while(iterator != NULL){
        printf("Peso: %d\n", iterator->peso);
        iterator = iterator->ant;
    }
    printf("Elementos totais: %d\nPeso total: %d\n", pilha->tamanho, pilha->peso_total);
}
void pilha_limpa(s_pilha* pilha){
    while(pilha->base != NULL){
        pilha_pop(pilha);
    }
    free(pilha);
}

int main(){
    s_pilha* pilha = pilha_cria();
    pilha_enche(pilha);
    pilha_limpa(pilha);
    

    return 0;
}