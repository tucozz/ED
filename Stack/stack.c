#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    data_type data;
    struct Node *next;
}Node;

struct Stack{
    Node *head;
    int size;
};

static void node_destroy(Node *n){
    free(n);
}

static Node *node_construct(data_type val, Node* next){
    Node *n = (Node *)malloc(sizeof(n));
    n->data = val;
    n->next = (struct Node*)next;

    return n;
}

// cria uma stack
Stack *stack_construct(){
    Stack *s = (Stack*)malloc(sizeof(s));
    s->size = 0;
    s->head = NULL;

    return s;
}

// insere um item na stack
void stack_push(Stack *s, data_type val){
    s->head = node_construct(val, s->head);
    s->size++;
}

// remove o ultimo item inserido e o retorna
data_type stack_pop(Stack *s){
    if(s->head == NULL)
        exit(printf("Error: list is empty."));

    data_type pop = s->head->data;
    Node *n =s->head;
    s->head = (Node *)s->head->next;
    node_destroy(n);
    s->size--;

    return pop;
}

// retorna 1 se a stack está vazia e 0 caso contrário
int stack_empty(Stack *s){
    return s->size == 0;
}

// libera o espaço alocado para a stack
void stack_destroy(Stack *s){
    Node *n = s->head;
    while (n != NULL){
        Node *next = (Node *)n->next;
        node_destroy(n);
        n = next;
    }

    free(s);
}
