#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>


#include "transcode.h"
#include "tools.h"

char nsxsi[64]="http://www.w3.org/2001/XMLSchema-instance";
char nsenc[64]="http://www.w3.org/2001/12/soap-encoding";
char nssoap[64]="http://www.w3.org/2001/12/soap-envelope";
char nsopc[64]="http://opcfoundation.org/webservices/OPCDA/";

DOMImplementation *dom; 
DOMWriter *writer;
XMLFormatTarget *xft;

void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
    dom = DOMImplementationRegistry::getDOMImplementation(X("Core"));    
    writer = ((DOMImplementationLS*)dom)->createDOMWriter();
    xft = new MemBufFormatTarget();
}

void releaseXML(struct TestData *td) {
    delete xft;
    delete writer;
    XMLPlatformUtils::Terminate();
}

void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    DOMElement *pnode,*node,*node1,*node2;
    DOMDocument *doc;
    XMLByte *mem;
    char str[16];
    int i;

    doc = dom->createDocument(X(nssoap),X("Envelope"),NULL);
    pnode = doc->getDocumentElement();
    pnode->setAttribute(X("xmlns"),X(nssoap));
    pnode->setAttribute(X("xmlns:xsi"),X(nsxsi));
    pnode->setAttribute(X("xmlns:enc"),X(nsenc));
    node=doc->createElementNS(X(nssoap),X("Body"));
    pnode->appendChild(node); pnode=node;

    node=doc->createElementNS(X(nsopc),X("WriteResponse"));
    pnode->appendChild(node);pnode=node;
    node=doc->createElementNS(X(nsopc),X("WriteResult"));
    node->setAttribute(X("RcvTime"),X("2002-04-29T10:16:26.6806250+02:00"));
    node->setAttribute(X("ReplyTime"),X("2002-04-29T10:16:26.7806250+02:00"));
    node->setAttribute(X("ClientRequestHandle"),X("WriteError"));
    node->setAttribute(X("RevisedLocaleID"),X("en"));
    node->setAttribute(X("ServerState"),X("running"));
    pnode->appendChild(node);
    node1=doc->createElementNS(X(nsopc),X("RItemList"));
    pnode->appendChild(node1);
    node=doc->createElementNS(X(nsopc),X("Errors"));
    node->setAttribute(X("ID"),X("E_UNKNOWNITEMID"));
    pnode->appendChild(node);
    node2=doc->createElementNS(X(nsopc),X("Text"));
    node->appendChild(node2);    
    node2->appendChild(doc->createTextNode(X("The item does not exist in the server address space.")));
    node=doc->createElementNS(X(nsopc),X("Errors"));
    node->setAttribute(X("ID"),X("S_CLAMP"));
    pnode->appendChild(node);
    node2=doc->createElementNS(X(nsopc),X("Text"));
    node->appendChild(node2);    
    node2->appendChild(doc->createTextNode(X("The value written was accepted but the output was clamped.")));

    pnode=node1;
    node=doc->createElementNS(X(nsopc),X("Items"));
    node->setAttribute(X("ItemPath"),X(""));
    node->setAttribute(X("ItemName"),X("WrongItemID1"));
    node->setAttribute(X("Timestamp"),X("0001-01-01T00:00:00.0000000+01:00"));
    node->setAttribute(X("ErrorID"),X("E_UNKNOWNITEMID"));
    pnode->appendChild(node);
    node1=doc->createElementNS(X(nsopc),X("Value"));
    node->appendChild(node1);
    node->setAttribute(X("xsi:nil"),X("true"));

    node=doc->createElementNS(X(nsopc),X("Items"));
    node->setAttribute(X("ItemPath"),X(""));
    node->setAttribute(X("ItemName"),X("WrongItemID2"));
    node->setAttribute(X("Timestamp"),X("0001-01-01T00:00:00.0000000+01:00"));
    node->setAttribute(X("ErrorID"),X("E_UNKNOWNITEMID"));
    pnode->appendChild(node);
    node1=doc->createElementNS(X(nsopc),X("Value"));
    node->appendChild(node1);
    node->setAttribute(X("xsi:nil"),X("true"));

    node=doc->createElementNS(X(nsopc),X("Items"));
    node->setAttribute(X("ItemPath"),X("/Reals"));
    node->setAttribute(X("ItemName"),X("Float1"));
    node->setAttribute(X("ValueType"),X("xsd:float"));
    node->setAttribute(X("Timestamp"),X("2002-04-29T11:47:18.1493750+02:00"));
    pnode->appendChild(node);
    node1=doc->createElementNS(X(nsopc),X("Value"));
    node->appendChild(node1);
    node->setAttribute(X("xsi:type"),X("xsd:float"));
    node1->appendChild(doc->createTextNode(X("10.0141414")));

    node=doc->createElementNS(X(nsopc),X("Items"));
    node->setAttribute(X("ItemPath"),X("/Reals"));
    node->setAttribute(X("ItemName"),X("Float2"));
    node->setAttribute(X("ValueType"),X("xsd:float"));
    node->setAttribute(X("Timestamp"),X("2002-04-29T11:47:18.1493750+02:00"));
    node->setAttribute(X("SuccessID"),X("S_CLAMP"));
    pnode->appendChild(node);
    node1=doc->createElementNS(X(nsopc),X("Value"));
    node->appendChild(node1);
    node->setAttribute(X("xsi:type"),X("xsd:float"));
    node1->appendChild(doc->createTextNode(X("1.07")));
    
    for (i=0;i<td->inc;i++) {
        node=doc->createElementNS(X(nsopc),X("Items"));
	node->setAttribute(X("ItemPath"),X("/Integer"));
        node->setAttribute(X("ItemName"),X("IntN"));
	node->setAttribute(X("ValueType"),X("xsd:int"));
        node->setAttribute(X("Timestamp"),X("2002-04-29T11:47:18.1493750+02:00"));
        node->setAttribute(X("SuccessID"),X("S_CLAMP"));
	pnode->appendChild(node);
        node1=doc->createElementNS(X(nsopc),X("Value"));
	node->appendChild(node1);
	node->setAttribute(X("xsi:type"),X("xsd:int"));
	sprintf(str,"%u",rand());
        node1->appendChild(doc->createTextNode(X(str)));
    }

    writer->writeNode(xft,*doc);
    mem=(XMLByte*)((MemBufFormatTarget*)xft)->getRawBuffer();

//    if (iter==td->iterations) puts((char*)mem);
    ((MemBufFormatTarget*)xft)->reset();
    
    doc->release();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
