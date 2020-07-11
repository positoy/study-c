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

void readXML(const char* path) {
    xmlDoc* doc = xmlParseFile(path);
    xmlNode* root = xmlDocGetRootElement(doc);
    print_node(root,0);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void writeXML() {
    xmlDoc* doc;
    xmlNode* node;
    xmlChar* xmlbuff;
    int bufsize;

    doc = xmlNewDoc("1.0");
    node = xmlNewNode(NULL, "greeting");
    xmlNodeSetContent(node, "this is the content");
    xmlDocSetRootElement(doc, node);

    xmlDocDumpFormatMemory(doc, &xmlbuff, &bufsize, 1);
    printf("%s", (char*)xmlbuff);

    xmlFree(xmlbuff);
    xmlFreeDoc(doc);

    return;
}

int main(int argc, char* argv[])
{
    readXML("DoxygenLayout.xml");
    writeXML();

    return 0;
}
