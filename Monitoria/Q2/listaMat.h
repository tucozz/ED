#ifndef _DATA_STRUCTURES_LIST_H_
#define _DATA_STRUCTURES_LIST_H_

#include "matriz.h"

typedef unsigned int bool;
typedef Matriz* data_type;

typedef struct ListIterator ListIterator;
typedef struct List List;
typedef struct Node Node;

// cria uma lista
List* list_construct();
// retorna o número de elementos na lista
int list_size(List* l);
// retorna o primeiro node da lista
Node* list_head(List* l);
// retorna o ultimo node da lista
Node* list_last(List* l);
// adiciona um item no início da lista
void list_print(List* l, void (*print_fn)(data_type));
// retorna o i-ésimo elemento da lista
data_type list_get(List* l, int i);
// remove o primeiro elemento
data_type list_pop_front(List* l);
// remove todos os nós da lista
void list_clear(List* l);
// libera o espaço alocado para a lista
void list_destroy(List* l);
// insere um elemento ao final 
void list_push_back(List *l, data_type data);
// remove e retorna o último elemento
data_type list_pop_back(List *l);
// cria um iterador para percorrer a lista do início para o final.
ListIterator *list_front_iterator(List *l);
// retorna o elemento do nó atual e move o iterador para o próximo nó.
data_type *list_iterator_next(ListIterator *it);
// retorna o elemento do nó atual e move o iterador para o nó anterior.
data_type *list_iterator_previous(ListIterator *it);
// verifica se o iterador chegou ao final da lista
bool list_iterator_is_over(ListIterator *it);
// libera a memória alocada para o iterador
void list_iterator_destroy(ListIterator *it);

#endif