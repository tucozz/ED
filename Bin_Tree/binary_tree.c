#include "binary_tree.h"
#include <stdio.h>

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->right = left;
    node->left = right;

    return node;
}
void node_destroy(Node *node);

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *bn = malloc(sizeof(BinaryTree));
    bn->root = NULL;
    bn->cmp_fn = cmp_fn;
    bn->key_destroy_fn = key_destroy_fn;
    bn->val_destroy_fn = val_destroy_fn;

    return bn;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);

void *binary_tree_get(BinaryTree *bt, void *key){
    Node *current = bt->root;
    if(current == NULL || bt->cmp_fn(current->key, key) == 0)
        return current;
    //isso assume que a funcao funciona apontando pra quem eh maior
    else if(bt->cmp_fn(current, key) < 0)
        return binary_tree_peek_recursive(current->left, bt->cmp_fn);
    else
        return binary_tree_peek_recursive(current->right, bt->cmp_fn);    
}

void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);


