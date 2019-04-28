#include "img.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>

#define hello printf("Hello Im here %d \n", __LINE__);

_Image* read_pbm(FILE* fp, char* path)
{
    unsigned int black = 0x00000000;
    unsigned int white = 0xFFFFFFFF;

    char header[3] = { 0 };
    fscanf(fp, "%s\n", header);
    if(strcmp(header, "P1") != 0)
    {
        fprintf(stderr, "File is not PBM P1 format");
        return NULL;
    }
    int width, height;
    fscanf(fp, "%d %d", &width, &height);
    unsigned int* pixels = malloc(width * height * sizeof(unsigned int));
    int i = 0;
    for(unsigned int i = 0; i < width * height; i++)
    {
        unsigned int foo;
        fscanf(fp, "%d", &foo);
        if(foo == 0)
        {
            pixels[i] = black;
        }
        else if(foo == 1)
        {
            pixels[i] = white;
        }
    }
    _Image* tmp = malloc(sizeof(_Image));
    tmp->name = path;
    tmp->width = width;
    tmp->height = height;
    tmp->pixels = pixels;

    return tmp;
}