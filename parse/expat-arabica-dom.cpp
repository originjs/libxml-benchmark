#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <SAX/InputSource.h>

#include "tools.h"

void initXML(struct TestData *td) {
}

void releaseXML(struct TestData *td) {
}

/* Drops core with Sep02, Jan03 versions */
void parseXML(struct TestData *td, unsigned long iter) {
    SAX2DOM::Parser<std::string> parser;    
    std::istringstream strm(td->xml);
    SAX::InputSource is(strm);
    parser.parse(is);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
