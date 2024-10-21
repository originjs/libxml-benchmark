#include <stdio.h>
#include <sys/time.h>
#include <gdome.h>

#include "tools.h"

GdomeDOMImplementation *di;

void initXML(struct TestData *td) {
    di=gdome_di_mkref();
}

void releaseXML(struct TestData *td) {
    GdomeException exc;
    gdome_di_unref(di,&exc);
}

void parseXML(struct TestData *td, unsigned long iter) {
    GdomeDocument *doc;
    GdomeException exc;

    doc = gdome_di_createDocFromMemory(di,td->xml,GDOME_LOAD_PARSING,&exc);
    if (!doc) {
        printf("Error parsing document: %d!\n",exc);
        exit(0);
    }

    gdome_di_freeDoc(di,doc,&exc);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
