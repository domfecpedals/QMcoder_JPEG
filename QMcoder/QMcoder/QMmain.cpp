//
//  main.cpp
//  QMcoder
//
//  Created by Yuan Liu on 2/10/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <queue>
#include <string.h>
#include <vector>
#include "readTable.h"
#include "bitio.h"

using namespace std;

void help();
int getFileSize(char *filename);
void renormalize(BIT_FILE *outfile);

unsigned int A;
unsigned short int C;
int currentState;
unsigned int Qe;
bool carry;
int MPS;

int compressedsize;


int main(int argc, char * argv[]) {
    char * filename;
    compressedsize=0;
    
    if(argv[1]!=NULL){
        filename=argv[1];
        cout<<"Input file is: "<<filename<<endl;
    }else{
        help();
        exit(1);
    }
    
    

    
    
    
    
    
    
    TABLEROW table[46]={};
    readTable("QM_state_transition_table.txt", table);
    
    
    //Open output file using bitio routine
    char *output=new char[64];
    strcat(output, filename);
    strcat(output, ".QM");
    
    BIT_FILE *output_file;
    output_file = OpenOutputBitFile(output);
    
    
    BIT_FILE *infile;
    infile = OpenInputBitFile(filename);
    
    
    
    
    //set initial state;
    A = 0x10000;
    C = 0x0000;
    currentState = 10;
    Qe = table[currentState].Qe;
    carry = false;
    MPS = 0;
    

    
    
    
   // cout<<size<<endl;
    // counter and size of file help find EOF
    int counter=0;
    int size=getFileSize(filename);
    cout<<size<<endl;
    
    
    
    while(counter<size*8){
        int newbit=InputBit(infile);
       
        //new bit is MPS
        if(newbit==MPS){
            A-=Qe;
            if(A<0x8000){
                if(A < Qe){
                if((A+C)>0xffff){
                    carry=true;
                }
                C+=A;
                A=Qe;
            }
            // change state, increase, update Qe
            int step=table[currentState].increaseState;
            currentState+=step;
            Qe=table[currentState].Qe;
            
            
            renormalize(output_file);
            }
            
        }else{ //new bit is LPS
            
            A-=Qe;
            if(A>=Qe){
                if(A+C>0xffff){
                    carry=true;
                }
                C+=A;
                A=Qe;
            }
            
            // change state, decrease, update Qe, swap MPS if state=0
            int step=table[currentState].decreaseState;
            currentState-=step;
            if(table[currentState].decreaseState==0){
                MPS=abs(1-MPS);// MSP=1 or 0, this will swap 1 and 0
            }
            Qe=table[currentState].Qe;
 
            renormalize(output_file);
            
        }
        
        counter++;
        
      //  cout<<counter<<endl;
        
    }
    cout<<"Compressed size: "<<ceilf(compressedsize/8)<<endl;
    CloseOutputBitFile(output_file);
    CloseInputBitFile(infile);
    
    return 0;
}




void renormalize(BIT_FILE *outfile){
    if (carry==true){
        OutputBit(outfile, 1);
        compressedsize++;
       // cout<<"carry reached"<<endl;
        carry=false;
    }
    
    while(A<0x8000){
        A=A<<1;
       // Check MSB value
        if((C&(0x8000))==0){
            OutputBit(outfile, 0);
            compressedsize++;
           // cout<<0;
        }else{
            OutputBit(outfile, 1);
            compressedsize++;
         //   cout<<1;
        }
        C=C<<1;
    }
}


// This function is from online source of C++ IO routine
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


void help(){
    cout<<"Usage: ./QM [filename]"<<endl;
}
