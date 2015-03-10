//
//  readTable.cpp
//  QMcoder
//
//  Created by Yuan Liu on 2/15/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include "readTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readTable(char *filename, TABLEROW *table){
    
    //read the file
    ifstream infile(filename, ios_base::in | ios_base::binary);
    
    if(!infile.is_open()){
        cout<<"Cannot open transition table!"<<endl;
        exit(1);
    }
    
    
    //create a buffer to store values
    char buff[80];
    
    //Get single line
    int i=0;
    double p=0;
    
    while(infile.good()){
        TABLEROW *qt = new TABLEROW;
        initial(qt);
        infile.getline(buff,80);
        char * pEnd;

        qt->state = strtol (buff,&pEnd,10);
        qt->Qe = strtol (pEnd,&pEnd,16);
        //P is just for human read
        p = strtod (pEnd,&pEnd);
        qt->increaseState = strtol (pEnd,&pEnd,10);
        
        //save as interger, so s is represented by 0;
        qt->decreaseState = strtol (pEnd,NULL,10);
        
        table[i]=*qt;
        i++;
    }
}

void initial(TABLEROW *qt){
    qt->state=0;
    qt->Qe=0;
    qt->increaseState=0;
    qt->decreaseState=0;
}