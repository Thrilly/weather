//  check_params.c
//  softwar
//
//  Created by Brice Fouepe on 23/06/2018.
//  Copyright © 2018 Brice Fouepe. All rights reserved.
//

#include <czmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


void printfc(char* str, char* color)
{
    if (strcmp(color,"green") == 0) {
        printf("\x1B[32m%s", str);
    } else if(strcmp(color,"red") == 0){
        printf("\x1B[31m%s", str);
    } else if(strcmp(color,"blue") == 0){
        printf("\x1B[36m%s", str);
    } else if(strcmp(color,"yellow") == 0){
        printf("\x1B[33m%s", str);
    }
    printf("\x1B[0m");
}

char *substr(char *src, int pos, int len) {
    char *dest=NULL;
    if (len>0) {
        dest = calloc(len+1, 1);
        if(NULL != dest) {
            strncat(dest,src+pos,len);
        }
    }
    return dest;
}
