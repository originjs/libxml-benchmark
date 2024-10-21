#include <stdio.h>
#include <sys/time.h>
#include <oratypes.h>
#include <oraxml.h>
#include <oraxsd.h>

#include "tools.h"

xmlctx	*ctx;
xsdctx	*scctx; 
xsd	*xsddoc;
xmlnode	*node;


void initXML(struct TestData *td) {
    unsigned int ecode;
    ctx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
    if (!ctx)
    {
        printf("Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
}

void initXML_Validation(struct TestData *td) {
    unsigned int ecode;
    scctx=schemaInitialize(ctx,&ecode);
    if (!scctx) {
        printf("Failed to initialze Schema Validator, error %u\n", (unsigned) ecode);
        exit(1);
    }

    ecode=schemaLoad(scctx,td->scfn,NULL,&xsddoc);
    if (ecode) {
        printf("Failed to parse xsd file, error %u\n", (unsigned) ecode);    
    }
}

void releaseXML(struct TestData *td) {
	schemaTerminate(scctx);
//	xmlterm(ctx);
}


void parseXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;

    ecode=xmlparsebuf(ctx,td->xml,td->xmllen,0,XML_FLAG_DISCARD_WHITESPACE);
    if (ecode) {
	printf("Failed to parse XML file, error %u\n", (unsigned) ecode);
    }	

    node=getDocumentElement(ctx);
}

void validateXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;
    
    ecode=schemaValidate(scctx,node,NULL);
    if (ecode) {
	printf("Validating of XML file failed, error %u\n", (unsigned) ecode);
    }	
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
