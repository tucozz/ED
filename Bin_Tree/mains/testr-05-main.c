
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

typedef struct
{
    char *name;
    int idade;
    float altura;
} Person;

Person *person_construct(const char *name, int idade, float altura)
{
    Person *p = (Person *)calloc(1, sizeof(Person));

    p->name = (char *)calloc(strlen(name) + 1, sizeof(char));
    p->idade = idade;
    p->altura = altura;

    memcpy(p->name, name, (strlen(name) + 1) * sizeof(char));

    return p;
}

void person_destroy(Person *p)
{
    free(p->name);
    free(p);
}

int cmp_fn(void *a, void *b)
{
    return strcmp(a, b);
}

void key_destroy_fn(void *key)
{
    free(key);
}

void val_destroy_fn(void *val)
{
    person_destroy((Person *)val);
}

int main()
{
    int i, n, idade;
    float altura;
    char op[20];
    char nome[100];

    scanf("%d", &n);

    BinaryTree *bt = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", op);

        if (!strcmp(op, "SET"))
        {
            scanf("%s %d %f", nome, &idade, &altura);
            binary_tree_add(bt, strdup(nome), person_construct(nome, idade, altura));
        }
        else
        {
            if (!binary_tree_empty(bt))
            {
                KeyValPair *pair;

                if (!strcmp(op, "POP_MAX"))
                    pair = binary_tree_pop_max(bt);
                else
                    pair = binary_tree_pop_min(bt);

                Person *p = pair->value;
                printf("%s %d %.2f\n", p->name, p->idade, p->altura);

                key_destroy_fn(pair->key);
                val_destroy_fn(pair->value);
                key_val_pair_destroy(pair);
            }
            else
                printf("ARVORE VAZIA\n");
        }
    }

    binary_tree_destroy(bt);

    return 0;
}