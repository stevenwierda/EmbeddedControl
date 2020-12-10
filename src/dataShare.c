/*
 * dataShare.c
 *
 *  Created on: 10 dec. 2020
 *      Author: Steven
 */
#include "dataShare.h"

long unsigned int timerInteruptTime = 250;

void setInteruptTime(long unsigned int value){
    timerInteruptTime = value;
}

long unsigned int getInteruptTime(void){
    return(timerInteruptTime);
}
