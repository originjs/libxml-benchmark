#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "tools.h"

#if LIBXML_VERSION > 20600
#define _SAX2_BENCHMARK
#endif

void startElement_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, const xmlChar **atts) {
    return;
}

void endElement_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name) {
    return;
}
void characters_(void *ctx ATTRIBUTE_UNUSED, const xmlChar *ch, int len) {
    return;
}


xmlSAXHandler handler = {
    NULL, /* internalSubset */
    NULL, /* isStandalone */
    NULL, /* hasInternalSubset */
    NULL, /* hasExternalSubset */
    NULL, /* resolveEntity */
    NULL, /* getEntity */
    NULL, /* entityDecl */
    NULL, /* notationDecl */
    NULL, /* attributeDecl */
    NULL, /* elementDecl */
    NULL, /* unparsedEntityDecl */
    NULL, /* setDocumentLocator */
    NULL, /* startDocument */
    NULL, /* endDocument */
    startElement_, /* startElement */
    endElement_, /* endElement */
    NULL, /* reference */
    characters_, /* characters */
    NULL, /* ignorableWhitespace */
    NULL, /* processingInstruction */
    NULL, /* comment */
    NULL, /* xmlParserWarning */
    NULL, /* xmlParserError */
    NULL, /* xmlParserError */
    NULL, /* getParameterEntity */
    NULL, /* cdataBlock; */
    NULL, /* externalSubset; */
#ifndef _SAX2_BENCHMARK
    1
#else
    XML_SAX2_MAGIC,    /* XML_SAX1_MAGIC, XML_SAX2_MAGIC */
    NULL,
    NULL, /* startElementNs */
    NULL, /* endElementNs */
    NULL  /* xmlStructuredErrorFunc */
#endif /* _SAX2_BENCHMARK */
};

void initXML(struct TestData *td) {
}

void releaseXML(struct TestData *td) {
    xmlCleanupParser();
}

void parseXML(struct TestData *td, unsigned long iter) {
    xmlSAXUserParseMemory(&handler,NULL,td->xml,td->xmllen);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
