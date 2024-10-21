#include <stdio.h>
#include <sys/time.h>
#include <sablot.h>

#include "tools.h"

SablotSituation parser;
SDOM_Document dom;

void initXML(struct TestData *td) {
    SablotCreateSituation(&parser);
}

void releaseXML(struct TestData *td) {
    SablotDestroySituation(parser);
}


void parseXML(struct TestData *td, unsigned long iter) {
    if (SablotParseBuffer(parser,td->xml,&dom)) {
	printf("Error parsing document!\n");
	exit(1);
    }

    SablotDestroyDocument(parser,dom);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
