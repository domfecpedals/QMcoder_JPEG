//
//  main.cpp
//  LloydMax
//
//  Created by Yuan Liu on 2/13/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Lloyd.h"
#include <fstream>


#define Size 256


using namespace std;

unsigned char* readIMG(char * filename);
void outputIMG(unsigned char *data, char* filename);



int main(int argc, char * argv[]) {
    
    
    int quantizerlvl;
    
    if(argv[1]!=NULL){
        quantizerlvl=atof(argv[1]);
    }else{
        cout<<"Usage ./Lloyd [quantizerl level]"<<endl;
        exit(1);
        
    }
    

    unsigned char *data1=readIMG("chem.256");
    unsigned char *data2=readIMG("moon.256");
    unsigned char *data3=readIMG("house.256");
    
    
    
    unsigned char *data=new unsigned char[256*256*3];
    copy(data1, data1+256*256,data);
    copy(data2, data2+256*256, data+256*256);
    copy(data3,data3+256*256,data+256*256*2);

    
    trainQuantizer(data, quantizerlvl, 0.001);
    
    unsigned char *data4=readIMG("f16.256");
    unsigned char *data5=readIMG("elaine.256");
    unsigned char *data6=readIMG("couple.256");

    char *output;
    cout<<"Quantizing chem.256"<<endl;
    unsigned char* outputData=testQuantizer(data1);
    output=new char[64];
    strcat(output, "chem.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);
    
    cout<<"Quantizing moon.256"<<endl;
    outputData=testQuantizer(data2);
    output=new char[64];
    strcat(output, "moon.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);
    
    cout<<"Quantizing house.256"<<endl;
    outputData=testQuantizer(data3);
    output=new char[64];
    strcat(output, "house.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);
    
    cout<<"Quantizing f16.256"<<endl;
    outputData=testQuantizer(data4);
    output=new char[64];
    strcat(output, "f16.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);

    cout<<"Quantizing elaine.256"<<endl;
    outputData=testQuantizer(data5);
    output=new char[64];
    strcat(output, "elaine.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);
    
    
    cout<<"Quantizing couple.256"<<endl;
    outputData=testQuantizer(data6);
    output=new char[64];
    strcat(output, "couple.quantized.");
    strcat(output, argv[1]);
    outputIMG(outputData, output);
    
    return 0;
}


void outputIMG(unsigned char *data, char* filename){
    FILE* file = fopen( filename, "wb" );
    fwrite(data, 1, 256*256, file );
    fclose(file);
}

unsigned char* readIMG(char * filename){
    FILE *file;
    
    // int BytesPerPixel=1;
    
    // image data array
    unsigned char *Imagedata=new unsigned char[256*256];
    
    // read image "ride.raw" into image data matrix
    if (!(file=fopen(filename,"rb")))
    {
        cout << "Cannot open file"<<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), 256*256, file);
    
    fclose(file);
    return Imagedata;
}


