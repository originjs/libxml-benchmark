#include <stdio.h>
#include <sys/time.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>


#include "tools.h"

#if defined(XERCES_HAS_CPP_NAMESPACE)
    XERCES_CPP_NAMESPACE_USE
#endif

void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
}

void releaseXML(struct TestData *td) {
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


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
