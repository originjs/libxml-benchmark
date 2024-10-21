#include <stdio.h>
#include <sys/time.h>
#include <sstream>

#include <DOMBuilder.h>
#include <DOM/Document.h>
#include <SAX/InputSource.h>

#include "tools.h"

using namespace CSL::XML;

DOMBuilder *parser;

void initXML(struct TestData *td) {
    parser = new DOMBuilder;
//	parser->setFeature("namespaces", false);                    // turn off namespace support
//	parser->setFeature("white-space-in-element-content", true); // do not remove ignorable whitespace
}

void releaseXML(struct TestData *td) {
    delete parser;
}


void parseXML(struct TestData *td, unsigned long iter) {
    Document *doc;
    
    istringstream strm(td->xml);
    CInputSource is(&strm);
    doc=parser->parseDOMInputSource(&is);    
    doc->release();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
