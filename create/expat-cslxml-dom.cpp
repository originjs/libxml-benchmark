#include <stdio.h>
#include <sys/time.h>
#include <sstream>

#include <DOMWriter.h>
#include <DOM/DOMImplementation.h>
#include <DOM/Document.h>
#include <DOM/Element.h>
#include "DOM/Text.h"
#include <XMLStream.h>

#include "tools.h"

using namespace CSL::XML;

DOMWriter *writer;
DOMImplementation *parser;

void initXML(struct TestData *td) {
    writer = new DOMWriter;
    parser = DOMImplementation::getInstance();
//	parser->setFeature("namespaces", false);                    // turn off namespace support
//	parser->setFeature("white-space-in-element-content", true); // do not remove ignorable whitespace

}

void releaseXML(struct TestData *td) {
    delete writer;
}

void parseXML(struct TestData *td, unsigned long iter) {
    Document *doc;
    ostringstream os;
    Element *pnode, *node, *node1, *node2;
    char s[16];
    int i;

    doc = parser->createDocument("http://www.w3.org/2001/12/soap-envelope", "Envelope", NULL);    
    pnode = doc->getDocumentElement();
    pnode->setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    pnode->setAttribute("xmlns:enc","http://www.w3.org/2001/12/soap-encoding");
    node=doc->createElement("Body");
    pnode->appendChild(node)->release(); pnode=node;
    node=doc->createElementNS("http://opcfoundation.org/webservices/OPCDA/","WriteResponse");
    pnode->appendChild(node)->release(); pnode=node;
    node=doc->createElement("WriteResult");
    node->setAttribute("RcvTime","2002-04-29T10:16:26.6806250+02:00");
    node->setAttribute("ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    node->setAttribute("ClientRequestHandle","WriteError");
    node->setAttribute("RevisedLocaleID","en");
    node->setAttribute("ServerState","running");
    pnode->appendChild(node)->release();
    node1=doc->createElement("RItemList");
    pnode->appendChild(node1)->release();
    node=doc->createElement("Errors");
    node->setAttribute("ID","E_UNKNOWNITEMID");
    pnode->appendChild(node)->release();
    node2=doc->createElement("Text");
    node->appendChild(node2)->release();
    node2->appendChild(doc->createTextNode("The item does not exist in the server address space."))->release();
    node=doc->createElement("Errors");
    node->setAttribute("ID","S_CLAMP");
    pnode->appendChild(node)->release();
    node2=doc->createElement("Text");
    node->appendChild(node2)->release();
    node->appendChild(doc->createTextNode("The value written was accepted but the output was clamped."))->release();

    pnode=node1;
    node=doc->createElement("Items");
    node->setAttribute("ItemPath","");
    node->setAttribute("ItemName","WrongItemID1");
    node->setAttribute("Timestamp","0001-01-01T00:00:00.0000000+01:00");
    node->setAttribute("ErrorID","E_UNKNOWNITEMID");
    pnode->appendChild(node)->release();
    node1=doc->createElement("Value");
    node->appendChild(node1)->release();
    node1->setAttribute("xsi:nil","true");

    node=doc->createElement("Items");
    node->setAttribute("ItemPath","");
    node->setAttribute("ItemName","WrongItemID2");
    node->setAttribute("Timestamp","0001-01-01T00:00:00.0000000+01:00");
    node->setAttribute("ErrorID","E_UNKNOWNITEMID");
    pnode->appendChild(node)->release();
    node1=doc->createElement("Value");
    node->appendChild(node1)->release();
    node1->setAttribute("xsi:nil","true");

    node=doc->createElement("Items");
    node->setAttribute("ItemPath","/Reals");
    node->setAttribute("ItemName","Float1");
    node->setAttribute("ValueType","xsd:float");
    node->setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
    pnode->appendChild(node)->release();
    node1=doc->createElement("Value");
    node->appendChild(node1)->release();
    node1->setAttribute("xsi:type","xsd:float");
    node1->appendChild(doc->createTextNode("10.0141414"));

    node=doc->createElement("Items");
    node->setAttribute("ItemPath","/Reals");
    node->setAttribute("ItemName","Float2");
    node->setAttribute("ValueType","xsd:float");
    node->setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
    node->setAttribute("SuccessID","S_CLAMP");
    pnode->appendChild(node)->release();
    node1=doc->createElement("Value");
    node->appendChild(node1)->release();
    node1->setAttribute("xsi:type","xsd:float");
    node1->appendChild(doc->createTextNode("1.07"));

    for (i=0;i<td->inc;i++) {
        node=doc->createElement("Items");
	node->setAttribute("ItemPath","/Integer");
        node->setAttribute("ItemName","IntN");
	node->setAttribute("ValueType","xsd:int");
        node->setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
        node->setAttribute("SuccessID","S_CLAMP");
	pnode->appendChild(node)->release();
        node1=doc->createElement("Value");
	node->appendChild(node1);
	node1->setAttribute("xsi:type","xsd:int");
	sprintf(s,"%u",rand());
	node1->appendChild(doc->createTextNode(s));
    }

    writer->writeNode(&os,doc);
//    if (iter==td->iterations) cout<<os.str();
    doc->release();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
