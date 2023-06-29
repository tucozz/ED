#include "binary_tree.h"

typedef struct{
    void *key;
    void *value;
    //cmp_fn
    struct Node *left_child;
    struct Node *right_child;
}Node;

struct Binary_Tree{
    Node *root;
    size_t size;
};

static Node *node_construct(void *key, void *value){
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->right_child = NULL;
    node->left_child = NULL;

    return node;
}

Binary_Tree *binary_tree_construct(size_t size){
    Binary_Tree *bn = malloc(sizeof(Binary_Tree));
    bn->root = NULL;
    bn->size = size;

    return bn;
}

void *binary_tree_peek_recursive(Binary_Tree *tree, void *key){
    Node *current = tree->root;
    if(current == NULL || tree->cmp_fn(current->key, key) == 0)
        return current;
    //isso assume que a funcaoo funciona apontando pra quem eh maior
    else if(tree->cmp_fn(current, key) < 0)
        return binary_tree_peek_recursive(current->left_child);
    else
        return binary_tree_peek_recursive(current->right_child);    
}




