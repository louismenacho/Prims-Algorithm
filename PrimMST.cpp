#include "header.h"

PrimMST::PrimMST(int N) {
    this->N = N;
    totalCost = 0;
    graphNodeIDArray = new int[N+1];
    for (int i = 0; i < N; ++i) {
        graphNodeIDArray[i] = 0;
    }
    edgeList = new edgeNode(-1,-1,-1);
    setA = new graphNode(-9999);
    setB = new graphNode(-9999);
    setB->size = 0;
    MSTofG = new edgeNode(-1,-1,-1);
}

void PrimMST::PrimsMST(ofstream& outfile1, ofstream& outfile2) {

    //step 4,5,6
    bool firstFound;
    for (int k = 1; k <= N; ++k) {
        if(graphNodeIDArray[k] > 0){
            if(!firstFound){
                graphNode* newGraphNode = new graphNode(k);
                insertSetA(newGraphNode);
                firstFound = true;
            } else {
                graphNode* newGraphNode = new graphNode(k);
                insertSetB(newGraphNode);
            }
        }
    }

    printArray(outfile2);
    printEdgeList(outfile2);

    //step 10 : repeat 7-9
    printProcess(outfile2);
    edgeNode *newEdge = edgeList->next;
    while (!setB->isEmpty) {
        //step 7
        int Ni = newEdge->Ni;
        int Nj = newEdge->Nj;
        int cost = newEdge->edgeCost;
        if (inSameSet(Ni, Nj)) {
            newEdge = newEdge->next;
        }//step 8
        else {
            insertMST(new edgeNode(Ni,Nj,cost));
            totalCost += newEdge->edgeCost;
            removeEdge(Ni, Nj);
            newEdge = edgeList->next;
            //step 9
            printProcess(outfile2);
        }
    }
    //step 11
    printFinal(outfile1);
}

bool PrimMST::inSameSet(int Ni, int Nj) {
    bool NiA = false;
    bool NjA = false;
    bool NiB = false;
    bool NjB = false;

    //check Set A
    graphNode* current = setA->next;
    while(current != NULL) {
        if(current->nodeID == Ni) {
            NiA = true;
        }
        if(current->nodeID == Nj) {
            NjA = true;
        }
        current = current->next;
    }


    //check Set B
    current = setB->next;
    while(current != NULL) {
        if(current->nodeID == Ni) {
            NiB = true;
        }
        if(current->nodeID == Nj) {
            NjB = true;
        }
        current = current->next;
    }


    if(NiA && NjA){
        return true;
    }
    if(NiB && NjB){
        return true;
    }

    if(NiB){
        removeSetB(Ni);
        insertSetA(new graphNode(Ni));
    } else if(NjB){
        removeSetB(Nj);
        insertSetA(new graphNode(Nj));
    }
    return false;
}

void PrimMST::insertEdgeNode(int Ni, int Nj, int edgeCost) {
    if (edgeCost < edgeList->edgeCost){
        edgeList = new edgeNode(Ni,Nj,edgeCost, edgeList); // case 1: insert at beginning
    } else {
        edgeNode* current = edgeList;
        edgeNode* previous = edgeList;
        while (current != NULL){
            if(current->edgeCost < edgeCost){
                previous = current;
                current = current->next;
            }else {
                previous->next = new edgeNode(Ni,Nj,edgeCost, current);// case 2: insert into middle
                break;
            }
        }// while END
        if (current == NULL){
            previous->next = new edgeNode(Ni,Nj,edgeCost, NULL);// case 3: insert at end
        }
    }
    graphNodeIDArray[Ni]++;
    graphNodeIDArray[Nj]++;
}


void PrimMST::insertSetA(graphNode *newGraphNode) {
    graphNode* current = setA;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newGraphNode;
}

void PrimMST::insertSetB(graphNode *newGraphNode) {
    graphNode* current = setB;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newGraphNode;
    setB->size++;
}

void PrimMST::insertMST(edgeNode *newEdgeNode) {
    edgeNode* current = MSTofG;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newEdgeNode;
}

void PrimMST::removeEdge(int Ni, int Nj) {
    edgeNode *current = edgeList;
    while (current->next != NULL) {
        if(current->next->next == NULL && current->next->Ni == Ni && current->next->Nj == Nj){
            current->next = NULL;
            continue;
        } else if (current->next->Ni == Ni && current->next->Nj == Nj) {
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void PrimMST::removeSetB(int N) {
    graphNode *current = setB;
    while (current->next != NULL) {
        if(current->next->next == NULL && current->next->nodeID == N){
            current->next = NULL;
            continue;
        } else if (current->next->nodeID == N) {
            current->next = current->next->next;
        }
        current = current->next;
    }
    setB->size--;
    if(setB->size == 0)
        setB->isEmpty = true;
}

void PrimMST::moveToSetA(int N) {
    graphNode* newGraphNode = new graphNode(N);
    insertSetA(newGraphNode);
}

void PrimMST::printArray(ofstream &outfile2) {
    //print array
    outfile2 << "\nGraph Node ID Array:\n";
    for (int i = 1; i <= N; ++i) {
        outfile2 << "Node " << i << ": " << graphNodeIDArray[i] << endl;
    }
    outfile2 << endl;
}

void PrimMST::printEdgeList(ofstream &outfile2) {
    //print edgeList
    outfile2 <<"Edge List\n";
    edgeNode* currentEN = edgeList->next;
    int count = 0;
    while(count < 10) {
        currentEN->printEdgeNode(outfile2);
        currentEN = currentEN->next;
        count++;
    }
    outfile2 << endl;
}


void PrimMST::printProcess(ofstream& outfile2) {
    outfile2 << "----------------------------";

    outfile2 << "\nMST of G: Total Cost = " << totalCost << endl;
    outfile2 << N << endl;
    edgeNode* currentEN = MSTofG->next;
    while(currentEN != NULL) {
        currentEN->printEdgeNode(outfile2);
        currentEN = currentEN->next;
    }
    outfile2 << endl;

    outfile2 << "\nSet A\n";
    graphNode* currentGN = setA->next;
    while(currentGN != NULL) {
        outfile2 << currentGN->nodeID << endl;
        currentGN = currentGN->next;
    }
    outfile2 << endl;

    outfile2 << "\nSet B\n";
    currentGN = setB->next;
    while(currentGN != NULL) {
        outfile2 << currentGN->nodeID << endl;
        currentGN = currentGN->next;
    }
    outfile2 << "----------------------------\n";


}

void PrimMST::printFinal(ofstream& outfile1) {
    outfile1 << "***FINAL***";
    outfile1 << "\nMST of G: Total Cost = " << totalCost << endl;
    outfile1 << N << endl;
    edgeNode* currentEN = MSTofG->next;
    while(currentEN != NULL) {
        currentEN->printEdgeNode(outfile1);
        currentEN = currentEN->next;
    }
    outfile1 << endl;
}







