//
//  main.cpp
//  JPEG
//
//  Created by Yuan Liu on 2/16/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "DCT.h"


using namespace std;

void help();

int main(int argc, char * argv[]) {

    char *filename="lena.raw";
    FILE *file;
    int Size=16;
    int blocksize=8;
    double qfactor=50;
    
    if(argv[1]==NULL){
        help();
        return 1;
    }
    
    if(argv[1]!=NULL){
        filename=argv[1];
    }else{
        help();
        return 1;
    }
    
    if(argv[2]!=NULL){
        qfactor= atof(argv[2]);
    }else{
        help();
        return 1;
    }
    
    
    // image data array
    unsigned char Imagedata[Size][Size];
    
    // read image "ride.raw" into image data matrix
    if (!(file=fopen(filename,"rb")))
    {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size, file);
    fclose(file);

    
    // Substract by 128, use int matrix to store the image, since negative value present here
    char **signedImage=new char*[Size];
    for(int i=0;i<Size;i++){
        signedImage[i]=new char[Size];
    }
    
    for(int i=0;i<Size;i++){
        for (int j=0;j<Size;j++){
            
                signedImage[i][j]=Imagedata[i][j]-128;
               // cout<<(int)signedImage[i][j]<<" ";
         
        }
      //  cout<<endl;
    }
    
    
    // Compute DCT matrix
    double **DCTcoefficients=new double*[Size];
    for(int i=0;i<Size;i++){
        DCTcoefficients[i]=new double[Size];
    }
    
    DCTcoefficients=DCTQuantized(signedImage,Size, blocksize, qfactor);
    for(int i=0;i<Size;i++){
        for (int j=0;j<Size;j++){
            cout<<DCTcoefficients[i][j]<<" ";
        }
        cout<<endl;
    }
    

    return 0;
}


void help(){
    cout<<"Usage: ./DCTQ [filename] [quantize factor]    NOTICE: image size 16X16, quantize factor from 0 to 100"<<endl;
    
}



