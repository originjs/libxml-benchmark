#include <stdio.h>
#include <sys/time.h>
#include <oratypes.h>
#include <oraxml.h>

#define ORACLE_PARSER
#include "tools.h"

xmlctx	*ctx;
xmlctx	*xslCtx;


void initXML(struct TestData *td) {
    unsigned int ecode;

    ctx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
    if (!ctx)
    {
        printf("Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
}

void initXML_Transformation(struct TestData *td) {
    unsigned int ecode;

    xslCtx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
    if (!ctx)
    {
        printf("Failed to initialze XSL parser, error %u\n", (unsigned) ecode);
        exit(1);
    }

    ecode=xmlparsebuf(xslCtx,td->xsl,td->xsllen,0,XML_FLAG_DISCARD_WHITESPACE);
    if (ecode) {
	printf("Failed to parse XSL file, error %u\n", (unsigned) ecode);
	exit(1);
    }	
}

void releaseXML(struct TestData *td) {
	xmlterm(xslCtx);
	xmlterm(ctx);
}


void parseXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;

    ecode=xmlparsebuf(ctx,td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE);
    if (ecode) {
	printf("Failed to parse XML file, error %u\n", (unsigned) ecode);
	exit(1);
    }	
}

void transformXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;
    xmlctx  *resctx;
    xmlnode *result;
    
    resctx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
    if (!ctx)
    {
        printf("Failed to initialze XSL Result parser, error %u\n", (unsigned) ecode);
        exit(1);
    }

    if (ecode = xslprocess(ctx, xslCtx, resctx, &result))
    {
        printf("XSL Transformation failed, error %u\n", (unsigned) ecode);
	exit(1);
    }

//    if (iter==td->iterations) printStream(stdout, result, 4, 0);

    xmlterm(resctx);
    xmlclean(ctx);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
