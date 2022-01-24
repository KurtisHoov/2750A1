#include "SVGParser.h"

char* attributeToString(void* data){
    Attribute* attribute = data;
    if (attribute == NULL) { return NULL; }
    char* output = malloc(strlen(attribute->name) + strlen(attribute->value) + 4);
    sprintf(output, "%s: %s\n", attribute->name, attribute->value);

    //printf("Output = %s\n", output);
    return(output);
}
void deleteAttribute(void* data){

    Attribute *attribute = data;
    printf("we deleteing %s\n", attribute->name);
    free(attribute->name);
    free(attribute);
}
int compareAttributes(const void *first, const void *second){
    printf("we in compare\n");
    return 3;
}
void deleteRectangle(void* data){
    Rectangle *rect = data;
    printf("we deleting rectangle %f\n", rect->y);
    free(rect);

}
char* rectangleToString(void* data){
    Rectangle* rect = data;
    if (rect == NULL) { return NULL; }
    char* output = malloc(50);
    sprintf(output,"x = %.0f\ny = %.0f\nheight = %.0f\nwidth = %.0f\n",rect->x, rect->y, rect->width, rect->height);
    return(output);

}
int compareRectangles(const void *first, const void *second){
    return 3;
}
void deleteCircle(void* data){
    Circle *circle = data;
    printf("Deleting Circle\n");
    free(circle);
}
char* circleToString(void* data){
    Circle* circle = data;
    if (circle == NULL) { return NULL; }
    char* output = malloc(50);
    sprintf(output,"cx = %.0f\ncy = %.0f\nr = %.0f\n",circle->cx, circle->cy, circle->r);
    return(output);
}
int compareCircles(const void *first, const void *second){
    return 3;
}
void deletePath(void* data){
    Path * path = data;
    printf("deleting path\n");
    free(path);
}
char* pathToString(void* data){
    Path * path = data;
    if(path == NULL) { return NULL; }
    printf("data :::::: %d\n", strlen(path->data));
    char* output = malloc(strlen(path->data) + 9);
    sprintf(output,"data = %s", path->data);
    return (output);
}
int comparePaths(const void *first, const void *second){
    return 3;
}