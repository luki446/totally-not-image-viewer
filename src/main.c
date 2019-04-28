#include <stdio.h>
#include <SDL.h>
#include <string.h>
#include "formats/img.h"
#include "formats/pbm.h"

#define WIDTH 800
#define HEIGHT 600

_Image* read_image(char* path);

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        fprintf(stderr, "You need to specify file to view\nFor example ./tniv.exe image.bmp");
        return -1;
    }
    else{
        _Image* show = read_image(argv[1]);
        if(show == NULL)
        {
            fprintf(stderr, "Opened image is NULL \n");
            return -1;
        }

        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            fprintf(stderr, "SDL_Init error: %s \n", SDL_GetError());
            return -1;
        }

        SDL_Window *win = SDL_CreateWindow("Please Work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show->width, show->height, SDL_WINDOW_SHOWN);
        if(win == NULL)
        {
            fprintf(stderr, "SDL CreateWindow error: %s \n", SDL_GetError() );
            return -1;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
        {
            fprintf(stderr, "SDL CreateRenderer error: %s \n", SDL_GetError() );
            return -1;
        }

        SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, show->width, show->height);
        if(tex == NULL)
        {
            fprintf(stderr, "SDL CreateTexture error: %s \n", SDL_GetError() );
            return -1;
        }

        uint32_t* pixels = malloc(800 * 600 * 4);
        uint32_t red = (0xFF << 24) + (0xFF << 16) + (0x00 << 8) + 0x00;

        for(uint32_t i = 0; i < 800 * 600; i++)
        {
            pixels[i] = red;
        }

        if(SDL_UpdateTexture(tex, NULL, show->pixels, sizeof(uint32_t) * show->width) != 0)
        {
            printf("SDL UpdateTexture error %s", SDL_GetError());
            return -1;
        }

        SDL_Event event;
        while(1)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
            {
                break;
            }
            if(SDL_RenderClear(renderer) != 0)
            {
                printf("SDL RenderClear error %s", SDL_GetError());
                break;
            }
            if(SDL_RenderCopy(renderer, tex, NULL, NULL) != 0)
            {
                printf("SDL RenderCopy error %s", SDL_GetError());
                break;
            }
            SDL_RenderPresent(renderer);
        }
        free_image(show);
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    return 0;
}

_Image* read_image(char * path)
{
    FILE* fp = NULL;
    char* exts = &path[strlen(path) - 3];
    fp = fopen(path, "rt");
    if(fp == NULL)
    {
        fprintf(stderr, "Error loading file %s %s \n", path, exts);
    }

    if(strcmp(exts, "pbm") == 0)
    {
        return read_pbm(fp, path);
    }
    else if(strcmp(exts, "ppm") == 0)
    {
        fprintf(stderr, "ppm is not implemented yet \n");
        return NULL;
    }
    else if(strcmp(exts, "pgm") == 0)
    {
        fprintf(stderr, "pgm is not implemented yet \n");
        return NULL;
    }
    else if(strcmp(exts, "bmp") == 0)
    {
        fprintf(stderr, "bmp is not implemented yet \n");
        return NULL;
    }
    else if(strcmp(exts, "jpg") == 0)
    {
        fprintf(stderr, "jpg is not implemented yet \n");
        return NULL;
    }
    else if(strcmp(exts, "png") == 0)
    {
        fprintf(stderr, "png is not implemented yet \n");
        return NULL;
    }
    else
    {
        fprintf(stderr, "Not recognized extension %s \n", exts);
        return NULL;
    }
    
}
