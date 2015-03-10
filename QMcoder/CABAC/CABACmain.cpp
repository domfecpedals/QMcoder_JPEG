//
//  main.cpp
//  CABAC
//
//  Created by Yuan Liu on 2/16/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <queue>
#include <string.h>
#include <vector>
#include <iostream>
#include "bitio.h"
#include "QMCODER.H"




using namespace std;

int getFileSize(char *filename);

int main(int argc, char * argv[]) {

    int contextbits=3;

    int contextlist[3]={};

    
    
    char *filename="image.dat-huffman.out";
    
    
    
    
    if(argv[1]==NULL){
        cout<<"Missing parameters"<<endl;
        cout<<"Usage: ./CABAC [filename] [context]"<<endl;
        exit(1);
    }else{
        filename=argv[1];
    }
    if(argv[2]==NULL){
        cout<<"Missing parameters"<<endl;
        cout<<"Usage: ./CABAC [filename] [context]"<<endl;
        exit(1);
    }else{
        contextbits=atof(argv[2]);
    }
    
    char *output=new char[64];
    strcat(output, filename);
    strcat(output, ".CABAC.");
    strcat(output, argv[2]);
    
    BIT_FILE *output_file;
    output_file = OpenOutputBitFile(output);
    
    
    BIT_FILE *infile;
    infile = OpenInputBitFile(filename);
    int filesize=getFileSize(filename);
    
    QM coder(output_file->file);
    coder.StartQM("encode");
    
    int counter=0;
    
    while(counter<filesize*8){
        int newbit=InputBit(infile);
        int context=0;
        
        // Calculate context
        for(int i = 0; i< contextbits; i++){
            context += pow(2,i)*contextlist[i];
        }
        
        // Encode use context
        coder.encode(newbit, context);
        
        
        // Update context
        for(int i = contextbits-1; i >= 0; i--){
            if(i == 0){
                contextlist[i] = contextbits;
            }
            else{
                contextlist[i] = contextlist[i-1];
            }
        }
  
        
        counter++;
    }
    
    coder.Flush();
    CloseOutputBitFile(output_file);
    CloseInputBitFile(infile);
    cout<<"CABAC done! Output file is: "<<output<<endl;
    return 0;
}


int getFileSize(char *filename){
    streampos size;
    ifstream file (filename, ios::in|ios::binary|ios::ate);
    if(file.is_open()) {
        size = file.tellg();
        file.close();
    }else{
        cout << "Unable to open output file.!!!" << endl;
    }
    return size;
}
