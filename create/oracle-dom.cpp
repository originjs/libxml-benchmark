#include <stdio.h>
#include <sys/time.h>
#include <oraxml.hpp>

#include "tools.h"
#define memsize 65535

/* 
Very strange optimization of library function: setAttribute(node,name,value)
    setAttribute(nodeVar,"name",valueVar); - doesn't copy context of 
    valueVar but simply make a pointer on it. xmlterm() wouldn't free
    this memory.
    But: setAttribute(nodeVar,"name","value"); - works OK, it copies
    context of stack variable.
*/

oratext nsxsi[64]="http://www.w3.org/2001/XMLSchema-instance";
oratext nsenc[64]="http://www.w3.org/2001/12/soap-encoding";
oratext nssoap[64]="http://www.w3.org/2001/12/soap-envelope";
oratext nsopc[64]="http://opcfoundation.org/webservices/OPCDA/";

XMLParser *parser;
char *mem;

void initXML(struct TestData *td) {
    unsigned int ecode;
    parser=new XMLParser;
    ecode=parser->xmlinit();
    if (ecode)
    {
        fprintf(stderr,"Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
    mem = (char*)malloc(memsize);
    if (!mem) {
        fprintf(stderr,"Can't allocate memory!\n");
        exit(1);
    }
	
}

void releaseXML(struct TestData *td) {
    parser->xmlterm();
    delete parser;
    free(mem);
}

void parseXML(struct TestData *td, unsigned long iter) {
    Document *doc;
    Element *pnode,*node,*node1,*node2;
    unsigned int ecode;
    char str[td->inc][16];;
    int i;
    
    doc=parser->createDocument(nssoap,NULL,NULL);
    pnode=doc->createElementNS((oratext*)nssoap,(oratext*)"soap:Envelope");
    doc->appendChild(pnode);    
    pnode->setAttribute((oratext*)"xmlns:soap",(oratext*)nssoap);
    pnode->setAttribute((oratext*)"xmlns:xsi",(oratext*)nsxsi);
    pnode->setAttribute((oratext*)"xmlns:enc",(oratext*)nsenc);
    node=doc->createElementNS(nssoap,(oratext*)"soap:Body");
    pnode->appendChild(node);pnode=node;
    node=doc->createElementNS((oratext*)nsopc,(oratext*)"WriteResponse");
    pnode->appendChild(node);pnode=node;
    node=doc->createElementNS((oratext*)nsopc,(oratext*)"WriteResult");
    node->setAttribute((oratext*)"RcvTime",(oratext*)"2002-04-29T10:16:26.6806250+02:00");
    node->setAttribute((oratext*)"ReplyTime",(oratext*)"2002-04-29T10:16:26.7806250+02:00");
    node->setAttribute((oratext*)"ClientRequestHandle",(oratext*)"WriteError");
    node->setAttribute((oratext*)"RevisedLocaleID",(oratext*)"en");
    node->setAttribute((oratext*)"ServerState",(oratext*)"running");
    pnode->appendChild(node);
    node1=doc->createElementNS((oratext*)nsopc,(oratext*)"RItemList");
    pnode->appendChild(node1);
    node=doc->createElementNS((oratext*)nsopc,(oratext*)"Errors");
    node->setAttribute((oratext*)"ID",(oratext*)"E_UNKNOWNITEMID");
    pnode->appendChild(node);
    node2=doc->createElementNS((oratext*)nsopc,(oratext*)"Text");
    node->appendChild(node2);    
    node2->appendChild(doc->createTextNode((oratext*)"The item does not exist in the server address space."));
    node=doc->createElementNS(nsopc,(oratext*)"Errors");
    node->setAttribute((oratext*)"ID",(oratext*)"S_CLAMP");
    pnode->appendChild(node);
    node2=doc->createElementNS(nsopc,(oratext*)"Text");
    node->appendChild(node2);    
    node2->appendChild(doc->createTextNode((oratext*)"The value written was accepted but the output was clamped."));

    pnode=node1;
    node=doc->createElementNS((oratext*)nsopc,(oratext*)"Items");
    node->setAttribute((oratext*)"ItemPath",(oratext*)"");
    node->setAttribute((oratext*)"ItemName",(oratext*)"WrongItemID1");
    node->setAttribute((oratext*)"Timestamp",(oratext*)"0001-01-01T00:00:00.0000000+01:00");
    node->setAttribute((oratext*)"ErrorID",(oratext*)"E_UNKNOWNITEMID");
    pnode->appendChild(node);
    node1=doc->createElementNS((oratext*)nsopc,(oratext*)"Value");
    node->appendChild(node1);
    node->setAttribute((oratext*)"xsi:nil",(oratext*)"true");

    node=doc->createElementNS((oratext*)nsopc,(oratext*)"Items");
    node->setAttribute((oratext*)"ItemPath",(oratext*)"");
    node->setAttribute((oratext*)"ItemName",(oratext*)"WrongItemID2");
    node->setAttribute((oratext*)"Timestamp",(oratext*)"0001-01-01T00:00:00.0000000+01:00");
    node->setAttribute((oratext*)"ErrorID",(oratext*)"E_UNKNOWNITEMID");
    pnode->appendChild(node);
    node1=doc->createElementNS((oratext*)nsopc,(oratext*)"Value");
    node->appendChild(node1);
    node->setAttribute((oratext*)"xsi:nil",(oratext*)"true");

    node=doc->createElementNS((oratext*)nsopc,(oratext*)"Items");
    node->setAttribute((oratext*)"ItemPath",(oratext*)"/Reals");
    node->setAttribute((oratext*)"ItemName",(oratext*)"Float1");
    node->setAttribute((oratext*)"ValueType",(oratext*)"xsd:float");
    node->setAttribute((oratext*)"Timestamp",(oratext*)"2002-04-29T11:47:18.1493750+02:00");
    pnode->appendChild(node);
    node1=doc->createElementNS((oratext*)nsopc,(oratext*)"Value");
    node->appendChild(node1);
    node->setAttribute((oratext*)"xsi:type",(oratext*)"xsd:float");
    node1->appendChild(doc->createTextNode((oratext*)"10.0141414"));

    node=doc->createElementNS((oratext*)nsopc,(oratext*)"Items");
    node->setAttribute((oratext*)"ItemPath",(oratext*)"/Reals");
    node->setAttribute((oratext*)"ItemName",(oratext*)"Float2");
    node->setAttribute((oratext*)"ValueType",(oratext*)"xsd:float");
    node->setAttribute((oratext*)"Timestamp",(oratext*)"2002-04-29T11:47:18.1493750+02:00");
    node->setAttribute((oratext*)"SuccessID",(oratext*)"S_CLAMP");
    pnode->appendChild(node);
    node1=doc->createElementNS((oratext*)nsopc,(oratext*)"Value");
    node->appendChild(node1);
    node->setAttribute((oratext*)"xsi:type",(oratext*)"xsd:float");
    node1->appendChild(doc->createTextNode((oratext*)"1.07"));
    
    for (i=0;i<td->inc;i++) {
        node=doc->createElementNS((oratext*)nsopc,(oratext*)"Items");
	node->setAttribute((oratext*)"ItemPath",(oratext*)"/Integer");
        node->setAttribute((oratext*)"ItemName",(oratext*)"IntN");
	node->setAttribute((oratext*)"ValueType",(oratext*)"xsd:int");
        node->setAttribute((oratext*)"Timestamp",(oratext*)"2002-04-29T11:47:18.1493750+02:00");
        node->setAttribute((oratext*)"SuccessID",(oratext*)"S_CLAMP");
	pnode->appendChild(node);
        node1=doc->createElementNS((oratext*)nsopc,(oratext*)"Value");
	node->appendChild(node1);
	node->setAttribute((oratext*)"xsi:type",(oratext*)"xsd:int");
	sprintf(str[i],"%u",rand());
        node1->appendChild(doc->createTextNode((oratext*)str[i]));
    }

    doc->print((oratext*)mem,memsize,0,0);
    
//    if (iter+1==td->iterations) puts(mem);

//    parser->xmlclean();
    parser->xmlterm();
    parser->xmlinit();
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
