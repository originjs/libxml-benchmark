#include <stdio.h>
#include <sys/time.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <XalanTransformer/XalanTransformer.hpp>
#include <xalanc/XercesParserLiaison/XercesParserLiaison.hpp>
#include <xalanc/XercesParserLiaison/XercesDOMSupport.hpp>
#include <xalanc/XalanTransformer/XercesDOMWrapperParsedSource.hpp>
#include <xalanc/PlatformSupport/URISupport.hpp>

#include <iostream>
#include <strstream>
#include <sstream>

//#define PARSE_DOM /* Slower */

#ifdef PARSE_DOM
#include "tools.h"
#else
#include "tools2.h"
#endif /* PARSE_DOM */


#if defined(XALAN_HAS_CPP_NAMESPACE)
XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XERCES(MemBufInputSource)
XALAN_USING_XERCES(XercesDOMParser)
XALAN_USING_XALAN(XalanTransformer)
XALAN_USING_XALAN(XalanCompiledStylesheet)
XALAN_USING_XALAN(XSLTInputSource)
#ifdef PARSE_DOM
XALAN_USING_XALAN(XercesParserLiaison)
XALAN_USING_XALAN(XercesDOMSupport)
XALAN_USING_XALAN(XercesDOMWrapperParsedSource)
XALAN_USING_XALAN(URISupport);
XALAN_USING_XALAN(XalanDOMString)
#endif /* PARSE_DOM */
#endif


XalanTransformer 		xt;
const XalanCompiledStylesheet*	cs = 0;
XercesDOMParser *parser = NULL;

const char id[5]="ID1\0";

#ifdef PARSE_DOM
const XalanDOMString theURI((const char*)id);
XercesParserLiaison theParserLiaison;
XercesDOMSupport theDOMSupport;
#endif /* PARSE_DOM */

void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
}

void initXML_Transformation(struct TestData *td) {
    XalanTransformer::initialize();
//    std::istringstream theXSLStream(td->xsl,std::istringstream::bin); NW
    std::istrstream theXSLStream(td->xsl, td->xsllen);
    const XSLTInputSource inputSource(&theXSLStream);

    if (xt.compileStylesheet(inputSource, cs)) {
	fprintf(stderr,"Error parsing XSL stylesheet\n");
	exit(1);
    }
}

void releaseXML(struct TestData *td) {
    if (parser) delete parser;
    xt.destroyStylesheet(cs);    
    XalanTransformer::terminate();
    XMLPlatformUtils::Terminate();
}

void parseXML(struct TestData *td, unsigned long iter) {
    MemBufInputSource *buffer;

    if (parser) delete parser;
    parser = new XercesDOMParser;
    buffer=new MemBufInputSource((XMLByte*)td->xml,td->xmllen,(const char*)&id);
    buffer->setCopyBufToStream(false);
    parser->parse(*buffer);
    delete buffer;
}

void transformXML(struct TestData *td, unsigned long iter) {
    std::ostringstream os;

#ifdef PARSE_DOM
    const XercesDOMWrapperParsedSource wrapper(parser->getDocument(),theParserLiaison,theDOMSupport,theURI);
    xt.transform(wrapper,cs,os);
#else
//    std::istringstream theXMLStream(td->xml,std::istringstream::out); NW
    std::istrstream	theXMLStream(td->xml, td->xmllen);
    xt.transform(&theXMLStream,cs,os);
#endif

//    if (iter==td->iterations) std::cout<<os.str();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
