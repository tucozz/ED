#include <stdio.h>
#include <stdlib.h>

typedef int data_type;

typedef struct{
    data_type *data;
    int size;
    int allocated;
    int first;
    int last;
    int next;
    int prev;
}Deque;

Deque *deque_construct(int max_size){
    Deque *d = malloc(sizeof(Deque));
    d->data = calloc(max_size, sizeof(data_type));
    d->size = 0;
    d->allocated = max_size;
    d->first = 0;
    d->last = 0;
    d->next = 0;
    d->prev = 0;
}

void deque_destroy(Deque *d){
    free(d->data);
    free(d);
}

void deque_pushback(Deque *d, data_type val){
    if(d->size == d->allocated){
        printf("ERROR: DEQUER CHEIO\n");
        return;
    }
    d->data[d->next] = val;
    if(d->next != d->last)
        d->last = (d->last + 1 + d->allocated)%d->allocated;
    d->next = (d->next + 1 + d->allocated)%d->allocated;
    d->size++;
}

void deque_pushfront(Deque *d, data_type val){
    if(d->size == d->allocated){
        printf("ERROR: DEQUER CHEIO\n");
        return;
    }
    d->data[d->prev] = val;
    if(d->prev != d->first)
        d->first = (d->first - 1 + d->allocated)%d->allocated;
    d->prev = (d->prev - 1 + d->allocated)%d->allocated;
    d->size++;
}

data_type deque_popback(Deque *d){
    if(d->size <= 0){
        printf("ERROR: DEQUER VAZIO\n");
        return -1;
    }
    data_type pop = d->data[d->last];
    d->last = (d->last - 1 + d->allocated)%d->allocated;
    d->size--;
    return pop;
}

data_type deque_popfront(Deque *d){
    if(d->size <= 0){
        printf("ERROR: DEQUER VAZIO\n");
        return -1;
    }
    data_type pop = d->data[d->first];
    d->first = (d->first + 1 + d->allocated)%d->allocated;
    d->size--;
    return pop;
}

int main(){
    //FUNÇÃO GERAL DE TESTE PARA O TIPO

    Deque *d = deque_construct(15);

    for(int i = 0; i < 15; i++){
        deque_pushback(d, i);
    }

    printf("VERDADEIRO:\n");
    for(int i = 0; i < 15; i++){
        printf("%d ", d->data[i]);
    }
    printf("\n");
    printf("PRIMEIRO: %d, ULTIMO: %d\n", d->first, d->last);

    for(int i = 0; i < 15; i++){
        printf("%d ", deque_popfront(d));
    }
    printf("\n");

    return 0;
}