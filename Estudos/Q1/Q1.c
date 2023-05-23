#include <stdio.h>
#include <stdlib.h>

typedef int data_type;

typedef struct{
    data_type *data;
    int size;
    int allocated;
    int first;
    int last;
}Deque;

Deque *deque_construct(int max_size){
    Deque *d = malloc(sizeof(Deque));
    d->data = calloc(max_size, sizeof(data_type));
    d->size = 0;
    d->allocated = max_size;
    d->first = 0;
    d->last = 0;
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
    int next = (d->last + 1 + d->allocated)%d->allocated;
    d->data[next] = val;
    d->last = next;
    d->size++;
}

void deque_pushfront(Deque *d, data_type val){
    if(d->size == d->allocated){
        printf("ERROR: DEQUER CHEIO\n");
        return;
    }
    int prev = (d->first - 1 + d->allocated)%d->allocated;
    d->data[prev] = val;
    d->first = prev;
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