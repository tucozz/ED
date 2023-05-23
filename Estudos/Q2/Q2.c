#include <stdio.h>
#include <stdlib.h>

typedef int data_type;

typedef struct{
    data_type *data;
    int size;
    int allocated;
}Pilha;

//ambas as pilhas devem ser construidas no array de tamanho n, passado pelo usuario
Pilha *pilha_construct(int n){
    Pilha *p = malloc(sizeof(Pilha));
    p->data = calloc(n, sizeof(data_type));
    p->size = 0;
    p->allocated = n;

    return p;
}

//ambas as pilhas devem ser passadas, a primeira para receber o push e a segunda como verificação.
//Nota: tambem existe como colocar um ponteiro dentro da struct e uma função nova de LINKAR as duas pilhas. Mas exige mais um passo do usuario.
void pilha_push(Pilha *p1, Pilha *p2, data_type val){
    if(p1->size + p2->size >= p1->allocated){
        printf("ERROR: FULL STACK\n");
        return;
    }
    p1->data[p1->size] = val;
    p1->size++;
}

data_type pilha_pop(Pilha *p){
    if(p->size <= 0){
        printf("ERROR: DEQUER VAZIO\n");
        return -1;
    }
    data_type pop = p->data[p->size - 1];
    p->size--;
    return pop;
}

void pilha_destruct(Pilha *p){
    free(p->data);
    free(p);
}

int main(){
    int n = 5;

    Pilha *p1 = pilha_construct(n);
    Pilha *p2 = pilha_construct(n);

    pilha_push(p1, p2, 1);
    pilha_push(p1, p2, 2);
    pilha_push(p1, p2, 3);
    pilha_push(p1, p2, 4);
    pilha_push(p1, p2, 5);
    pilha_push(p1, p2, 6);

    printf("VERDADEIRO: ");
    for(int i=0; i < n; i++){
        printf("%d ", p1->data[i]);
    }
    printf("\n");

    for(int i=0; i < n; i++){
        printf("%d ", pilha_pop(p1));
    }
    printf("\n");
    

    return 0;
}