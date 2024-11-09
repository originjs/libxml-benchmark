#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlsave.h>

#if LIBXML_VERSION > 20600
#define READ_MEMORY
//xmlParserCtxtPtr ctxt = NULL;
#endif

#ifdef READ_MEMORY
#define DTD_VALIDATION_SUPPORTED
#endif

#include "tools.h"

static void libxml_free_doc(void* doc) {
    xmlFreeDoc((xmlDocPtr)doc);
}

void initXML(struct TestData *td) {
    xmlInitParser();
    td->free_doc = libxml_free_doc;
}

void releaseXML(struct TestData *td) {
#ifdef READ_MEMORY
//    if (ctxt) xmlFreeParserCtxt(ctxt);
#endif
    xmlCleanupParser();
}

void* parseXML(struct TestData *td, unsigned long iter) {
    int err;
    xmlDocPtr doc;
#ifdef READ_MEMORY
#ifdef DTD_VALIDATION
    doc=xmlReadMemory(td->xml,td->xmllen,"xml",NULL,XML_PARSE_DTDVALID);
#else
    doc=xmlReadMemory(td->xml,td->xmllen,"xml",NULL,0);
#endif
#else
    doc=xmlParseMemory(td->xml,td->xmllen);
#endif
    if (!doc) {
        printf("Error parsing document!\n");
        exit(0);
    }
    return (void*)doc;
}

void saveXML(struct TestData *td, void* doc) {
    xmlSaveCtxtPtr savectx;
    long bytes_written;

    // 创建保存上下文,保存到文件
    savectx = xmlSaveToFilename("output-test.rdf", NULL, XML_SAVE_FORMAT);
    if (!savectx) {
        printf("Error creating save context!\n");
        exit(0);
    }

    // 保存文档
    bytes_written = xmlSaveDoc(savectx, (xmlDocPtr)doc);
    if (bytes_written == -1) {
        printf("Error saving document!\n");
        xmlSaveClose(savectx);
        exit(0);
    }

    xmlSaveClose(savectx);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
