#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    data_type data;
    struct Node *next;
}Node;

struct Queue{
    Node *head;
    Node *last;
    int size;
};

static void node_destroy(Node *n){
    free(n);
}

static Node *node_construct(data_type val, Node* next){
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = val;
    n->next = (struct Node*)next;

    return n;
}

// cria uma queue
Queue *queue_construct(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->size = 0;
    q->head = NULL;
    q->last = NULL;

    return q;
}

// insere um item na queue 
void queue_enqueue(Queue *queue, data_type value){
    Node *new_node = node_construct(value, NULL);
    
    if (queue->last == NULL){
        queue->last = new_node;
        queue->head = queue->last;
    }
    else{
        queue->last->next = (struct Node *)new_node;
        queue->last = (Node *)queue->last->next;
    }

    queue->size++;
}

// remove o elemento mais antigo da pilha e o retorna
data_type queue_dequeue(Queue *queue){
    if(queue->head == NULL)
        exit(printf("Error: list is empty."));

    data_type pop = queue->head->data;
    Node *n =queue->head;
    queue->head = (Node *)queue->head->next;
    node_destroy(n);
    queue->size--;
    if(queue->head == NULL)
        queue->last = NULL;

    return pop;
}

// retorna 1 se a queue está vazia e 0 caso contrário
int queue_empty(Queue *queue){
    return queue->size == 0;
}

// libera o espaco alocado para a queue
void queue_destroy(Queue *queue){
    Node *n = queue->head;
    while (n != NULL){
        Node *next = (Node *)n->next;
        node_destroy(n);
        n = next;
    }

    free(queue);
}
