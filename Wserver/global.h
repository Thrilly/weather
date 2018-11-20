//  global.h
//  softwar
//
//  Created by Ordine Team on 23/06/2018.
//  Copyright © 2018 Ordine Team. All rights reserved.
//

#include <czmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


typedef struct s_data_weather
{
    int                     dep;
    char*                   dep_name;
    char*                   weather;
    int                     temp;
    struct s_data_weather*  next;
} DepDataWeather;


// Globals functions
int             check_params(int argc, char *argv[]);
void            printfc(char* str, char* color);
char            *substr(char *src,int pos,int len);

// DDW functions
DepDataWeather	*add_ddw(DepDataWeather *list, int dep, char* dep_name, char* weather, int temp);
// DepDataWeather	*edit_ddw(DepDataWeather *list, int dep, char* dep_name, char* weather, int temp);
DepDataWeather  *search_ddw(DepDataWeather *list, int dep);
DepDataWeather  *delete_ddw(DepDataWeather *list, int dep);
int              count_ddw(DepDataWeather *list);
