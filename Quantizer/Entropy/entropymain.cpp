//
//  main.cpp
//  Entropy
//
//  Created by Yuan Liu on 2/28/15.
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

using namespace std;

void getInfo(char *filename);
void relative_freq(char *input,double *frequency);


int main(int argc, char * argv[]) {

    char *filename;
    if(argv[1]!=NULL){
        filename=argv[1];
    }else{
        cout<<"Usage: ./entropy [filename]";
        exit(1);
    }
    
    
    //char *filename="f16.quantized.3";
    getInfo(filename);

    
    
    return 0;
}


void getInfo(char *filename){
    double freq[256]={};
    //double sum=0;
    
    relative_freq(filename, freq);
    double entropy=0;
    
    cout<<"Current file name is <"<<filename<<">"<<endl;
    for(int i=0;i<256;i++){
        
        if(freq[i]!=0){
            entropy+=-freq[i]*log2(freq[i]);
         //   cout<<"Frequency of symbol <"<<i<<"> is "<<freq[i]<<endl;
        }
    }
    
    
    cout<<"Entropy of file <"<<filename<<"> is: "<<entropy<<endl;
    
    
    
    //cout<< " sum is "<<sum<<endl;
    
    
}

void relative_freq(char *input,double *frequency){
    
    ifstream infile(input, ios_base::in | ios_base::binary);
    //unsigned char sym;
    unsigned char sym;
    int total;
    sym = infile.get();
    frequency[sym]++;
    total++;
    while(infile.good())
    {
        frequency[sym]++;
        total++;
        sym=infile.get();
    }
    
    for (int i=0;i<256;i++){
        frequency[i]=frequency[i]/total;
        
    }
    
    infile.close();
}