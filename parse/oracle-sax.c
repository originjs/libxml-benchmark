#include <stdio.h>
#include <sys/time.h>
#include <oratypes.h>
#include <oraxml.h>

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

xmlctx	*ctx;

void initXML(struct TestData *td) {
    unsigned int ecode;
    ctx = xmlinit(&ecode, 0, 0, 0, &saxcb, 0, 0, 0, 0);
    if (!ctx)
    {
        fprintf(stderr,"Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
}

void releaseXML(struct TestData *td) {
    xmlterm(ctx);
}

void parseXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;
    
#ifdef DTD_VALIDATION
    ecode=xmlparsebuf(ctx,td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE|XML_FLAG_VALIDATE);
#else
    ecode=xmlparsebuf(ctx,td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE);
#endif
    if (ecode) {
	fprintf(stderr,"Failed to parse XML file, error %u\n", (unsigned) ecode);
	exit(1);
    }	
    
//    xmlclean(ctx);
    xmlterm(ctx);
    ctx = xmlinit(&ecode, 0, 0, 0, &saxcb, 0, 0, 0, 0);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
