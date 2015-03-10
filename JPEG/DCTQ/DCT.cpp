
#include "DCT.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159

using namespace std;


double Q[8][8] =
{
    {16,11,10,16,24,40,51,61},
    {12,12,14,19,26,58,60,55},
    {14,13,16,24,40,57,69,56},
    {14,17,22,29,51,87,80,62},
    {18,22,37,56,68,109,103,77},
    {24,35,55,64,81,104,113,92},
    {49,64,78,87,103,121,120,101},
    {72,92,95,98,112,100,103,99}
};


double quantizer(int i, int j, double factor){
    
    
    double scale;
    if (factor<=50){
        scale=double(50/factor);
    }else{
     //   cout<< "larger than 50"<<endl;
        scale=double((100-factor)/50);
    }
    
    
    double quantizer=double(scale*Q[i][j]);
    
  //  cout<<quantizer<<" quantizer ";
    return quantizer;
    
}

double **DCTQuantized(char **data, int size, int blocksize, int factor){
    double **DCT=new double*[size];
    for(int i=0;i<size;i++){
        DCT[i]=new double[size];
    }
    
    //int blockCount=size/blocksize;
    double difference=0;
    double MSE=0;
    
    // loop for blocks
    for(int blki=0;blki<size;){
        for(int blkj=0;blkj<size;){
            cout<<"Block "<<blki/8+1<<", "<<blkj/8+1<<endl;
            
            
            for(int i=0;i<blocksize;i++){
                for (int j=0;j<blocksize;j++){
                    double q=quantizer(i,j,factor);
                    
                    int original=round(calculateCoeff(data, i, j, blki, blkj, blocksize));
                    
                    cout<<" "<<original;
                    
                    DCT[blki+i][blkj+j]=round(calculateCoeff(data, i, j, blki, blkj, blocksize)/q);
                    
                    
                    difference=pow((original-DCT[blki+i][blkj+j]),2);
                    MSE+=difference;
                    
                    
                }
                cout<<endl;
            }
            blkj+=8;
        }
        blki+=8;
    }
    
    MSE=MSE/(size*size);

    
    double psnr = 10*log10(pow(255,2)/MSE);
    cout<<"The current psnr: "<<psnr<<endl;
    
    
    return DCT;
    
}


double calculateCoeff(char **data, int i, int j, int blki, int blkj, int blocksize){
    double coeff=0;
    double ci=1, cj=1;
    if(i==0){ci=1/sqrt(2);}
    if(j==0){cj=1/sqrt(2);}
    for (int x=0;x<blocksize;x++){
        for (int y=0;y<blocksize;y++){
            coeff+=data[blki+x][blkj+y]*cos((2*x+1)*i*PI/(2*blocksize))*cos((2*y+1)*j*PI/(2*blocksize));
        }
    }
    coeff*=(ci*cj/sqrt(2*blocksize));
    return coeff;
}
