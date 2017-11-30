#include "header.h"


graphNode::graphNode() {
    next = NULL;
    isEmpty = true;
    size = 0;
}

graphNode::graphNode(int id) {
    nodeID = id;
    next = NULL;
}

graphNode::~graphNode() {
    delete next;
}

void graphNode::Insert(int id) {
    graphNode* current = this;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new graphNode(id);
}


void graphNode::Delete() {
    graphNode* current = this;
    while (current->next != NULL) {
        if(current->next->next == NULL){
            current->next = NULL;
            continue;
        } else {
            current->next = current->next->next;
        }
        current = current->next;
    }
}


