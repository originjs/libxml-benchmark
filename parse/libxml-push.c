#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "tools.h"

//xmlSAXHandler handler;

void initXML(struct TestData *td) {
    xmlInitParser();
//    initxmlDefaultSAXHandler(&handler,0);
}

void releaseXML(struct TestData *td) {
    xmlCleanupParser();
}

void parseXML(struct TestData *td, unsigned long iter) {
    xmlParserCtxtPtr ctx;
    xmlChar *mem;
    int memsize;
    
//    ctx=xmlCreatePushParserCtxt(&handler,NULL,td->xml,4,"opc");
    ctx=xmlCreatePushParserCtxt(NULL,NULL,td->xml,4,"opc");
    xmlParseChunk(ctx,td->xml+4,td->xmllen-4,1);
    
/*    xmlDocDumpMemory(ctx->myDoc,&mem,&memsize);
    if (iter==td->iterations) puts(mem);
    free(mem);*/
    
    xmlFreeDoc(ctx->myDoc);
    xmlFreeParserCtxt(ctx);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
