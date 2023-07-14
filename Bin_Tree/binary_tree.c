#include "binary_tree.h"
#include <stdlib.h>

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = malloc(sizeof(KeyValPair));
    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right, Node* parent){
    Node *node = malloc(sizeof(Node));
    node->kvp = key_val_pair_construct(key, value);
    node->right = left;
    node->left = right;
    node->parent = parent;

    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    key_destroy_fn(node->kvp->key);
    val_destroy_fn(node->kvp->value);
    key_val_pair_destroy(node->kvp);
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

Node *_add_recursive(Node *node, void *key, data_type value, CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    if (node == NULL)
        return node_construct(key, value, NULL, NULL, NULL);
    if (cmp_fn(key, node->kvp->key) == 0){
        val_destroy_fn(node->kvp->value);
        node->kvp->value = value;
        key_destroy_fn(key);
        return node;
    }
    if (cmp_fn(key, node->kvp->key) < 0){
        node->left = _add_recursive(node->left, key, value, cmp_fn, key_destroy_fn, val_destroy_fn);
        node->left->parent = node;
    }
    else{
        node->right = _add_recursive(node->right, key, value, cmp_fn, key_destroy_fn, val_destroy_fn);
        node->right->parent = node;
    }
    return node;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    bt->root = _add_recursive(bt->root, key, value, bt->cmp_fn, bt->key_destroy_fn, bt->val_destroy_fn);
}

int binary_tree_empty(BinaryTree *bt){return bt->root == NULL;}

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

void Transplant(BinaryTree *T, Node *u, Node *v){
    if(u->parent == NULL)
        T->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v != NULL)
        v->parent = u->parent;
}

Node *Node_min(Node* node){
    while(node->left != NULL)
        node = node->left;
    return node;
}

Node *Node_max(Node* node){
    while(node->right != NULL)
        node = node->right;
    return node;
}

void binary_tree_delete(BinaryTree *T, Node *z){
    Node *y = NULL;
    if(z->left == NULL)
        Transplant(T, z, z->right);
    else if(z->right == NULL)
        Transplant(T, z, z->left);
    else{
        y = Node_min(z->right); 
        if(y->parent != z){
            Transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void binary_tree_remove(BinaryTree *bt, void *key){
    Node *result = binary_tree_get_recursive(bt->root, key, bt->cmp_fn);
    binary_tree_delete(bt, result);
    node_destroy(result, bt->key_destroy_fn, bt->val_destroy_fn);
}

KeyValPair *binary_tree_min(BinaryTree *bt){
    Node *node = Node_min(bt->root);
    return node->kvp;
}

KeyValPair *binary_tree_max(BinaryTree *bt){
    Node *node = Node_max(bt->root);
    return node->kvp;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    Node *node = Node_min(bt->root);
    KeyValPair *kvp = node->kvp;
    binary_tree_delete(bt, node);
    free(node);
    return kvp;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
    Node *node = Node_max(bt->root);
    KeyValPair *kvp = node->kvp;
    binary_tree_delete(bt, node);
    free(node);
    return kvp;
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

void inorder_recursive_aux(Node *n, Vector *v){
    if(n == NULL)
        return;
    inorder_recursive_aux(n->left, v);
    vector_push_back(v, n->kvp);
    inorder_recursive_aux(n->right, v);
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){
    Vector *vector = vector_construct();
    inorder_recursive_aux(bt->root, vector);
    return vector;
}

void preorder_recursive_aux(Node *n, Vector *v){
    if(n == NULL)
        return;
    vector_push_back(v, n->kvp);
    preorder_recursive_aux(n->left, v);
    preorder_recursive_aux(n->right, v);
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){
    Vector *vector = vector_construct();
    preorder_recursive_aux(bt->root, vector);
    return vector;
}

void postorder_recursive_aux(Node *n, Vector *v){
    if(n == NULL)
        return;
    postorder_recursive_aux(n->left, v);
    postorder_recursive_aux(n->right, v);
    vector_push_back(v, n->kvp);
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt){
    Vector *vector = vector_construct();
    postorder_recursive_aux(bt->root, vector);
    return vector;
}


