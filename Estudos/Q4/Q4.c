#include <string.h>

typedef struct 
{
    char *cpf;
    char *nome;
    int idade; 
    float altura; 
} Pessoa; 

typedef struct No
{
    Pessoa p;
    struct No *prox;
} No;

typedef struct 
{
    No *cabeca;
} ListaEncadeada;

// funcao a ser implementada
Pessoa buscar_pessoa(ListaEncadeada *l, char *cpf){
    No *n = l->cabeca;

    while(strcmp(cpf, n->p.cpf) != 0){
        n = n->prox;
    }
        return n->p;
}