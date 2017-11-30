#include "header.h"
#include <iostream>
using namespace std;

edgeNode::edgeNode(int ni, int nj, int ec) {
    Ni = ni;
    Nj = nj;
    edgeCost = ec;
    next = NULL;
}

edgeNode::edgeNode(int ni, int nj, int ec, edgeNode* node) {
    Ni = ni;
    Nj = nj;
    edgeCost = ec;
    next = node;
}

edgeNode::~edgeNode() {
    delete next;
}

void edgeNode::Insert(edgeNode* node) {
    edgeNode* current = this;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = node;
}

void edgeNode::Delete() {
    edgeNode* current = this;
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

void edgeNode::printEdgeNode(ofstream& outfile) {
    outfile << Ni << " " << Nj << " " << edgeCost << endl;
}