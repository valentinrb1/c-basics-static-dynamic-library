/**
 * @file Plugin.c
 * @author Robledo, Valentín
 * @brief Function that implements the "plugin" that obtains information from /proc/filesystems and is used as a dynamic library.
 * @version 1.0
 * @date September de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Plugin.h"

char** getFileSystems(u_int32_t* n)
{
    u_int32_t w_count = 0;
    u_int32_t c_count = 0;

    FILE* file;
    char* line_buf = NULL;
    size_t line_buf_size;
    ssize_t line_size;

    file = fopen("/proc/filesystems", "r");
    if(file == NULL) exit(EXIT_FAILURE);

    char** words = malloc(sizeof(char*));
    words[w_count] = malloc(sizeof(char));

    line_size = getline(&line_buf, &line_buf_size, file);

    while(line_size > 0)
    {
        c_count = 0;

        for(u_int32_t i = 0; line_buf[i] != '\0'; i++)
        {
            if(line_buf[i] == 9 && i > 0) line_buf[i] = ' ';

            if(line_buf[i] != '\n' && line_buf[i] != 9)
            {
                words[w_count][c_count] = line_buf[i];

                c_count++;

                words[w_count] = realloc(words[w_count], (c_count+1)*sizeof(char));
            }
        }

        words[w_count][c_count] = '\0';

        w_count++;
        
        words = realloc(words, (w_count + 1) * sizeof(char*));
        words[w_count] = malloc(sizeof(char));

        line_size = getline(&line_buf, &line_buf_size, file);
    }

    free(words[w_count]);
    w_count--;

    words = realloc(words, (w_count+1)*sizeof(char*));
    
    free(line_buf);
    fclose(file);

    *n = w_count;

    return words;
}