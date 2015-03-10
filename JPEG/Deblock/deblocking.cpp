//
//  deblocking.cpp
//  JPEGdeblocking
//
//  Created by Yuan Liu on 2/19/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include "deblocking.h"
#include <math.h>


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

int b[9] = {1,1,2,2,4,2,2,1,1};


void deblockH(double ***data, int size, int blocksize, int channel){
    double *Horizon=new double[blocksize+2];
    
    for (int i=0;i<size;i++){
        for ( int j=3;j+blocksize<size;j+=blocksize){
            
            int idx=0;
            for (int k=j;k<(j+blocksize+2);k++){
                Horizon[idx]=data[i][k][channel];
                idx++;
            }
            
            int QQ=Q[i%8][0];
            
            bool isSmooth=isSmoothMode(Horizon,blocksize);
            
            double *result;
            
            if(isSmooth){
                result=smoothMode(Horizon, QQ, blocksize);
            }else{
                result=defaultMode(Horizon, QQ, blocksize);
            }
            
            int idx2=0;
            
            
            for (int k=j;k<(j+blocksize+2);k++){
                data[i][k][channel]=result[idx2];
                idx2++;
            }
            
        }
        
        
    }
    
    
}

void deblockV(double ***data, int size, int blocksize, int channel){
    
    double *Vertical=new double[blocksize+2];
    
    for (int i=0;i<size;i++){
        for (int j=3;j+blocksize<size;j+=blocksize){
            int idx=0;
            for(int k=j;k<(j+blocksize+2);k++){
                Vertical[idx]=data[k][i][channel];
                idx++;
            }
            
            // Vertical Q;
            int QQ=Q[0][i%8];
            
            bool isSmooth=isSmoothMode(Vertical,blocksize);
            
            double *result;
            if(isSmooth){
                result=smoothMode(Vertical, QQ, blocksize);
            }else{
                result=defaultMode(Vertical, QQ, blocksize);
            }
            
            int idx2=0;
            for(int k=j;k<(j+blocksize+2);k++){
                data[k][i][channel]=Vertical[idx2];
                idx2++;
            }
        }
    }
    
    
    
}

// true is smooth mode
// fault is default mode
bool isSmoothMode(double *dimensionData, int blocksize){
    int threshold1=2, threshold2=6;
    int counter=0;
    for (int i=0;i<=blocksize;i++){
        if(fabs(dimensionData[i]-dimensionData[i+1])<=threshold1){
            counter++;
        }
    }
    
    if(counter>threshold2){
        return true;
    }
    
    return false;
}

double *smoothMode(double *Data, int Q, int blocksize){
    
    int max=Data[1];
    int min=Data[1];
    
    for (int i=1;i<=blocksize;i++){
        if(Data[i]>max){
            max=Data[i];
        }
        if(Data[i]<min){
            min=Data[i];
        }
    }
    
    
    double Ps;
    double Pe;
    
    if(fabs(Data[1]=Data[0])<Q){
        Ps=Data[0];
    }else{
        Ps=Data[1];
    }
    if(fabs(Data[blocksize+1]-Data[blocksize])<Q){
        Pe=Data[blocksize+1];
    }
    else{
        Pe=Data[blocksize];
    }
    
    
    
    if((max-min)>=2*Q){
        return Data;
    }
    double *newVal=new double[blocksize+2];
    
    for (int i=1;i<=blocksize;i++){
        double t=0;
        for (int j=0;j<=blocksize;j++){
            double pp;
            if(j+i-4<1){
                pp=Ps;
            }else if(j+i-4>blocksize){
                pp=Pe;
            }else{
                pp=Data[i+j-4];
            }
            t+=b[j]*pp;
            
        }
        newVal[i]=t/16;
    }
    
    newVal[0]=Data[0];
    newVal[blocksize+1]=Data[blocksize+1];
    
    
    
    return newVal;
}


double *defaultMode(double *Data, int Q, int blocksize){
    //c1 c2 c3 are approximated to 2, 5, and 8,
    
    int c1=2, c2=5, c3=8;
    double *a3k=new double[3];
    // 0<=k<=2, k=0, 1, 2
    
    for (int k=0;k<3;k++){
        a3k[k]=(c1*Data[2*k+1]-c2*Data[2*2+2]+c2*Data[2*k+3]-c1*Data[2*k+4])/c3;
    }
    
    if(fabs(a3k[1])<Q){
        return Data;
    }
    
    int sign=0;
    
    if(a3k[1]>0){
        sign=1;
    }else if(a3k[1]<0){
        sign=-1;
    }
    
    double a31=sign*minA(a3k);
    
    double d=clipInDefault(c2*(a31-a3k[1])/c3, 0, (Data[4]-Data[5])/2);
    
    
    Data[4]=Data[4]-d;
    Data[5]=Data[5]-d;
    
    return Data;
}

double clipInDefault(double x, double p, double q){
    if(x<=p){
        return p;
    }else if(x>=q){
        return q;
    }else{
        return x;
    }
}

double minA(double *a3k){
    double max=a3k[0];
    for (int i=1;i<3;i++){
        if (a3k[i]>max){
            max=a3k[i];
        }
    }
    return max;
}