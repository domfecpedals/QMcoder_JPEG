//
//  DCT.h
//  JPEG
//
//  Created by Yuan Liu on 2/16/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#ifndef __JPEG__DCT__
#define __JPEG__DCT__

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>



    

double quantizer(int i, int j, double factor);
double calculateCoeff(char **data, int i, int j, int blki, int blkj, int blocksize);
double **DCTQuantized(char **data, int size, int blocksize, int factor);

#endif /* defined(__JPEG__DCT__) */
