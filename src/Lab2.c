/**
 * @file Lab2.c
 * @author Robledo, Valentín
 * @brief Auxiliary functions that implement the solution of exercises 1 and 2 of laboratory 2, Operating Systems I.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Lab2.h"

/**
* @brief Gets all the words from a given file.
*
* Generates a dynamic two-dimensional array with all the words contained in the specified file.
* Minimizes the memory used for storing these words.
*
* @param file_name file from which the words are to be obtained.
* @param n pointer where the number of words obtained will be stored.
* @return char** memory address of the two-dimensional array where the words obtained are located.
*/
char** getWords(char* file_name, u_int32_t* n)
{
    u_int32_t w_count = 0;
    u_int32_t c_count = 0;

    char last = ' ';
    char c;

  	FILE* file;

	char** words = malloc(sizeof(char*));
	words[w_count] = malloc(sizeof(char));

	file = fopen(file_name, "r");
    
  	if(file == NULL) 
		exit(EXIT_FAILURE);

    while ((c = (char)fgetc(file)) != EOF)
    {
        if(c == ' ' && last != ' ')
        {
            words[w_count][c_count] = '\0';

            w_count++;
            c_count = 0;

            words = realloc(words, (w_count + 1) * sizeof(char*));
            words[w_count] = malloc(sizeof(char));
        } 
        else
        {
            if(c != '(' && c != ')')
            {
                words[w_count][c_count] = c;
                c_count++;
                words[w_count] = realloc(words[w_count], (c_count + 1) * sizeof(char));
            }
        }

        last = c;
    }

    words[w_count][c_count] = '\0';

    *n = w_count;

  	fclose(file);

    return words;
}

/**
* @brief Frees the memory space where the words are stored.
*
* @param words memory address where the two-dimensional array of words is located.
* @param n number of words stored in the array.
*/
void freeWords(char** words, u_int32_t n)
{
    for(int i = 0; i < n; i++)
    {
        free(words[i]);
    }

    free(words);
}

/**
* @brief Prints the words in an array in uppercase to the console (does not alter the array of words).
*
* @param words memory address where the two-dimensional array of words is located.
* @param n number of words stored in the array.
*/
void upperCasePrintWords(char** words, u_int32_t n) 
{
    printf("- UPPER CASE WORDS (/proc/version):\n");
    
    for(int i = 0; i < n; i++)
    {
        printf("    ");

        for(int j = 0; words[i][j] != '\0'; j++)
		{ 
			printf("%c", toupper(words[i][j]));
        }

        printf("\n");
    }

    printf("\n");
}

/**
* @brief Converts all words in the given two-dimensional array to uppercase.
*
* @param words memory address where the two-dimensional array of words is located.
* @param n number of words stored in the array.
*/
void toUpperCaseWords(char** words, u_int32_t n)
{
    for(u_int32_t i = 0; i < n; i++)
    {
        for(int j = 0; words[i][j] != '\0'; j++)
		{
        	words[i][j] = toupper(words[i][j]);
        }
    }
}

/**
* @brief Prints information about memory to the console.
*
*/
void printMemoryInfo(void)
{
    MEM_INFO memInfo;

    getMemInfo(&memInfo);

	printf("- MEM INFO (/proc/meminfo):\n");
    printf("	Memoria Total      : %*lu [MB]\n", 7, memInfo.MemTotal     / 1024);
    printf("	Memoria Libre      : %*lu [MB]\n", 7, memInfo.MemFree 	   / 1024);
    printf("	Memoria Disponible : %*lu [MB]\n", 7, memInfo.MemAvailable / 1024);
    printf("	Swap Total         : %*lu [MB]\n", 7, memInfo.SwapTotal    / 1024);
    printf("	Swap Libre         : %*lu [MB]\n\n", 7, memInfo.SwapFree   / 1024);
}

/**
* @brief Prints information about the CPU to the console.
*
*/
void printCpuInfo(void)
{
    CPU_INFO cpuInfo;

    getCpuInfo(&cpuInfo);

	printf("- CPU INFO (/proc/cpuinfo):\n");
    printf("	Modelo             : %s\n", cpuInfo.ModelName);
    printf("	Nucleos            : %d\n", cpuInfo.Cores);
    printf("	Hilos              : %d\n\n", cpuInfo.Threads);
}

/**
* @brief Obtains information about the memory.
*
* Reads and processes the information stored in the file "/proc/meminfo"
* to later store it in the pointer to the structure given as a parameter.
*
* @param memInfo pointer to the structure where the obtained information is to be stored.
*/
void getMemInfo(MEM_INFO* memInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/meminfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, file)) != -1)
	{
		char* token = strtok(line, ":");
		
		if (strncmp(token, "MemTotal", 8) == 0) {
			token = strtok(NULL, ":");
			memInfo->MemTotal = atol(strtok(token, " "));
		}

		if (strncmp(token, "MemFree", 7) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemFree = atol(strtok(token, " "));
		}

		if (strncmp(token, "MemAvailable", 12) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemAvailable = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapTotal", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapTotal = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapFree", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapFree = atol(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}

/**
* @brief Obtains information about the CPU.
*
* Reads and processes the information stored in the file "/proc/cpuinfo"
* to later store it in the pointer to the structure given as a parameter.
*
* @param cpuInfo pointer to the structure where the obtained information is to be stored.
*/
void getCpuInfo(CPU_INFO* cpuInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/cpuinfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, file)) != -1)
	{
		char* token = strtok(line, ":");
		
		if (strncmp(token, "model name", 10) == 0) {	
		/* This block of code is responsible for removing the blank spaces at the beginning
		and end of the string containing the CPU model information */

  			const char *end;
  			token = strtok(NULL, ":"); 

    		while(isspace((unsigned char)*token)) token++;

	 		end = token + strlen(token) - 1;
  			while(end > token && isspace((unsigned char)*end)) end--;
  			end++;

  			memcpy(cpuInfo->ModelName, token, (end - token));
  			cpuInfo->ModelName[(end - token)] = 0;
		}

		if (strncmp(token, "cpu cores", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Cores = atoi(strtok(token, " "));
		}

		if (strncmp(token, "siblings", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Threads = atoi(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}
