#include "SVGParser.h"
#include "LinkedListAPI.c"
#include "SVGHelpers.c"

static void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        //if the current node is and element
       SVG* newSvg = malloc(sizeof(SVG)); //create node for new node type
        if (cur_node->type == XML_ELEMENT_NODE) {
            
            sprintf(newSvg->namespace,"%s", cur_node->name); //assign name to nameSpace
            //svg->namespace = cur_node->name;
            //printf("node type: Element, name: %s\n", cur_node->name);
            printf("node type: Element, name: %s\n", newSvg->namespace);
            

        }
       
        
        if(strcmp(newSvg->namespace, "title") == 0){ //if we are on the title the content will be found in the child
            sprintf(newSvg->title,"%s", cur_node->children->content);
            printf("title = %s", newSvg->title);
        }
            
        // Uncomment the code below if you want to see the content of every node.
        // if (cur_node->content != NULL){
        //     printf("  content: %s\n", cur_node->content);
        // }


        // Iterate through every attribute of the current node
        xmlAttr *attr;
        newSvg->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes); //initalize attribute list

        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
        { 
                

            xmlNode *value = attr->children;
            char *attrName = (char *)attr->name;
            char *cont = (char *)(value->content);
            Attribute* newAtt = malloc(sizeof(Attribute) + strlen(cont) * sizeof(char) + 1);   //create new attribute node
            newAtt->name = malloc(sizeof(char) * strlen(attrName) + 1); //malloc name
            sprintf(newAtt->name,"%s", attrName); //set name
            sprintf(newAtt->value,"%s", cont); //set vlaue
                

           // printf("\tattribute name: %s, attribute value = %s\n", attrName, cont);
            printf("\tattribute name: %s, attribute value = %s\n", newAtt->name, newAtt->value);
            printf("node type: Element, name: %s\n", newSvg->namespace);

            insertBack(newSvg->otherAttributes, newAtt);

           // sprintf(newSvg->otherAttributes,"%s %s", newAtt->name, newAtt->value);
           // printf("-----OA = %s\n", newSvg->otherAttributes);

        }

        if (newSvg->otherAttributes != NULL) {
            printf("\n%s\n", toString(newSvg->otherAttributes));
        }
        
        print_element_names(cur_node->children);
        printf("calling freeList()\n");
        freeList(newSvg->otherAttributes);
    }
    
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

    print_element_names(root_element);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

     return 0;

 }

int main(int argc, char *argv[]){
    if (argc != 2)
        return(1);



    createSVG(argv[1]);
    
}