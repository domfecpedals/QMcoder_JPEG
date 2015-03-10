//
//  Lloyd.h
//  LloydMax
//
//  Created by Yuan Liu on 2/13/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#ifndef __LloydMax__Lloyd__
#define __LloydMax__Lloyd__

#include <stdio.h>

void trainQuantizer(unsigned char *data, int bitDepth, double dist);
unsigned char* testQuantizer(unsigned char *data);
double* getHist(unsigned char* data);
void updateThreshold(double *qval, double *interval, int levels);
void updateQval(double *qval, double *interval, int levels, double *hist);
double quantize(unsigned char *data, int levels, double *interval, double *qval);
#endif /* defined(__LloydMax__Lloyd__) */
