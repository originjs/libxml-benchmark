#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <sstream>

#include <SAX/XMLReader.h>
#include <SAX/ContentHandler.h>
#include <SAX/InputSource.h>

#include "tools.h"

class SimpleHandler : public SAX::ContentHandler {
 public:
    void startElement(const std::string& namespaceURI, const std::string& localName,
                        const std::string& qName, const AttributesT& atts);
    void endElement(const std::string& namespaceURI, const std::string& localName,
                        const std::string& qName);
    void characters(const std::string& ch);

  SimpleHandler() { }
  ~SimpleHandler() { }
  
  void setDocumentLocator(const LocatorT& locator) { }
  void startDocument() {}
  void endDocument() {}
  void startPrefixMapping(const std::string& prefix, const std::string& uri) {}
  void endPrefixMapping(const std::string& prefix) {}
  void ignorableWhitespace(const std::string& ch) {}
  void processingInstruction(const std::string& target, const std::string& data) {}
  void skippedEntity(const std::string& name) {}
};

    void SimpleHandler::startElement(const std::string& namespaceURI, const std::string& localName, const std::string& qName, const AttributesT& atts) {
	return;
    }
    void SimpleHandler::endElement(const std::string& namespaceURI, const std::string& localName, const std::string& qName) {
	return;
    }
    void SimpleHandler::characters(const std::string& ch) {
	return;
    }

SimpleHandler *handler;

void initXML(struct TestData *td) {
    handler = new SimpleHandler;
}

void releaseXML(struct TestData *td) {
    delete handler;
}


void parseXML(struct TestData *td, unsigned long iter) {
    SAX::XMLReader<std::string> parser;    
    parser.setContentHandler(*handler);

    std::istringstream strm(td->xml);
    SAX::InputSource is(strm);
    parser.parse(is);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
