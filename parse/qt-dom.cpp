#include <stdio.h>
#include <sys/time.h>
#include <qxml.h>
#include <qwindowdefs.h>
#include <qstring.h>
#include <qcstring.h>
#include <qdom.h>

#include "tools.h"

QByteArray *qba;

void initXML(struct TestData *td) {
    qba=new QByteArray;
}

void releaseXML(struct TestData *td) {
    delete qba;
}


void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    static QDomDocument *parser;
    
    parser = new QDomDocument;
    qba->setRawData(td->xml,td->xmllen);
    parser->setContent(*qba,FALSE);
    qba->resetRawData(td->xml,td->xmllen);
    delete parser;
}



int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
