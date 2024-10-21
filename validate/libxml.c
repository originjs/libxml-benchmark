#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

#include "tools.h"

xmlDocPtr doc=0;
#ifdef LIBXML_SCHEMAS_ENABLED
xmlSchemaParserCtxtPtr xsdctx;
xmlSchemaPtr xsdschema;
xmlSchemaValidCtxtPtr xsd;
#endif /* LIBXML_SCHEMAS_ENABLED */

void err(void *ctx, const char *msg, ...) {
    va_list prm;
    va_start(prm,msg);
    vprintf(msg,prm);
    va_end(prm);
}

void warn(void *ctx, const char *msg, ...) {
    va_list prm;
    va_start(prm,msg);
    vprintf(msg,prm);
    va_end(prm);
}

void initXML(struct TestData *td) {
    xmlInitParser();
}

void releaseXML(struct TestData *td) {
#ifdef LIBXML_SCHEMAS_ENABLED
    xmlSchemaFreeValidCtxt(xsd);
    xmlSchemaFree(xsdschema);
    xmlSchemaFreeParserCtxt(xsdctx);
#endif /* LIBXML_SCHEMAS_ENABLED */
    xmlFreeDoc(doc);    
    xmlCleanupParser();
}

void initXML_Validation(struct TestData *td) {
#ifdef LIBXML_SCHEMAS_ENABLED
    xsdctx=xmlSchemaNewMemParserCtxt(td->xsd,td->xsdlen);
    if (!xsdctx) {
        printf("Error parsing document schema (xmlSchemaNewMemParserCtxt)!\n");
        exit(0);
    }
    xsdschema=xmlSchemaParse(xsdctx);
    if (!xsdschema) {
        printf("Error parsing document schema (xmlSchemaParse)!\n");
        exit(0);
    }
    xsd=xmlSchemaNewValidCtxt(xsdschema);
    if (!xsd) {
        printf("Error parsing document schema (xmlSchemaNewValidCtxt)!\n");
        exit(0);
    }
    xmlSchemaSetValidErrors(xsd,err,warn,NULL);
#endif /* LIBXML_SCHEMAS_ENABLED */
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

void validateXML(struct TestData *td, unsigned long iter) {
#ifdef LIBXML_SCHEMAS_ENABLED
    if (xmlSchemaValidateDoc(xsd,doc)) {
	puts("Error in XML file!");
	exit(0);
    }
#endif /* LIBXML_SCHEMAS_ENABLED */
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
