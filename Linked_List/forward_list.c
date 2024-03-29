#include "forward_list.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>

// cria uma lista
ForwardList* forward_list_construct(){
    ForwardList *lista = (ForwardList *)malloc(sizeof(lista));
    lista->size = 0;
    lista->head = NULL;

    return lista;
}

// retorna o número de elementos na lista
int forward_list_size(ForwardList* l){
    return l->size;
}

// adiciona um item no início da lista
void forward_list_push_front(ForwardList* l, data_type val){
    l->head = node_construct(val, l->head);
    l->size++;
}

// mostra a lista na tela
void forward_list_print(ForwardList* l, void (*print_fn)(data_type)){
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
data_type forward_list_get(ForwardList* l, int i){
    if(i < 0 || i > l->size)
        exit(printf("Error: index out of bounds."));

    Node *n = l->head;

    for(int j=0;j<i;j++){
        n = n->next;
    }

    return n->value;
}
// remove o primeiro elemento
data_type forward_list_pop_front(ForwardList* l){
    if(l->head == NULL)
        exit(printf("Error: list is empty."));

    data_type pop = l->head->value;
    Node *n =l->head;
    l->head = l->head->next;
    node_destroy(n);

    return pop;
}

// retorna uma lista contendo o reverso de outra
ForwardList* forward_list_reverse(ForwardList* l){
    ForwardList *l2 = forward_list_construct();

    Node *n = l->head;
    while(n != NULL){
        forward_list_push_front(l2, n->value);
        n = n->next;
    }

    return l2;
}

// remove todos os nós da lista
void forward_list_clear(ForwardList* l){
    int n_itens = l->size;
    
    for(int i = 0; i < n_itens; i++){
        forward_list_pop_front(l);
    }
}

// libera o espaço alocado para a lista
void forward_list_destroy(ForwardList* l){
    Node *n = l->head;
    while (n != NULL){
        Node *next = n->next;
        node_destroy(n);
        n = next;
    }

    free(l);
}

// remove todas as ocorrências de um valor da lista
void forward_list_remove(ForwardList* l, data_type val){
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
void forward_list_cat(ForwardList* l, ForwardList* m){
    Node *n = m->head;

    while(n != NULL){
        forward_list_push_front(l, n->value);
        n = n->next;
    }
}
