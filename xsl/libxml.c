#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <xslt.h>
#include <xsltInternals.h>
#include <transform.h>
#include <xsltutils.h>

#include "tools.h"

xmlDocPtr doc=0;
xmlDocPtr xsldoc=0;
xsltStylesheetPtr xsl=0;


void initXML(struct TestData *td) {
    xmlInitParser();
}

void releaseXML(struct TestData *td) {
    xsltFreeStylesheet(xsl);
//    xmlFreeDoc(xsldoc);
    xmlFreeDoc(doc);    
    xmlCleanupParser();
}

void initXML_Transformation(struct TestData *td) {
    xsldoc=xmlParseMemory(td->xsl,td->xsllen);
    xsl=xsltParseStylesheetDoc(xsldoc);
}


void parseXML(struct TestData *td, unsigned long iter) {
    if (doc) {
	xmlFreeDoc(doc);    
    }
    doc=xmlParseMemory(td->xml,td->xmllen);
    if (!doc) {
        printf("Error parsing document!\n");
        exit(0);
    }
}

void transformXML(struct TestData *td, unsigned long iter) {
    xmlChar *mem;
    int memsize;
    xmlDocPtr res=0;
    const char * params[1] = { NULL };

    res=xsltApplyStylesheet(xsl,doc,params);

/*    if (iter==td->iterations) {
	xmlDocDumpMemory(res,&mem,&memsize);
	puts(mem);
	free(mem);
    }*/

    xmlFreeDoc(res);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
