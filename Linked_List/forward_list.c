#include <forward_list.h>
#include <node.h>
#include "stdlib.h"

// cria uma lista
ForwardList* forward_list_create(){
    ForwardList *lista = malloc(sizeof(lista));
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
    Node *n = node_construct(val, l->head);
    l->head = n;
    l->size++;
}

// mostra a lista na tela
void forward_list_print(ForwardList* l, void (*print_fn)(data_type)){
    Node *n = l->head;

    while (n != NULL){
        print_fn(n->value);
        n = n->next;
    }
}

// retorna o i-ésimo elemento da lista
data_type forward_list_get(ForwardList* l, int i){
    Node *n = l->head;
    
    for(int j=0;j<i;j++){
        n = n->next;
    }

    return n->value;
}
// remove o primeiro elemento
data_type forward_list_pop_front(ForwardList* l){
    data_type pop = l->head->value;
    Node *n =l->head;
    l->head = l->head->next;
    node_destroy(n);
    return pop;
}

// retorna uma lista contendo o reverso de outra
ForwardList* forward_list_reverse(ForwardList* l){
    ForwardList *l2 = forward_list_create();
    for(int i=0; i<l->size; i++){
        forward_list_push_front(l2, forward_list_get(l, i));
    }
}

// remove todos os nós da lista
void forward_list_clear(ForwardList* l){
    for(int i = l->size-1;i>=0;i--){
        node_destroy(forward_list_get(l, i));
    }
    l->head = NULL;
}

// libera o espaço alocado para a lista
void forward_list_destroy(ForwardList* l){
    forward_list_clear(l);
    free(l);
}

// remove todas as ocorrências de um valor da lista
void forward_list_remove(ForwardList* l, data_type val){

}

// remove valores duplicados de uma lista ordenada
void forward_list_unique(ForwardList* l){

}

// adiciona os itens da lista m no início da lista l
void forward_list_cat(ForwardList* l, ForwardList* m){

}

// ordena a lista l
void forward_list_sort(ForwardList* l);