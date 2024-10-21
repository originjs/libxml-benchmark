#include <stdio.h>
#include <sys/time.h>
#include <oraxml.hpp>

#define DTD_VALIDATION_SUPPORTED
#include "tools.h"

int startDocument(void *ctx) {
    return 0;
}
int endDocument(void *ctx) {
    return 0;
}
int startElement(void *ctx, const oratext *name, const struct xmlnodes *attrs) {
    return 0;
}
int endElement(void *ctx, const oratext *name) {
    return 0;
}
int characters(void *ctx, const oratext *ch, size_t len) {
    return 0;
}

xmlsaxcb saxcb = {
    startDocument,
    endDocument,
    startElement,
    endElement,
    characters
};

XMLParser *parser;

void initXML(struct TestData *td) {
    unsigned int ecode;
    parser=new XMLParser;
    ecode=parser->xmlinit(0,0,0,&saxcb);
    if (ecode)
    {
        fprintf(stderr,"Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
}

void releaseXML(struct TestData *td) {
    parser->xmlterm();
    delete parser;
}

void parseXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;
    
#ifdef DTD_VALIDATION
    ecode=parser->xmlparseBuffer((oratext*)td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE|XML_FLAG_VALIDATE);
#else
    ecode=parser->xmlparseBuffer((oratext*)td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE);
#endif
    if (ecode) {
	fprintf(stderr,"Failed to parse XML file, error %u\n", (unsigned) ecode);
	exit(1);
    }	
//    parser->xmlclean();
    parser->xmlterm();
    parser->xmlinit(0,0,0,&saxcb);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
