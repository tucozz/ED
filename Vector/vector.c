#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "string.h"

// Aloca espaço para um elemento do tipo vector e inicializa os seus atributos.
Vector *vector_construct(){
    Vector *v = calloc(1, sizeof(Vector));
    v->allocated = 10;
    v->size = 0;
    
    v->data = calloc(v->allocated, sizeof(data_type));

    return v;
} 

// Libera o espaço reservado para o vector.
void vector_destroy(Vector *v){
    free(v->data);
    free(v);
}

// Adiciona o item dado ao final do vector e aumenta o tamanho. Aumenta a capacidade alocada se necessário.
void vector_push_back(Vector *v, data_type val){
    if( v->size >= v->allocated){
        v->data = realloc(v->data, 2*v->allocated*sizeof(data_type));
        v->allocated = 2*v->allocated;
    }
    v->data[v->size] = val;
    v->size++;
}

// Retorna o número de elementos atualmente no vector.
int vector_size(Vector *v){return v->size;}

// Retorna o i-ésimo elemento do vector.
data_type vector_get(Vector *v, int i){
    if(i <0 || i >= v->size){
        printf("ERRO: INDICE INVALIDO\n");
        exit(1);
    }
    return v->data[i];
} 

// Atualiza o i-ésimo elemento do vector  para que ele passe a ter o valor val. 
void vector_set(Vector *v, int i, data_type val){
    if(i <0 || i >= v->size){
        printf("ERRO: INDICE INVALIDO\n");
        exit(1);
    }
        v->data[i] = val;
} 

// Retorna o índice da primeira ocorrência do item no Vector ou -1 se o elemento não for encontrado.
int vector_find(Vector *v, data_type val){
    int i;
    
    for(i=0;i<v->size;i++){
        if(v->data[i] == val)
        return i;
    }
    return -1;
}

// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i){
    data_type dt = v->data[i];
    
    for(int j = i; j<v->size-1; j++){
        v->data[j] = v->data[j+1];
    }

    v->size--;

    return dt;
}

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v){
    return vector_remove(v, v->size-1);
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val){
    if( v->size >= v->allocated){
        v->data = realloc(v->data, 2*v->allocated*sizeof(data_type));
        v->allocated = 2*v->allocated;
    }
    for(int j = v->size; j>i;j--){
        v->data[j] = v->data[j-1];
    }
    v->data[i] = val;
    v->size++;
}

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j){
    data_type aux;
    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v){
    for(int i=0, flag = 1;i<v->size-1;i++){
        for(int j=0;j<v->size-i-1;j++){
            if(v->data[j] > v->data[j+1])
            vector_swap(v, j, j+1);
            flag = 0;
        }
        if(flag)
        return;
    }
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val){
    int min = 0, max = v->size-1, central = 0;
    while(1){
        central = (min+max)/2;
        if( v->data[central] == val )
            return central;
        if( min >= max )
            return -1;
        if(v->data[central] > val)
            max = central-1;
        if(v->data[central] < val)
            min = central+1;
    }
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v){
    for(int i=0; i<=(v->size-1)/2;i++)
        vector_swap(v, i, v->size-i-1);
}

// Cria uma cópia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v){
    Vector *v2 = calloc(1, sizeof(Vector));
    v->allocated = v->allocated;
    v->size = v->size;
    
    memcpy(v2->data, v->data, sizeof(*(v->data)));

    return v2;
}

// Remove todos os elementos de v
void vector_clear(Vector *v){
    free(v->data);
    v->allocated = 10;
    v->size = 0;
    
    v->data = calloc(v->allocated, sizeof(data_type));
}

Vector *vector_find_all(Vector *v, data_type val){
    Vector *v2 = vector_construct();
    for(int i=0;i<v->size;i++){
        if(v->data[i] == val){
            vector_push_back(v2, i);
        }
    }
    return v2;
}
