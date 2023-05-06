#ifndef _DATA_STRUCTURES_LIST_H_
#define _DATA_STRUCTURES_LIST_H_

#include "node.h"

typedef struct{
    int size;
    Node *head;
    Node *last;
}List;

// cria uma lista
List* list_construct();
// retorna o número de elementos na lista
int list_size(List* l);
// adiciona um item no início da lista
void list_push_front(List* l, data_type val);
// mostra a lista na tela
void list_print(List* l, void (*print_fn)(data_type));
// retorna o i-ésimo elemento da lista
data_type list_get(List* l, int i);
// remove o primeiro elemento
data_type list_pop_front(List* l);
// retorna uma lista contendo o reverso de outra
List* list_reverse(List* l);
// remove todos os nós da lista
void list_clear(List* l);
// libera o espaço alocado para a lista
void list_destroy(List* l);
// remove todas as ocorrências de um valor da lista
void list_remove(List* l, data_type val);
// adiciona os itens da lista m no início da lista l
void list_cat(List* l, List* m);
// insere um elemento ao final 
void list_push_back(List *l, data_type data);
// remove e retorna o último elemento
data_type list_pop_back(List *l);
// mostra a lista na tela de tras para frente
void list_print_reverse(List* l, void (*print_fn)(data_type));

#endif