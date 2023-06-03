#include <stdio.h>
#include <stdlib.h>

//Foi feita no leetcode sem isso, mas pra adaptar pra cá precisa.
typedef int bool;
#define true 1;
#define false 0;

typedef struct{
    char *lista;
    int size;
    int alloc;
}pilha;

pilha *pilha_construct(int size){
    pilha *p = malloc(sizeof(pilha));
    p->lista = calloc(size, sizeof(char));
    p->alloc = size;
    p->size = 0;

    return p;
}

void pilha_push(pilha *p, char data){
    if(p->size == p->alloc){
        p->lista = realloc(p->lista, 2*p->alloc);
        p->alloc = 2*p->alloc;
    }
    p->lista[p->size] = data;
    p->size++;
}

char pilha_pop(pilha *p){
    if(p->size == 0)
        return '\0';
    char pop = p->lista[p->size-1];
    p->size--;
    return pop;
}

bool pilha_empty(pilha *p){
    return p->size == 0;
}

bool isValid(char * s){
    char c = 'c', pop;
    int i = 0;
    pilha *p = pilha_construct(5);
    while(c != '\0'){
        c = s[i];
        switch (c){
            case '(':
                pilha_push(p, c);
                break;
            case'[':
                pilha_push(p, c);
                break;
            case'{':
                pilha_push(p, c);
                break;
            case ')':
                pop = pilha_pop(p);
                if(pop != '(')
                    return false;
                break;
            case']':
                pop = pilha_pop(p);
                if(pop != '[')
                    return false;
                break;
            case'}':
                pop = pilha_pop(p);
                if(pop != '{')
                    return false;
                break;
            case'\0':
                if(pilha_empty(p))
                    return true;
                return false;
            default:
                return false;
        }
        i++;
    }
    return true;
}