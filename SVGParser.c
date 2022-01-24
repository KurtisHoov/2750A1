#include "SVGParser.h"
#include "LinkedListAPI.c"
#include "SVGHelpers.c"
#include <string.h>

char * SVGToString(const SVG* newSvg){
    char *output = malloc(10000);
    char *test = NULL;
    sprintf(output, "");
    printf("in SVG to String\n");
    //for rectangles
    if(newSvg->rectangles != NULL){
        printf("rectangles\n");
        strcat(output,"\nprinting rectangle:::::::::::::\n");
        test = toString(newSvg->rectangles);
        strcat(output, test);
        free(test);
        test = NULL;
        Rectangle * newRect = newSvg->rectangles->head->data;
        
        if (newRect->otherAttributes != NULL) {
            printf("otherAtt Rec\n");
            strcat(output,"\nprinting rectangle attributes:::::::::\n");
            test = toString(newRect->otherAttributes);
            strcat(output, test);
            free(test);
            test = NULL;
        }
    }
    //for circles
    if(newSvg->circles != NULL){
        printf("circles\n");
        strcat(output,"\nprinting circle:::::::::::::\n");
        test = toString(newSvg->circles);
        //output = (char *)realloc(output, strlen(test) + 1);
        strcat(output, test);
        free(test);
        test = NULL;

        Circle * newCircle = newSvg->circles->head->data;
        
        if (newCircle->otherAttributes != NULL) {
            strcat(output,"\nprinting circle attributes:::::::::\n");
            test = toString(newCircle->otherAttributes);
           // output = (char *)realloc(output, strlen(test) + 1);
            strcat(output, test);
            free(test);
            test = NULL;
        }
    }
    //for paths
    if(newSvg->paths != NULL){
        printf("paths\n");
        strcat(output,"\nprinting path:::::::::::::\n");
        test = toString(newSvg->paths);
        printf("woenfoweifnoi %d\n", sizeof(test));
        // output = (char *)realloc(output, strlen(test) + 1);
        strcat(output, test);
        free(test);
        test = NULL;

        Path * newPath = newSvg->paths->head->data;
        
        if (newPath->otherAttributes != NULL) {
            strcat(output,"\nprinting path attributes:::::::::\n");
            test = toString(newPath->otherAttributes);
            // output = (char *)realloc(output, strlen(test) + 1);
            strcat(output, test);
            free(test);
            test = NULL;
        }
    }
    //for svg attributes
    if (newSvg->otherAttributes != NULL) {
        printf("svg\n");
        strcat(output,"\nprinting svg attributes::::::::::\n");
        test = toString(newSvg->otherAttributes);
        //output = (char *)realloc(output, strlen(test) + 1 + sizeof(SVG));
        strcat(output, test);
        free(test);
        test = NULL;
    }
    return(output);
}
void deleteSVG(SVG * newSvg){
    if(newSvg->otherAttributes != NULL){
        printf("freeing otherAtt\n");
        freeList(newSvg->otherAttributes); //free svg attributes
    }
    if(newSvg->rectangles != NULL){
        Rectangle *rect = newSvg->rectangles->head->data;
        if(rect->otherAttributes != NULL){
            printf("freeing rectAtts\n");
            freeList(rect->otherAttributes); //free rect attributes
        }
        freeList(newSvg->rectangles); //free rect
    }
    if(newSvg->circles != NULL){
        Circle *circle = newSvg->circles->head->data;
        if(circle->otherAttributes != NULL){
            printf("freeing circleAtts\n");
            freeList(circle->otherAttributes); //free circle attributes
        }
        freeList(newSvg->circles); //free cirle
    }
    if(newSvg->paths != NULL){
        Path *path = newSvg->paths->head->data;
        if(path->otherAttributes != NULL){
            printf("freeing pathAtts\n");
            freeList(path->otherAttributes); //free circle attributes
        }
        freeList(newSvg->paths); //free cirle
    }
    
    free(newSvg);
}

