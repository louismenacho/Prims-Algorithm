#ifndef PRIM_HEADER_H
#define PRIM_HEADER_H

#include <iostream>
#include <fstream>

using namespace std;

class graphNode {
    friend class PrimMST;
private:
    int nodeID;
    int size;
    graphNode* next;
    bool isEmpty;
public:
    graphNode();
    graphNode(int id);
    ~graphNode();
    void Insert(int id);
    void Delete();
};

class edgeNode {
    friend class PrimMST;
private:
    int Ni;
    int Nj;
    int edgeCost;
    edgeNode* next;
public:
    edgeNode(int ni, int nj, int ec);
    edgeNode(int Ni, int Nj, int edgeCost, edgeNode* node);
    ~edgeNode();
    void Insert(edgeNode* node);
    void Delete();
    void printEdgeNode(ofstream& outfile);
};

class PrimMST {
private:
    int N;
    int totalCost;
    int* graphNodeIDArray;
    edgeNode* edgeList;
    graphNode* setA;
    graphNode* setB;
    edgeNode* MSTofG;
public:
    PrimMST(int N);
    void PrimsMST(ofstream& outfile1, ofstream& outfile2);
    void insertEdgeNode(int Ni, int Nj, int edgeCost);
    void removeEdge(int Ni, int Nj);
    void insertSetA(graphNode* newGraphNode);
    void insertSetB(graphNode* newGraphNode);
    void insertMST(edgeNode *newEdgeNode);
    void removeSetB(int N);
    bool inSameSet(int Ni, int Nj);
    void printArray(ofstream& outfile2);
    void printEdgeList(ofstream& outfile2);
    void printProcess(ofstream& outfile2);
    void printFinal(ofstream& outfile1);

    void moveToSetA(int nj);
};


#endif //PRIM_HEADER_H


