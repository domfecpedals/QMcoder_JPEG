//
//  Lloyd.cpp
//  LloydMax
//
//  Created by Yuan Liu on 2/13/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#include "Lloyd.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>


// Global array to store quantizer parameters
double *threshold;
double *assignedval;
int quantizerlvl;



void trainQuantizer(unsigned char *data, int bitDepth, double dist){
    
    int levels=pow(2,bitDepth);
    
    
    double oldMSE, newMSE;
    double distortion=1;
    double psnr=0;
    
    //store histogram info
    double *freq;
    freq=getHist(data);
    
    /////////////////check array size!!!!!!
    
    double *qval=new double[levels];
    double *interval=new double[levels+1];
    
    interval[0]=0;
    interval[levels]=255;
    
    // initial quantizer levels
    double step=255/(levels-1);
    
    for(int i=0;i<levels;i++){
        qval[i]=(i)*step;
        //std::cout<<qval[i]<<std::endl;
    }
    
    
    
    
    
    /////////////////////
    // Start iteration
    int loop_tracker=1;
    updateThreshold(qval, interval, levels);
    updateQval(qval, interval, levels, freq);
    newMSE=quantize(data, levels, interval, qval);
    psnr = 10*log10(pow(255,2)/newMSE);
    std::cout<<"Training iteration is: "<<loop_tracker<<std::endl;
    std::cout<<"The current psnr: "<<psnr<<std::endl;
    // initial old MSE, that's why separatedly run iteration #1
    //oldMSE=newMSE;
    
    while(distortion>dist){
        loop_tracker++;
        updateThreshold(qval, interval, levels);
        updateQval(qval, interval, levels, freq);
        oldMSE=newMSE;
        newMSE=quantize(data, levels, interval, qval);
        psnr = 10*log10(pow(255,2)/newMSE);
        std::cout<<"Training iteration is: "<<loop_tracker<<std::endl;
        std::cout<<"The current psnr: "<<psnr<<std::endl;
        distortion= abs(oldMSE-newMSE)/newMSE;
        

        

    
    }
    
    threshold=new double[levels+1];
    assignedval=new double[levels];
    threshold[levels]=255;
        for(int i=0;i<levels;i++){
            threshold[i]=interval[i];
            assignedval[i]=qval[i];
            //std::cout<<assignedval[i]<<std::endl;
        }
    quantizerlvl=*new int;
    quantizerlvl=levels;
}


unsigned char* testQuantizer(unsigned char *data){
    

    double MSE=0;
    double difference=0;
    
    unsigned char *quantizedImg=new unsigned char[256*256];
    
    for (int i=0;i<256*256;i++){
        unsigned char orginal=data[i];
        
        // loop over all levels
        for (int j=0;j<quantizerlvl;j++){
            
            if (orginal>=threshold[j]&&orginal<threshold[j+1]){
                quantizedImg[i]=assignedval[j];
            }
        }
        difference=pow((orginal-quantizedImg[i]),2);
        // std::cout<<(int)orginal<<" "<<quantized<<std::endl;;
        MSE+=difference;
        
    }
    
    MSE=MSE/(256*256);
    
    
   
   
    
    float PSNR = 10*log10(pow(255,2)/MSE);
    std::cout << "PSNR is: " << PSNR << std::endl;
    
    return quantizedImg;
    
    
}



double* getHist(unsigned char* data){
    double *fq=new double[256];

    unsigned char val;
    for (int i=0;i<256*256*3;i++){
        val=data[i];
        fq[val]++;
    }
    long int sum=0;
    for (int i=0;i<256;i++){
        sum+=fq[i];
    }
    
    return fq;

}

void updateThreshold(double *qval, double *interval, int levels){
    // interval[0]=0;interval[max]=255;
    for (int i=1;i<levels;i++){
        interval[i]=(qval[i]+qval[i-1])/2;
        //std::cout<<interval[i]<<std::endl;
    }
   // std::cout<<"last thresh "<<interval[levels]<<std::endl;
}

void updateQval(double *qval, double *interval, int levels, double *hist){
    double lbound, hbound;
    int sum, probSum;
    
    //std::cout<<"first "<<interval[0]<<std::endl;
    for (int i=0;i<levels;i++){
        
        lbound=ceilf(interval[i]);
        hbound=floorf(interval[i+1]);
        
      //  std::cout<<lbound<<" "<<hbound<<std::endl;
        
        sum=0;
        probSum=0;
        
        for (int j=lbound;j<=hbound;j++){
            sum+=j*hist[j];
            probSum+=hist[j];
        }
        
        if(probSum!=0){
            qval[i]=sum/probSum;
        }
        
    }
}


// Do quantization and return the MSE
double quantize(unsigned char *data, int levels, double *interval, double *qval){
    double quantized=0;
    double difference;
    double MSE=0;
    // apply quantizer to each pixel
    for (int i=0;i<256*256*3;i++){
        unsigned char orginal=data[i];
        
        // loop over all levels
        for (int j=0;j<levels;j++){
            
            if (orginal>=interval[j]&&orginal<interval[j+1]){
                quantized=qval[j];
            }
        }
        difference=pow((orginal-quantized),2);
       // std::cout<<(int)orginal<<" "<<quantized<<std::endl;;
        MSE+=difference;
        
    }
    
    MSE=MSE/(256*256*3);
    
    return MSE;
}