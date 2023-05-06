#include "list.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>

// cria uma lista
List* list_construct(){
    List *lista = (List *)malloc(sizeof(lista));
    lista->size = 0;
    lista->head = NULL;
    lista->last = NULL;

    return lista;
}

// retorna o número de elementos na lista
int list_size(List* l){
    return l->size;
}

// adiciona um item no início da lista
void list_push_front(List* l, data_type val){
    Node *new_node = node_construct(val, NULL, l->head);
    if (l->head != NULL)
        l->head->prev = new_node;
    l->head = new_node;
    l->size++;

    if(l->size == 1)
        l->last = l->head;
}

// mostra a lista na tela
void list_print(List* l, void (*print_fn)(data_type)){
    Node *n = l->head;

    printf("[");
    while (n != NULL){
        print_fn(n->value);
        n = n->next;

        if(n != NULL)
            printf(", ");
    }
    printf("]");
}

// retorna o i-ésimo elemento da lista
data_type list_get(List* l, int i){
    if(i < 0 || i > l->size)
        exit(printf("Error: index out of bounds."));

    Node *n = l->head;

    for(int j=0;j<i;j++){
        n = n->next;
    }

    return n->value;
}
// remove o primeiro elemento
data_type list_pop_front(List* l){
    if(l->head == NULL)
        exit(printf("Error: list is empty."));

    data_type pop = l->head->value;
    Node *n =l->head;
    l->head = l->head->next;
    if(l->head != NULL)
        l->head->prev = NULL;
    node_destroy(n);
    l->size--;

    if(l->size <= 1)
        l->last = l->head;

    return pop;
}

// retorna uma lista contendo o reverso de outra
List* list_reverse(List* l){
    List *l2 = list_construct();

    Node *n = l->head;
    while(n != NULL){
        list_push_front(l2, n->value);
        n = n->next;
    }

    return l2;
}

// remove todos os nós da lista
void list_clear(List* l){
    int n_itens = l->size;
    
    for(int i = 0; i < n_itens; i++){
        list_pop_front(l);
    }
}

// libera o espaço alocado para a lista
void list_destroy(List* l){
    Node *n = l->head;
    while (n != NULL){
        Node *next = n->next;
        node_destroy(n);
        n = next;
    }

    free(l);
}

// remove todas as ocorrências de um valor da lista
void list_remove(List* l, data_type val){
    Node *n = l->head, *prev = NULL,*new_n = NULL;
    while (n != NULL) {
        if (n->value == val) {
            if (prev == NULL)
            l->head = new_n = n->next;
            else
                prev->next = new_n = n->next;
        
            node_destroy(n);
            n = new_n;
            l->size--;
        }
        else {
            prev = n;
            n = n->next;
        }
    }

}

// adiciona os itens da lista m no início da lista l
void list_cat(List* l, List* m){
    Node *n = m->head;

    while(n != NULL){
        list_push_front(l, n->value);
        n = n->next;
    }
}

// insere um elemento ao final 
void list_push_back(List *l, data_type data){
    Node *new_node = node_construct(data, l->last, NULL);
    
    if (l->last == NULL)
        l->head = l->last = new_node;
    else
        l->last = l->last->next = new_node;
    l->size++;
}

// remove e retorna o último elemento
data_type list_pop_back(List *l){
    Node *querodestruir = l->last;

    querodestruir->prev->next = NULL;
    data_type pop = querodestruir->value;
    l->last = querodestruir->prev;
    node_destroy(querodestruir);

    return pop;
}

// mostra a lista na tela de tras para frente
void list_print_reverse(List* l, void (*print_fn)(data_type)){
    Node *n = l->last;

    printf("[");
    while (n != NULL){
        print_fn(n->value);
        n = n->prev;

        if(n != NULL)
            printf(", ");
    }
    printf("]");
}