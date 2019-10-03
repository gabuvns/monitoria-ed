/*
A mãe de Elliot cansou de anotar a lista de compras do mercado no papel e 
como ela sabe queo filho dela estuda computação na UnB
pediu para ele anotar no computador, entretanto, por ser muito habilidoso Elliot resolveu criar um programa
para facilitar a hora da compra, não apenas era capaz de receber alimentos como também retira-los caso necessario);
 

O input funciona da seguinte maneira: o usuario digita o nome do produto seguido pelo seu preco (com duas casas decimais)
- por exemplo "abacaxi 15.50" (float) -,
este item é adicionado, caso o usuario digite "rm abacaxi" o item abacaxi deve ser removido da lista.
O programa acaba quando o usuário digita "end".

output:
O output final deve mostrar toda a lista, no formato "item preco" ("abacaxi 15.25"),
e no fim a quantidade de itens e a soma de todos os preços dos itens da lista.
"Total de itens: X\nPreco total: Y\n";
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct item{
    char* nome;
    double preco;
    struct item* prox;
    struct item* prev;
}s_item;

typedef struct lista {
    s_item* inicial;
    s_item* final;
    int tamanho;
}s_lista;


s_lista* cria_lista(){
    s_lista* aux = malloc(sizeof(s_lista));
    aux->inicial = NULL;
    aux->final = NULL;
    aux->tamanho = 0;
    return aux;
}

s_item* cria_item(char* nome, double preco){
    s_item* aux = malloc(sizeof(s_item));
    
    aux->prox = NULL;
    aux->prev = NULL;
    aux->nome = nome;
    aux->preco = preco;

    return aux;
}

void remove_item(s_lista* lista){
   char aux_nome[20]; 
    
    scanf("%s", aux_nome);
    s_item* lixo = lista->inicial;


    while(strcmp(lixo->nome, aux_nome)){
        lixo = lixo->prox;
    }    

    if(lixo->prev != NULL){
        if(lixo->prox != NULL){
            lixo->prev->prox = lixo->prox;
            lixo->prox->prev = lixo->prev;
        }
    
        else{
            lixo->prev->prox = NULL;
        }
    }

    else{
        if(lixo->prox != NULL){
            lista->inicial = lixo->prox;
        }
        else{
            lista->final = NULL;
        }

        lixo->prev = NULL;
    }

    lista->tamanho--;

    free(lixo->nome);
    free(lixo);

}

void preenche_lista(s_lista* lista){
    char aux_nome[15];
    double preco = 0;

    while(strcmp(aux_nome, "end")){
        scanf("%s", aux_nome);
        //Podemos usar tambem strcmp() para comparacao!
        if(strcmp(aux_nome, "end")){
            //Verificamos se eh para remover
            if(aux_nome[0] == 'r' && aux_nome[1] == 'm'){             
                remove_item(lista);
            }

            else{
                //Se nao pega o input normalmente
                scanf("%lf", &preco);
                
                char* ptr_nome = malloc(15);
                strcpy(ptr_nome, aux_nome);

                if(lista->inicial == NULL){
                    lista->inicial = cria_item(ptr_nome, preco);
                    lista->tamanho++;
                }

                else{
                    s_item* iterator = lista->inicial;
                    
                    while(iterator ->prox != NULL){
                        iterator = iterator -> prox;
                    }
                    iterator->prox = cria_item(ptr_nome, preco);
                    lista->tamanho++;

                    iterator->prox->prev = iterator;
                    
                }
            }
        }    
    }
}
void limpa_lista(s_lista* lista){
    if(lista->tamanho > 0){
        s_item* iterator = lista->inicial;
        s_item* lixo = lista->inicial;

        while(iterator->prox !=NULL){
            lixo = iterator;
            free(lixo->nome);
            free(lixo);
            iterator = iterator->prox;
        }
        free(iterator->nome);
        free(iterator);
        free(lista);
    }
}

void print_lista(s_lista* lista){
    if(lista->inicial != NULL && lista->tamanho > 0){
        double preco_total = 0;
        s_item* iterator = lista->inicial;
        //Para evitar bugs
    
        while(iterator != NULL){
            preco_total = preco_total + iterator->preco;
            printf("%s %.2f\n", iterator->nome, iterator->preco);
            iterator = iterator->prox;
        }   
        printf("Total de itens: %d\nPreco total: %.2f\n", lista->tamanho, preco_total);
    }
    else{
        printf("Lista vazia\n");
    }

}

int main (){
    s_lista* lista = cria_lista();
    preenche_lista(lista);
    print_lista(lista);
    limpa_lista(lista);
    
}