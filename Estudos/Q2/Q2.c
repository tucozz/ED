typedef int data_type;

typedef struct{
    data_type *data;
    int size;
    int allocated;
}Pilha;

//ambas as pilhas devem ser construidas no array de tamanho n, passado pelo usuario
void pilha_construct(int n){
    Pilha *p = malloc(sizeof(Pilha));
    p->data = calloc(n, sizeof(data_type));
    p->size = 0;
    p->allocated = n;
}

void pilha_push(Pilha *p1, Pilha *p2, data_type val){
    if(p1->size + p2->size >= p1->allocated){
        printf("ERROR: FULL STACK\n");
        return;
    }
    p1->data[p1->size] = val;
    p1->size++;
}

data_type pilha_pop(Pilha *p){
    if(p->size <= 0){
        printf("ERROR: DEQUER VAZIO\n");
        return -1;
    }
    data_type pop = p->data[p->size - 1];
    p->size--;
    return pop;
}

void pilha_destruct(Pilha *p){
    free(p->data);
    free(p);
}