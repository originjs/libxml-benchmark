#include <stdio.h>
#include <sys/time.h>
#include <expat.h>

#include "tools.h"

void starttag(void *UserData, const XML_Char *name, const XML_Char **attrs) {
    return;
}

void endtag(void *UserData, const XML_Char *name) {
    return;
}

void texttag(void *UserData, const XML_Char *data, int len) {
    /* Isn't NULL terminated! Data can be splited in several calls! */
    return;
}

XML_Parser doc;

void initXML(struct TestData *td) {
    doc=XML_ParserCreate(NULL);
    XML_SetStartElementHandler(doc,&starttag);
    XML_SetEndElementHandler(doc,&endtag);
    XML_SetCharacterDataHandler(doc,&texttag);
}

void releaseXML(struct TestData *td) {
    XML_ParserFree(doc);
}

void parseXML(struct TestData *td, unsigned long iter) {
    enum XML_Status status;

    status=XML_Parse(doc,td->xml,td->xmllen,1);

    if (status!=XML_STATUS_OK) {
	printf("Error parsing XML!\n");
	exit(1);
    }

    if (XML_ParserReset(doc,NULL)==XML_FALSE) {
        printf("Error reinitialising XML parser!\n");
        exit(1);
    }
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
