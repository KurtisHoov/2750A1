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
    printf("we deleteing\n");
    Attribute *attribute = data;
    free(attribute);
}

int compareAttributes(const void *first, const void *second){
    printf("we in compare\n");
    return 3;
}