List * rectParse(xmlNode * a_node, SVG * newSvg){
    xmlNode *cur_node = NULL;
    cur_node = a_node;
    Rectangle* newRect = malloc(sizeof(Rectangle));
    newRect->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes); //initalize rectangle attribute list

    printf("going into rect loop\n");
    xmlAttr *attr;
    for(attr = cur_node->properties; attr != NULL; attr = attr->next){

        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);

        if(strcmp(attrName, "x") == 0){
            newRect->x = atof(cont);
            printf("\n x = %.0f", newRect->x);
        }else if(strcmp(attrName, "y") == 0){
            newRect->y = atof(cont);
            printf("\n y = %.0f", newRect->y);
        }else if(strcmp(attrName, "width") == 0){
            newRect->width = atof(cont);
            printf("\n width = %.0f", newRect->width);
        }else if(strcmp(attrName, "height") == 0){
            newRect->height = atof(cont);
            printf("\n height = %.0f\n", newRect->height);
            
        }else{ //otherAttributes
            Attribute* rectAtt = malloc(sizeof(Attribute) + strlen(cont) * sizeof(char) + 1);   //create new attribute node
            rectAtt->name = malloc(sizeof(char) * strlen(attrName) + 1); //malloc name
            sprintf(rectAtt->name,"%s", attrName); //set name
            sprintf(rectAtt->value,"%s", cont); //set vlaue
            printf("\trectAtt name: %s, value = %s\n", rectAtt->name, rectAtt->value);
            insertBack(newRect->otherAttributes, rectAtt);
        }
    }
    insertBack(newSvg->rectangles, newRect);
}

List * circleParse(xmlNode * a_node, SVG * newSvg){
    xmlNode *cur_node = NULL;
    cur_node = a_node;
    Circle* newCircle = malloc(sizeof(Circle));
    newCircle->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes); //initalize circle attribute list

    printf("going into circle loop\n");
    xmlAttr *attr;
    for(attr = cur_node->properties; attr != NULL; attr = attr->next){
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);

        if(strcmp(attrName, "cx") == 0){
            newCircle->cx = atof(cont);
            printf("\n cx = %.0f", newCircle->cx);
        }else if(strcmp(attrName, "cy") == 0){
            newCircle->cy = atof(cont);
            printf("\n cy = %.0f", newCircle->cy);
        }else if(strcmp(attrName, "r") == 0){
            newCircle->r = atof(cont);
            printf("\n r = %.0f", newCircle->r);
        }
        else{ //otherAttributes
            Attribute* circleAtt = malloc(sizeof(Attribute) + strlen(cont) * sizeof(char) + 1);   //create new attribute node
            circleAtt->name = malloc(sizeof(char) * strlen(attrName) + 1); //malloc name
            sprintf(circleAtt->name,"%s", attrName); //set name
            sprintf(circleAtt->value,"%s", cont); //set vlaue
            printf("\tcircleAtt name: %s, value = %s\n", circleAtt->name, circleAtt->value);
            insertBack(newCircle->otherAttributes, circleAtt);
        }
    }
    insertBack(newSvg->circles, newCircle);
}
List * pathParse(xmlNode * a_node, SVG * newSvg){
    xmlNode *cur_node = NULL;
    cur_node = a_node;
    Path* newPath = malloc(sizeof(Path));
    newPath->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes); //initalize path attribute list

    printf("going into path loop\n");
    xmlAttr *attr;
    for(attr = cur_node->properties; attr != NULL; attr = attr->next){
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);
        if(strcmp(attrName, "d") == 0){
            newPath = realloc(newPath, strlen(cont) + sizeof(Path) + 1);
            sprintf(newPath->data, "%s", cont);
            printf("here1\n");

            printf("\n d = %s\n", newPath->data);
        }
        else{ //otherAttributes
            printf("attrName = %s, cont = %s\n", attrName, cont);
            Attribute* pathAtt = malloc(sizeof(Attribute) + strlen(cont) * sizeof(char) + 1);   //create new attribute node
            printf("here2\n");

            pathAtt->name = malloc(sizeof(char) * strlen(attrName) + 1); //malloc name
            sprintf(pathAtt->name,"%s", attrName); //set name
            sprintf(pathAtt->value,"%s", cont); //set vlaue
            printf("\tpathAtt name: %s, value = %s\n", pathAtt->name, pathAtt->value);
            insertBack(newPath->otherAttributes, pathAtt);
        }
    }
    insertBack(newSvg->paths, newPath);
}


