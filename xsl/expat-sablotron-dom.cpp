#include <stdio.h>
#include <sys/time.h>
#include <sablot.h>

#include "tools.h"

SablotSituation parser;
SDOM_Document dom;
SDOM_Document xsl;
SablotHandle processor;

void initXML(struct TestData *td) {
    SablotCreateSituation(&parser);
}

void initXML_Transformation(struct TestData *td) {
    SablotParseStylesheetBuffer(parser, td->xsl, &xsl);
    SablotCreateProcessorForSituation(parser, &processor);
}

void releaseXML(struct TestData *td) {
    SablotDestroyDocument(parser,xsl);
    SablotDestroyProcessor(processor);
    SablotDestroySituation(parser);
}


void parseXML(struct TestData *td, unsigned long iter) {
    if (SablotParseBuffer(parser,td->xml,&dom)) {
	printf("Error parsing document!\n");
	exit(1);
    }

}

void transformXML(struct TestData *td, unsigned long iter) {
    char * result;
    SablotAddArgTree(parser, processor, "xsl", xsl);
    SablotAddArgTree(parser, processor, "xml", dom);
    SablotRunProcessorGen(parser, processor, "arg:/xsl", "arg:/xml", "arg:/res");
    SablotGetResultArg(processor, "arg:/res", &result);
    
//    if (iter==td->iterations) puts(result);

    SablotFree(result);
    SablotDestroyDocument(parser,dom);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
