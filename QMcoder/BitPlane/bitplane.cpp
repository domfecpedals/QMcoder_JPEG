
//  main.cpp
//  bitPlane
//
//  Created by Yuan Liu on 2/17/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "bitio.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <queue>
#include <string.h>
#include <vector>


//#define  BYTE  unsigned char

using namespace std;

int getFileSize(char *filename);

int main(int argc, char * argv[]) {

    int      size;
    unsigned char   **in_img, **out_img;
    

    char *filename;
    
    
    
    if(argv[1]!=NULL){
        filename=argv[1];
    }else{
        cout<<"No input file selected"<<endl;
        cout<<"Format ./bitplane [input filename]"<<endl;
        exit(1);
    }

   


    in_img=new unsigned char*[size];
    out_img=new unsigned char*[size];
    for(int i=0;i<size;i++){
        in_img[i]=new unsigned char[size];
        out_img[i]=new unsigned char[size];
    }
    
    
    
    BIT_FILE *infile;
    infile = OpenInputBitFile(filename);
    
    
    
    char *output=new char[64];
    strcat(output, filename);
    strcat(output, ".BP");
    
    BIT_FILE *output_file;
    output_file = OpenOutputBitFile(output);
    size = getFileSize(filename);
    
    int *temp=new int[size*8];
    
    int counter=0;
    while(counter<size*8){
        //int newbit=InputBit(infile);
        
        temp[counter]=InputBit(infile);
        
        counter++;
    }
    
    
   
    
 
    // Plane 1 to 7
    for (int bitp=1;bitp<9;bitp++){
        for (int i=0;i<size*8;i++){
            if((i+1)%8==bitp){
                OutputBit(output_file, temp[i]);
            }
        }
    }
    
    // Add last plane
    for (int i=0;i<size*8;i++){
        if((i+1)%8==0){
            OutputBit(output_file, temp[i]);
        }
    }
    
    CloseOutputBitFile(output_file);
    CloseInputBitFile(infile);

    
    
    return 0;
}


// This function is from online source of C++ IO routine
int getFileSize(char *filename){
    streampos size;
    ifstream file(filename, ios::in|ios::binary|ios::ate);
    if(file.is_open()) {
        size = file.tellg();
        file.close();
    }else{
        cout << "Unable to open output file.!!!" << endl;
    }
    return size;
}


