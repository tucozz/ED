#include "binary_tree.h"
#include <stdlib.h>

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = malloc(sizeof(KeyValPair));
    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    key_destroy_fn(kvp->key);
    val_destroy_fn(kvp->value);
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *node = malloc(sizeof(Node));
    node->kvp = key_val_pair_construct(key, value);
    node->right = left;
    node->left = right;

    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    key_val_pair_destroy(node->kvp, key_destroy_fn, val_destroy_fn);
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *bn = malloc(sizeof(BinaryTree));
    bn->root = NULL;
    bn->cmp_fn = cmp_fn;
    bn->key_destroy_fn = key_destroy_fn;
    bn->val_destroy_fn = val_destroy_fn;

    return bn;
}

Node *_add_recursive(Node *node, void *key, data_type value, CmpFn cmp_fn) {
    if (node == NULL)
        return node_construct(key, value, NULL, NULL);
    if (cmp_fn(key, node->kvp->key) < 0)
        node->left = _add_recursive(node->left, key, value, cmp_fn);
    else
        node->right = _add_recursive(node->right, key, value, cmp_fn);
    return node;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    bt->root = _add_recursive(bt->root, key, value, bt->cmp_fn);
}

int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);

KeyValPair *binary_tree_min(BinaryTree *bt){
    Node *node = bt->root;
    while(node->left != NULL)
        node = node->left;
    return node->kvp;
}

KeyValPair *binary_tree_max(BinaryTree *bt){
    Node *node = bt->root;
    while(node->right != NULL)
        node = node->right;
    return node->kvp;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);

void *binary_tree_get_recursive(Node *current, void *key, CmpFn cmp_fn){
    if(current == NULL || cmp_fn(current->kvp->key, key) == 0)
        return current;
    //isso assume que a funcao funciona apontando pra quem eh maior
    else if(cmp_fn(current->kvp->key, key) > 0)
        return binary_tree_get_recursive(current->left, key, cmp_fn);
    else
        return binary_tree_get_recursive(current->right, key, cmp_fn);    
}

void *binary_tree_get(BinaryTree *bt, void *key){
    Node *result = binary_tree_get_recursive(bt->root, key, bt->cmp_fn);
    if(result)
        return result->kvp->value;
    return NULL;
}

void binary_tree_destroy_recursive(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    if(node == NULL)
        return;
    binary_tree_destroy_recursive(node->left, key_destroy_fn, val_destroy_fn);
    binary_tree_destroy_recursive(node->right, key_destroy_fn, val_destroy_fn);
    node_destroy(node, key_destroy_fn, val_destroy_fn);
}

void binary_tree_destroy(BinaryTree *bt){
    binary_tree_destroy_recursive(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);


