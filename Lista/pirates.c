/*
Muitos séculos atrás antes de computadores existirem os piratas eram responsáveis por administrar toda a carga do navio manualmente.
Por se tratarem de cargas muito valiosas era necessário ter cuidado, por isso para evitar roubos um capitão dividiu esta tarefa entre seus dois mais fieis marujos,
sendo eles Cormac e Kenway. Como eram piratas obviamente não obedeceram e bolaram um esquema pra roubar a carga.

O navio comportava um número N de cargas, sabiam que podiam roubar 40% (arredondando para baixo) de toda a carga do navio sem que o capitão descobrisse.
Como visavam sempre o maior lucro possível procuravam sempre as cargas de maior valor. Para que se lembrassem qual carga pegar, anotavam o numero das cargas em uma lista Z.

A entrada consiste em um numero N que irá representar o total de cargas que o navio possui, em seguida cada linha será composta pelo ID X da carga e pelo valor Y da carga. Além disso,
sabe-se que não existem IDs repetidos (Tanto o ID quanto o valor da carga são valores inteiros). 

A saida consiste  na quantidade de carga disponivel para roubo ("roubo disponivel: %d") e nos IDs ("IDs: %d %d")que os piratas anotaram na lista, separados por espaço, além disso são ordenados pelo valor de cada carga de modo decrescente. Caso não seja possivel roubar nenhuma 
carga, o programa deve informar "Nenhum roubo disponivel".

Dica: Lembre-se de compilar com -lm se utilizar a <math.h>
*/



#include <stdio.h>
#include <stdlib.h>


typedef struct carga{
    int id;
    int valor;
    struct carga* ant;
    struct carga* prox;

}s_carga;

typedef struct lista{
    int tamanho;
    s_carga* final;
    s_carga* inicial;
}s_lista;

s_carga* add_carga(int id_, int valor_){
    s_carga* aux = malloc(sizeof(s_carga));
    aux -> id = id_;
    aux -> valor = valor_;
    aux -> prox = NULL; 
    aux -> ant = NULL;

    return aux;
}

s_lista* cria_lista(int tamanho_){
    s_lista* aux = malloc(sizeof(s_lista));
    aux ->tamanho = tamanho_;
    aux ->inicial = NULL;
    return aux;
}

void preenche_lista(s_lista* lista, int tamanho){
    int id = 0, valor = 0;  

    for(int i = 0; i < tamanho; i++){
        scanf("%d %d", &id, &valor);

        if(lista->inicial == NULL){
            lista->inicial = add_carga(id, valor);
            lista->final = lista->inicial;
        }
               
        else{
            s_carga* atual = lista->final;

            if(valor > atual->valor){
                atual->prox = add_carga(id, valor);
                atual->prox->ant = atual;
                lista->final = atual->prox;
            }

            else{
                s_carga* aux = add_carga(id,valor);

                while(atual->valor > valor && atual->ant != NULL){
                    atual = atual->ant;
                }   
                aux->ant = atual->ant;

                aux->prox = atual;
                atual->ant = aux;

            }
        }
    }

}

void print_lista(s_lista* lista){
    s_carga* iterator = lista->inicial;
    while(iterator!=NULL){
        printf("%d ", iterator->id);
        iterator = iterator->prox; 
    }
}


void print_carga_roubada(s_lista* carga_total, int roubo_disponivel){
    s_carga* aux = carga_total->final; 

    if(roubo_disponivel <=0){
    
        printf("Nenhum roubo disponivel\n");
    }

    else{
        printf("roubo disponivel = %d\n", roubo_disponivel);
        printf("IDs: ");

        for(int i=roubo_disponivel; i >= 1;i--){
            printf("%d ",aux->id);
        
            aux = aux->ant;

        }
        printf("\n");
    }
 
}

int main(){
    int n; 
    scanf("%d", &n);

    s_lista* carga_total = cria_lista(n);
    preenche_lista(carga_total, n);

    //Calculamos o total a ser roubado
    int roubo_disponivel = n*0.4;

    print_carga_roubada(carga_total, roubo_disponivel);
   
    return 0;
}