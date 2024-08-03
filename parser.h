#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <string.h>
#include "color.h"

typedef struct 
{
    char type[2];
    unsigned int width;
    unsigned int height;
    unsigned int maximum_color_value;
} surface_properties;

FILE* open_file(const char* filename);
void close_file(FILE* file);
surface_properties read_config(FILE* file);
void print_config(surface_properties properties);
color* read_pixels(FILE* file, surface_properties properties);

#endif


