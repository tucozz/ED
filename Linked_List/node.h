#ifndef _DATA_STRUCTURES_NODE_H_
#define _DATA_STRUCTURES_NODE_H_

typedef int data_type;

typedef struct{
    data_type value;
    Node *next;
}Node;

Node *node_construct(data_type value, Node *next);

void node_destroy(Node *n);

#endif