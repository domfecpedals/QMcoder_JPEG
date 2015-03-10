//
//  main.cpp
//  JPEGdeblocking
//
//  Created by Yuan Liu on 2/16/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "deblocking.h"
#include "bitio.h"
#include <math.h>


using namespace std;

void help();
void writeRawImage(double ***data, int size, int channels, char *outputfile);

int main(int argc, char * argv[]) {
    
    int size=256;
    bool color=false;
    int pbytes=1;
    char *filename="pepper5.raw";
    
    
    
    if(argv[1]==NULL){
        help();
        return 1;
    }
    
    if(argv[1]!=NULL&&strcmp(argv[1],"color")==0){
        color=true;
    }else if(argv[1]!=NULL&&strcmp(argv[1],"bw")==0){
        color=false;
    }else{
        help();
        return 1;
    }
    
    if(argv[2]!=NULL){
        filename=argv[2];
    }else{
        help();
        return 1;
    }
    


    if(color){
        pbytes=3;
    }
   
    
    
    
    
    FILE *file;
    // image data array. Assigning memory
    unsigned char* imgArray = new unsigned char[size*size*pbytes];
    
    // read image "ride.raw" into image data matrix
    if (!(file = fopen(filename, "rb"))) {
        cout << "Cannot open file: " << filename << endl;
        exit(1);
    }
    fread(imgArray, sizeof(unsigned char), size * size * pbytes, file);
    fclose (file);
    

    double***Imagedata;
    Imagedata = new double**[size];
    for (int i = 0; i < size; ++i) {
        Imagedata[i] = new double*[size];
        for (int j = 0; j < size; ++j)
            Imagedata[i][j] = new double[pbytes];
    }
    
    //Convert 1-d array element to 3-D
    int no = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            for(int k = 0; k < pbytes; k++)
                Imagedata[i][j][k] = imgArray[no++];
    

    
    
    //read image
    
    
    if(!color){
        deblockH(Imagedata, 256, 8, 0);
        deblockV(Imagedata, 256, 8, 0);
    }else{
        
        // Apply one RGB separately
        deblockH(Imagedata, 256, 8, 0);
        deblockV(Imagedata, 256, 8, 0);
        deblockH(Imagedata, 256, 8, 1);
        deblockV(Imagedata, 256, 8, 1);
        deblockH(Imagedata, 256, 8, 2);
        deblockV(Imagedata, 256, 8, 2);
    }
    

    char *output=new char[64];
    
    strcat(output, filename);
    strcat(output, ".deblocked");
    
    writeRawImage(Imagedata, 256, pbytes, output);
    
    
    //write image
    
    
    
    return 0;
}


void writeRawImage(double ***data, int size, int channels, char *outputfile){
    
    BIT_FILE *outfile=OpenOutputBitFile(outputfile);
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            for(int k = 0; k < channels; k++)
                OutputBits(outfile, round(data[i][j][k]), 8);
    
    CloseOutputBitFile(outfile);
}

void help(){
    cout<<"Usage: ./deblocking [color/bw] [input filename]"<<endl;
}


