//
//  main.cpp
//  blocking
//
//  Created by Yuan Liu on 2/18/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <string.h>


#define Size 256
using namespace std;

unsigned char* readIMG(char * filename);
void outputIMG(unsigned char *data, char* filename);

int main(int argc, char * argv[]) {
    

    // Read in all 3 training images
    unsigned char *data=new unsigned char[256*256*3];
    unsigned char *data1=readIMG("chem.256");
    unsigned char *data2=readIMG("moon.256");
    unsigned char *data3=readIMG("house.256");
    copy(data1, data1+256*256,data);
    copy(data2, data2+256*256, data+256*256);
    copy(data3, data3+256*256,data+256*256*2);
    
    
    //int blocksize=2;
    
    int rows=256*3;
    int cols=256;
    int blockheight;
    int blockwidth;
    
    
    if(argv[1]!=NULL){
        blockwidth=atof(argv[1]);
        blockheight=atof(argv[1]);
        
    }else{
        cout<<"Input files are hard coded"<<endl;
        cout<<"Usage ./blocking [block witdh(2x2 enetr 2 here)] [output filename]"<<endl;
        exit(1);
    }
    
    
    int blocks_per_col = rows/blockheight;
    int blocks_per_row = cols/blockwidth;
    int num_cols = blocks_per_row*blockwidth;
    int num_rows = blocks_per_col*blockheight;
    int num_blocks = blocks_per_col*blocks_per_row;
    int num_pixels = rows*cols;
    int vector_length = blockheight*blockwidth;
    
    
    FILE *outputfile;
    char *outputname="trainingVector";
    
    if(argv[2]!=NULL){
        outputname=argv[2];
    }else{
        cout<<"Using default output filename trainingVector"<<endl;
    }
    
    
    if((outputfile = fopen(outputname,"w")) == NULL){
        fprintf(stderr,"%s: %s\n",outputname,"NOTFOUND");
        exit(9);
    }
    
    unsigned char **blocked_image=new unsigned char*[vector_length];

    
    /* create the block vectors and write them to the output file */
    for(int i=0; i<num_blocks; i++) {
        blocked_image[i]=new unsigned char[vector_length];
        
        for(int j=0; j<vector_length; j++) {
            int k = (i%blocks_per_row)*blockwidth + (j%blockwidth) +
            ( (i/blocks_per_row)*blockheight + (j/blockwidth) ) * cols;
            blocked_image[i][j] = data[k];
        }
        
        if (fwrite(blocked_image[i], sizeof(unsigned char), vector_length, outputfile)
            != vector_length) {
            //fprintf(stderr,"%s: %s: %s\n",programname,outputname,NOWRITE);
            exit(13);
        }
    }
    
    
    fclose(outputfile);
    
    
    return 0;
}


unsigned char* readIMG(char * filename){
    FILE *file;
    unsigned char *Imagedata=new unsigned char[256*256];
    if (!(file=fopen(filename,"rb")))
    {
        cout << "Cannot open file"<<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), 256*256, file);
    
    fclose(file);
    return Imagedata;
}
