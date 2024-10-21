#include <stdio.h>
#include <sys/time.h>
#include <oraxml.hpp>

#define DTD_VALIDATION_SUPPORTED
#include "tools.h"

XMLParser *parser;

void initXML(struct TestData *td) {
    unsigned int ecode;
    parser=new XMLParser;
    ecode=parser->xmlinit();
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
    }	
//    parser->xmlclean();
    parser->xmlterm();
    parser->xmlinit();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
