#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#if LIBXML_VERSION > 20600
#define READ_MEMORY
//xmlParserCtxtPtr ctxt = NULL;
#endif

#ifdef READ_MEMORY
#define DTD_VALIDATION_SUPPORTED
#endif

#include "tools.h"



void initXML(struct TestData *td) {
    xmlInitParser();
#ifdef READ_MEMORY
/*    ctxt = xmlNewParserCtxt();
    if (!ctxt) {
	fprintf(stderr, "Can't create parser context!\n");
	exit(0);
    }*/
#endif
}

void releaseXML(struct TestData *td) {
#ifdef READ_MEMORY
//    if (ctxt) xmlFreeParserCtxt(ctxt);
#endif
    xmlCleanupParser();
}

void parseXML(struct TestData *td, unsigned long iter) {
    int err;
    xmlDocPtr doc;
#ifdef READ_MEMORY
#ifdef DTD_VALIDATION
    doc=xmlReadMemory(td->xml,td->xmllen,"xml",NULL,XML_PARSE_DTDVALID);
#else
    doc=xmlReadMemory(td->xml,td->xmllen,"xml",NULL,0);
#endif
/*    doc=xmlCtxtReadMemory(ctxt,td->xml,td->xmllen,"xml",NULL,XML_PARSE_DTDVALID);
    printf("%u\n",ctxt->valid); */


#else
    doc=xmlParseMemory(td->xml,td->xmllen);
#endif
    if (!doc) {
        printf("Error parsing document!\n");
        exit(0);
    }
    xmlFreeDoc(doc);    

}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
