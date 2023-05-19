#include <stdlib.h>
#include <stdio.h>

typedef int data_type;

typedef struct{
    data_type *data;
    int next;
    int prev;
    int first;
    int last;
    int size;
    int used;
} Dequer;

Dequer *dequer_construct(int size){
    Dequer *d = malloc(sizeof(Dequer));
    d->data = calloc(size, sizeof(data_type));
    d->next = 0;
    d->first = 0;
    d->size = size;
    d->used = 0;
}

data_type dequer_pop_back(Dequer *d){
    if(d->used == 0){
        printf("INVALIDO, DEQUER VAZIO\n");
        return 0;
    }
    data_type pop = d->data[d->last];
    d->data[d->last] = 0;    
    d->last = d->last - 1;
    if(d->last < 0)
        d->last = d->size;
    d->next = d->next - 1;
    if(d->next < 0)
        d->next = d->size;
    d->used --;

    return pop;
}

data_type dequer_pop_front(Dequer *d){
    if(d->used == 0){
        printf("INVALIDO, DEQUER VAZIO\n");
        return 0;
    }
    data_type pop = d->data[d->first];
    d->data[d-> first] = 0;
    d->first = (d->first % d->size) + 1;
    d->prev = (d->prev % d->size) + 1;


    d->used --;

    return pop;
}

void dequer_push_front(Dequer *d, data_type val){
    if(d->used == d->size){
        printf("INVALIDO, DEQUER CHEIO\n");
    }
    d->data[d->prev] = val;
    d->first = d->first - 1;
    if(d->first < 0)
        d->first = d->size;
    d->prev = d->prev - 1;
    if(d->prev < 0)
        d->prev = d->size;
    d->used++;
}

void dequer_push_back(Dequer *d, data_type val){
    if(d->used == d->size){
        printf("INVALIDO, DEQUER CHEIO\n");
    }
    d->data[d->next] = val;
    d->next = (d->next % d->size) + 1;
    d->last = (d->last % d->size) + 1;
    d->used++;
}

int main(){
    Dequer *d = dequer_construct(15);

    for(int i=0; i < 15; i++){
        dequer_push_front(d, i);
    }

    printf("ORIGINAL: ");
    for(int i=0; i < 15; i++){
        printf("%d ", d->data[i]);
    }
    printf("\n");

    for(int i=0; i < 15; i++){
        printf("%d ", dequer_pop_front(d));
    }
    printf("\n");

    return 0;
}