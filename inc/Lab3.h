/**
 * @file Lab2.3
 * @author Robledo, Valentín
 * @brief Header de Lab3.c.
 * @version 1.0
 * @date September de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LAB3_H__
#define __LAB3_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "cJSON.h"
#include "Lab2.h"

char *cJSONFormatMEM(MEM_INFO memory);
char *cJSONFormatCPU(CPU_INFO cpu);
char *cJSONFormatWords(char** words, u_int32_t n);

void printWords(char** words,u_int32_t n);
void pluginDynamic();

#endif //__LAB3_H__