#include <stdio.h>
#include <sys/time.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/sax/DocumentHandler.hpp>
#include <xercesc/sax/HandlerBase.hpp>


#include "tools.h"

#if defined(XERCES_HAS_CPP_NAMESPACE)
    XERCES_CPP_NAMESPACE_USE
#endif

class DocHandlers : public HandlerBase {
 public:
    void startElement(const XMLCh* const name, AttributeList& attributes);
    void endElement(const XMLCh* const name);
    void characters(const XMLCh* const text, const unsigned int len);
    void resetDocument();
};

void DocHandlers::startElement(const XMLCh* const name, AttributeList& attributes) {
    return;
}

void DocHandlers::endElement(const XMLCh* const name) {
    return;
}

void DocHandlers::characters(const XMLCh* const text, const unsigned int len) {
    return;
}

void DocHandlers::resetDocument() {
    return;
}

SAXParser *parser;
DocHandlers *handler;

void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
    parser=new SAXParser;
    handler=new DocHandlers;
    parser->setDocumentHandler(handler);
}

void releaseXML(struct TestData *td) {
    delete handler;
    delete parser;
    XMLPlatformUtils::Terminate();
}

void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    MemBufInputSource *buffer;

    buffer=new MemBufInputSource((XMLByte*)td->xml,td->xmllen,(const char*)&id);
    buffer->setCopyBufToStream(false);
    parser->parse(*buffer);
    delete buffer;
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
