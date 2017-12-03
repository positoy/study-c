#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void print_node(xmlNode* _node, int depth) {
    xmlNode* node = NULL;
    for (node=_node; node; node=node->next) {

        if (node->type == XML_ELEMENT_NODE) {
            for (int i=0; i<depth; i++) printf("\t");
            printf("%s\n", node->name);
        }
        print_node(node->children, depth+1);
    }
}

int main()
{
    xmlDoc* doc = xmlParseFile("DoxygenLayout.xml");
    xmlNode* root = xmlDocGetRootElement(doc);
    print_node(root,0);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
