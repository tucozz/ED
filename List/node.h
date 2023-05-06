#ifndef _DATA_STRUCTURES_NODE_H_
#define _DATA_STRUCTURES_NODE_H_

typedef int data_type;

typedef struct Node{
    data_type value;
    struct Node *next;
    struct Node *prev;
}Node;

Node *node_construct(data_type value, Node *prev, Node *next);

void node_destroy(Node *n);

#endif