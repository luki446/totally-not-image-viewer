#ifndef IMG_H
#define IMG_H

#include <memory.h>


typedef struct _img
{
    char* name;
    unsigned int width;
    unsigned int height;
    unsigned int * pixels;
} _Image;

void free_image(_Image * ptr)
{
    free(ptr->pixels);
    free(ptr);
}

#endif