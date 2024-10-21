#include <stdio.h>
#include <sys/time.h>
#include <qxml.h>
#include <qwindowdefs.h>
#include <qstring.h>
#include <qcstring.h>

#include "tools.h"

class DocHandlers : public QXmlDefaultHandler {
 public:
    bool startElement(const QString namespaceURI, const QString localName, const QString qName, const QXmlAttributes attrs);
    bool endElement(const QString namespaceURI, const QString localName, const QString qName);
    bool characters(const QString text);
};


bool DocHandlers::startElement(const QString namespaceURI, const QString localName, const QString qName, const QXmlAttributes attrs) {
    return TRUE;
}

bool DocHandlers::endElement(const QString namespaceURI, const QString localName, const QString qName) {  
    return TRUE;
}

bool DocHandlers::characters(const QString text) {
    return TRUE;
}

QByteArray *qba;
DocHandlers *handler;
QXmlSimpleReader *parser;

void initXML(struct TestData *td) {
    qba = new QByteArray;
    parser = new QXmlSimpleReader;
    handler = new DocHandlers;
    parser->setContentHandler(handler);
}

void releaseXML(struct TestData *td) {
    delete parser;
    delete handler;
    delete qba;
}

void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    QXmlInputSource *qis;
    
    qba->setRawData(td->xml,td->xmllen);
    qis = new QXmlInputSource;
    qis->setData(*qba);
    parser->parse(qis);
    delete qis;
    qba->resetRawData(td->xml,td->xmllen);
}



int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
