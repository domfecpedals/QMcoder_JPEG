//
//  deblocking.h
//  JPEGdeblocking
//
//  Created by Yuan Liu on 2/19/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#ifndef __JPEGdeblocking__deblocking__
#define __JPEGdeblocking__deblocking__

#include <stdio.h>


void deblockH(double ***data, int size, int blocksize, int channel);
void deblockV(double ***data, int size, int blocksize, int channel);
bool isSmoothMode(double *dimensionData, int blocksize);
double *smoothMode(double *dimensionData, int Q, int blocksize);
double *defaultMode(double *dimensionData, int Q, int blocksize);
double clipInDefault(double x, double p, double q);
double minA(double *a3k);
#endif /* defined(__JPEGdeblocking__deblocking__) */
