//
//  readTable.h
//  QMcoder
//
//  Created by Yuan Liu on 2/15/15.
//  Copyright (c) 2015 Yuan Liu. All rights reserved.
//

#ifndef __QMcoder__readTable__
#define __QMcoder__readTable__

#include <stdio.h>

typedef struct tableRow{
    int state;
    unsigned int Qe;
    int increaseState;
    int decreaseState;
}TABLEROW;

void initial(TABLEROW *qt);
void readTable(char *filename, TABLEROW *table);

#endif /* defined(__QMcoder__readTable__) */