SVG * svgParse(xmlNode * a_node, SVG *newSvg)
{
    xmlNode *cur_node = NULL;
    //SVG* newSvg = malloc(sizeof(SVG)); //create node for new node type
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        //if the current node is and element
       
        if (cur_node->type == XML_ELEMENT_NODE) {
            //sprintf(newSvg->namespace,"%s", cur_node->name); //assign name to nameSpace
            printf("node type: Element, name: %s\n", cur_node->name);
            //printf("node type: Element, name: %s\n", newSvg->namespace);
        }
        if(strcmp(cur_node->name, "title") == 0){ //if we are on the title the content will be found in the child
            sprintf(newSvg->title,"%s", cur_node->children->content);
            printf("title = %s", newSvg->title);
        }
        // Uncomment the code below if you want to see the content of every node.
        // if (cur_node->content != NULL){
        //     printf("  content: %s\n", cur_node->content);
        // }
        // Iterate through every attribute of the current node
        xmlAttr *attr;
        printf("before entering the for loop - cur_node->name = %s\n", cur_node->name);

        if(strcmp(cur_node->name, "rect") == 0){
            newSvg->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles); //initalize rectangle list
            newSvg->rectangles = rectParse(cur_node, newSvg); //parse rectangle
        }else if(strcmp(cur_node->name, "circle") == 0){
            newSvg->circles = initializeList(&circleToString, &deleteCircle, &compareCircles); //initalize circle list
            newSvg->circles = circleParse(cur_node, newSvg); //parse circle
        }else if(strcmp(cur_node->name, "path") == 0){
            newSvg->paths = initializeList(&pathToString, &deletePath, &comparePaths);
            newSvg->paths = pathParse(cur_node, newSvg);
        }else if(strcmp(cur_node->name, "svg") == 0){ 
            newSvg->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes); //initalize attribute list
            newSvg->rectangles = NULL;
            newSvg->circles = NULL;
            newSvg->paths = NULL;

            printf("going into svg attributes\n");
            for (attr = cur_node->properties; attr != NULL; attr = attr->next){            

                xmlNode *value = attr->children;
                char *attrName = (char *)attr->name;
                char *cont = (char *)(value->content);
           
                Attribute* newAtt = malloc(sizeof(Attribute) + strlen(cont) * sizeof(char) + 1);   //create new attribute node
                newAtt->name = malloc(sizeof(char) * strlen(attrName) + 1); //malloc name
                sprintf(newAtt->name,"%s", attrName); //set name
                sprintf(newAtt->value,"%s", cont); //set vlaue
                printf("\tattribute name: %s, attribute value = %s\n", newAtt->name, newAtt->value);
                insertBack(newSvg->otherAttributes, newAtt);
            }
        }
        

        svgParse(cur_node->children, newSvg);
        
    }
    return(newSvg);


}


 SVG* createSVG(const char* fileName){
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    LIBXML_TEST_VERSION

    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", fileName);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    SVG* newSvg = malloc(sizeof(SVG)); //create node for new node type
    newSvg = svgParse(root_element, newSvg);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
    if(newSvg != NULL){
        printf("returning newSvg\n");
        return newSvg;
    }else{
        return NULL;
    }

 }

int main(int argc, char *argv[]){
    if (argc != 2)
        return(1);


    SVG * newSvg = createSVG(argv[1]);
    if(newSvg != NULL){
        printf("here!!!!!!!\n");
        char * output = SVGToString(newSvg);
        printf("-------------------------\n%s", output);
        free(output);
        printf("-------------------------\n");
        deleteSVG(newSvg);
    }
}
