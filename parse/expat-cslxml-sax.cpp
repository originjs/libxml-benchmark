#include <stdio.h>
#include <sys/time.h>
#include <sstream>

#include <SAX2Parser.h>
#include <SAX/ContentHandler.h>
#include <SAX/InputSource.h>

#include "tools.h"

using namespace CSL::XML;

class SimpleHandler : public CContentHandler {
 public:
	void StartElement(const XMLString& uri, const XMLString& localName, const XMLString& qname, const CAttributes& attrList);
	void EndElement(const XMLString& uri, const XMLString& localName, const XMLString& qname);
	void Characters(const XMLChar ch[], int start, int length);

	void SetDocumentLocator(const CLocator& loc) {}
	void StartDocument() {}
	void EndDocument() {}
	void IgnorableWhitespace(const XMLChar ch[], int start, int length) {}
	void ProcessingInstruction(const XMLString& target, const XMLString& data) {}
	void StartPrefixMapping(const XMLString& prefix, const XMLString& uri) {}
	void EndPrefixMapping(const XMLString& prefix) {}
	void SkippedEntity(const XMLString& name) {}
};

void SimpleHandler::StartElement(const XMLString& uri, const XMLString& localName, const XMLString& qname, const CAttributes& attrList) {
    return;
}

void SimpleHandler::EndElement(const XMLString& uri, const XMLString& localName, const XMLString& qname) {
    return;
}

void SimpleHandler::Characters(const XMLChar ch[], int start, int length) {
    return;
}

SimpleHandler *handler;
CSAX2Parser *parser;

void initXML(struct TestData *td) {
    parser = new CSAX2Parser;
    handler = new SimpleHandler;
    parser->SetContentHandler((CContentHandler*)handler);
}

void releaseXML(struct TestData *td) {
    delete parser;
    delete handler;
}

void parseXML(struct TestData *td, unsigned long iter) {
    istringstream strm(td->xml);
    CInputSource is(&strm);
    parser->Parse(&is);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
