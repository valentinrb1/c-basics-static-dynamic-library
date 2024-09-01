/**
 * @file Lab3.h
 * @author Robledo, Valentín
 * @brief Functions that solve practical work 3.
 * @version 1.0
 * @date September de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Lab3.h"

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        if(!strcmp(argv[1], "-a"))
        {
            printCpuInfo();
            printMemoryInfo();
        }
        else if(!strcmp(argv[1], "-s"))
        { 
            u_int32_t n;
            char** words = getWords("/proc/version", &n);

            upperCasePrintWords(words, n);

            freeWords(words, n);
        }
        else if(!strcmp(argv[1], "-d"))
        {
            pluginDynamic();
        }
        else
        {
            printf("Invalid Argument \n");
        }
    }
    else if(argc == 3)
    {
        if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-j"))
        {
            MEM_INFO memory;           
            getMemInfo(&memory);
            printf("%s \n", cJSONFormatMEM(memory));
               
            CPU_INFO cpu;
            getCpuInfo(&cpu);
            printf("%s \n", cJSONFormatCPU(cpu));
        }
        else if(!strcmp(argv[1], "-s") && !strcmp(argv[2], "-j"))
        {
            u_int32_t n;
            char** words = getWords("/proc/version", &n);

            toUpperCaseWords(words, n);
               
            printf("%s \n", cJSONFormatWords(words, n));

            freeWords(words, n);
        }
        else
        {
            printf("Invalid Argument \n");
        }
    }
    else
    {
        printf("Invalid Argument \n");
    }

    return 0;
}

char *cJSONFormatMEM(MEM_INFO memory)
{
    char *printMemInfoJSON = NULL;
    cJSON *MemTotal        = NULL;   
    cJSON *MemFree         = NULL;  
    cJSON *MemAvailable    = NULL;
    cJSON *SwapTotal       = NULL;
    cJSON *SwapFree        = NULL;

    cJSON *memInfoJSON = cJSON_CreateObject(); 
    if (!memInfoJSON) return NULL;
    
    MemTotal = cJSON_CreateNumber(memory.MemTotal/1024);
    if(!MemTotal){ cJSON_Delete(memInfoJSON); return NULL;}
    cJSON_AddItemToObject(memInfoJSON, "MemTotal", MemTotal);
    
    MemFree = cJSON_CreateNumber(memory.MemFree/1024);
    if(!MemFree){cJSON_Delete(memInfoJSON); return NULL;}
    cJSON_AddItemToObject(memInfoJSON, "MemFree", MemFree);

    MemAvailable = cJSON_CreateNumber(memory.MemAvailable/1024);
    if(!MemAvailable){cJSON_Delete(memInfoJSON); return NULL;}
    cJSON_AddItemToObject(memInfoJSON, "MemAvailable", MemAvailable);

    SwapTotal = cJSON_CreateNumber(memory.SwapTotal/1024);
    if(!SwapTotal){cJSON_Delete(memInfoJSON); return NULL;}
    cJSON_AddItemToObject(memInfoJSON, "SwapTotal", SwapTotal);

    SwapFree = cJSON_CreateNumber(memory.SwapFree/1024);
    if(!SwapFree){cJSON_Delete(memInfoJSON); return NULL;}
    cJSON_AddItemToObject(memInfoJSON, "SwapFree", SwapFree);

    printMemInfoJSON = cJSON_Print(memInfoJSON);

    cJSON_Delete(memInfoJSON);

    return printMemInfoJSON;
}

char *cJSONFormatCPU(CPU_INFO cpu)
{
     char *printCpuInfoJSON = NULL;
     cJSON *ModelName       = NULL;
     cJSON *Cores           = NULL;
     cJSON *Threads         = NULL;

     cJSON *cpuInfoJSON = cJSON_CreateObject();
     if(!cpuInfoJSON) return NULL;

     Cores = cJSON_CreateNumber(cpu.Cores);
     if(!Cores) {cJSON_Delete(cpuInfoJSON); return NULL;}
     cJSON_AddItemToObject(cpuInfoJSON, "Cores", Cores);

     Threads = cJSON_CreateNumber(cpu.Threads);
     if(!Threads) {cJSON_Delete(cpuInfoJSON); return NULL;}
     cJSON_AddItemToObject(cpuInfoJSON, "Threads", Threads);

     ModelName = cJSON_CreateString(cpu.ModelName);
     if(!ModelName) {cJSON_Delete(cpuInfoJSON); return NULL;}
     cJSON_AddItemToObject(cpuInfoJSON, "ModelName", ModelName);

     printCpuInfoJSON = cJSON_Print(cpuInfoJSON);

     cJSON_Delete(cpuInfoJSON);

     return printCpuInfoJSON;
}

char *cJSONFormatWords(char** words, u_int32_t n)
{
     char *printWords  = NULL;
     cJSON *WordsArray = NULL;
     cJSON *Words      = NULL;

     cJSON *JSONWords = NULL;
     JSONWords = cJSON_CreateObject();
     if(!JSONWords) return NULL;

     WordsArray = cJSON_CreateArray();
     if(!WordsArray) {cJSON_Delete(JSONWords); return NULL;}
     cJSON_AddItemToObject(JSONWords, "WordsArray", WordsArray);

     for(u_int32_t i=0; i < n; i++)
     {
          Words = cJSON_CreateString(words[i]);
          if(!Words){cJSON_Delete(JSONWords); return NULL;}
          cJSON_AddItemToArray(WordsArray, Words);
     }

     printWords = cJSON_Print(JSONWords);

     cJSON_Delete(JSONWords);

     return printWords;
}

void printWords(char** words,u_int32_t n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%s \n", words[i]);
    }
    printf("\n");
}

void pluginDynamic()
{
    void *libhandle = dlopen("libplugin.so", RTLD_LAZY);

    if(!libhandle)
    {
        fprintf(stderr, "%s \n", dlerror());
        exit(EXIT_FAILURE);
    }

    char** (*getFileSystems) (u_int32_t*);

    *(void**) &(getFileSystems) = dlsym(libhandle, "getFileSystems");

    u_int32_t n;
    char** words = getFileSystems(&n);

    printf("%s \n", cJSONFormatWords(words, n));

    dlclose(libhandle);
                
    freeWords(words, n);
}
