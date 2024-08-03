#include "parser.h"
#include <stdlib.h>

#define MAX_LINE_LENGTH 42

FILE* open_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if(file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

void close_file(FILE* file)
{
    fclose(file);
}

surface_properties read_config(FILE* file)
{
    char result[24] = "";
    surface_properties properties = {0};
    unsigned int current_line = 0;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line), file) != NULL && current_line < 3)
    {
        if(line[0]=='#') continue;
        line[strcspn(line, "\n")] = '\0';
        strcat(result, line);
        strcat(result, " ");
        current_line++;
    }
    sscanf(result, "%s %u %u %u", properties.type, &properties.width, &properties.height, &properties.maximum_color_value);
    return properties;
}

void print_config(surface_properties properties)
{
    printf("type: %s\n", properties.type);
    printf("width: %u\n", properties.width);
    printf("height: %u\n", properties.height);
    printf("maximum_color_value: %u\n", properties.maximum_color_value);
}

color* read_pixels(FILE* file, surface_properties properties)
{
    color* color_vector = (color*)malloc(properties.width * properties.height * sizeof(color));
    char line[MAX_LINE_LENGTH];
    int aux = 0;
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if(line[0]=='#') continue;
        color color_triplet;
        sscanf(line, "%d %d %d",&color_triplet.r, &color_triplet.g, &color_triplet.b);
        color_triplet.a = 1;
        color_vector[aux] = color_triplet;
        aux++;
    }
    return color_vector;
}

