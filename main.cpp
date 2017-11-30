//
//  main.cpp
//  PrimMST
//
//  Created by Louis Menacho on 12/1/15.
//  Copyright (c) 2015 QC. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

int main(int argc, char * argv[]) {

    ifstream infile(argv[1]);

    int readNum;
    int Ni;
    int Nj;
    int cost;
    int control = 1;

    infile >> readNum;
    PrimMST primMST(readNum);

    while(infile >> readNum){
        if(control == 1){
            Ni = readNum;
            control++;
        }
        else if(control == 2){
            Nj = readNum;
            control++;
        }
        else if(control == 3){
            cost = readNum;
            primMST.insertEdgeNode(Ni,Nj,cost);
            control = 1;
        }
    }


    ofstream outfile1;
    ofstream outfile2;
    outfile1.open(argv[2]);
    outfile2.open(argv[3]);

    primMST.PrimsMST(outfile1,outfile2);

    outfile1.close();
    outfile2.close();
    return 0;
}