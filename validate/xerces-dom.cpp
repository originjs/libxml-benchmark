#include <stdio.h>
#include <sys/time.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <iostream>

#include "DOMTreeErrorReporter.hpp"
#include "tools2.h"

DOMTreeErrorReporter *errReporter;


void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
    errReporter = new DOMTreeErrorReporter();

}

void initXML_Validation(struct TestData *td) {
}

void releaseXML(struct TestData *td) {
    delete errReporter;
    XMLPlatformUtils::Terminate();
}

void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    MemBufInputSource *buffer;
    XercesDOMParser *parser;

    parser = new XercesDOMParser;
    
    buffer=new MemBufInputSource((XMLByte*)td->xml,td->xmllen,(const char*)&id);
    buffer->setCopyBufToStream(false);
    parser->parse(*buffer);

    delete buffer;
    delete parser;

}

void validateXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    MemBufInputSource *buffer;
    XercesDOMParser *parser;

    parser = new XercesDOMParser;
    parser->setDoSchema(1);
    parser->setDoNamespaces(1);
    parser->setValidationScheme(XercesDOMParser::Val_Always);
//    parser->setValidationSchemaFullChecking(1);
    parser->setErrorHandler(errReporter);
    
    buffer=new MemBufInputSource((XMLByte*)td->xml,td->xmllen,(const char*)&id);
    buffer->setCopyBufToStream(false);
    parser->parse(*buffer);

    delete buffer;
    delete parser;
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
