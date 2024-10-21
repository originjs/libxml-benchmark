#include <stdio.h>
#include <sys/time.h>
#include <oratypes.h>
#include <oraxml.h>

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

char nsxsi[64]="http://www.w3.org/2001/XMLSchema-instance";
char nsenc[64]="http://www.w3.org/2001/12/soap-encoding";
char nssoap[64]="http://www.w3.org/2001/12/soap-envelope";
char nsopc[64]="http://opcfoundation.org/webservices/OPCDA/";

xmlctx		*ctx;
xmldomimp	*dom;
char 		*mem;

void initXML(struct TestData *td) {
    unsigned int ecode;
    ctx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
    if (!ctx)
    {
        printf("Failed to initialze XML parser, error %u\n", (unsigned) ecode);
        exit(1);
    }
    dom = getImplementation(ctx);
    mem = malloc(memsize);
}

void releaseXML(struct TestData *td) {
    free(mem);
    xmlterm(ctx);
}

void parseXML(struct TestData *td, unsigned long iter) {
    unsigned int ecode;
    xmlnode *doc;
    xmlnode *pnode,*node,*node1,*node2;
    char str[td->inc][16];
    int i;
    
    
    doc=createDocument(ctx);
    pnode=createElementNS(ctx,nssoap,"soap:Envelope");
    appendChild(ctx,doc,pnode);    
    setAttribute(ctx,pnode,"xmlns:soap",nssoap);
    setAttribute(ctx,pnode,"xmlns:xsi",nsxsi);
    setAttribute(ctx,pnode,"xmlns:enc",nsenc);
    node=createElementNS(ctx,nssoap,"soap:Body");
    appendChild(ctx,pnode,node);pnode=node;
    node=createElementNS(ctx,nsopc,"WriteResponse");
    appendChild(ctx,pnode,node);pnode=node;
    node=createElementNS(ctx,nsopc,"WriteResult");
    setAttribute(ctx,node,"RcvTime","2002-04-29T10:16:26.6806250+02:00");
    setAttribute(ctx,node,"ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    setAttribute(ctx,node,"ClientRequestHandle","WriteError");
    setAttribute(ctx,node,"RevisedLocaleID","en");
    setAttribute(ctx,node,"ServerState","running");
    appendChild(ctx,pnode,node);
    node1=createElementNS(ctx,nssoap,"RItemList");
    appendChild(ctx,pnode,node1);
    node=createElementNS(ctx,nssoap,"Errors");
    setAttribute(ctx,node,"ID","E_UNKNOWNITEMID");
    appendChild(ctx,pnode,node);
    node2=createElementNS(ctx,nssoap,"Text");
    appendChild(ctx,node,node2);    
    appendChild(ctx,node2,createTextNode(ctx,"The item does not exist in the server address space."));
    node=createElementNS(ctx,nssoap,"Errors");
    setAttribute(ctx,node,"ID","S_CLAMP");
    appendChild(ctx,pnode,node);
    node2=createElementNS(ctx,nssoap,"Text");
    appendChild(ctx,node,node2);    
    appendChild(ctx,node2,createTextNode(ctx,"The value written was accepted but the output was clamped."));

    pnode=node1;
    node=createElementNS(ctx,nssoap,"Items");
    setAttribute(ctx,node,"ItemPath","");
    setAttribute(ctx,node,"ItemName","WrongItemID1");
    setAttribute(ctx,node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    setAttribute(ctx,node,"ErrorID","E_UNKNOWNITEMID");
    appendChild(ctx,pnode,node);
    node1=createElementNS(ctx,nssoap,"Value");
    appendChild(ctx,node,node1);
    setAttribute(ctx,node1,"xsi:nil","true");

    node=createElementNS(ctx,nssoap,"Items");
    setAttribute(ctx,node,"ItemPath","");
    setAttribute(ctx,node,"ItemName","WrongItemID2");
    setAttribute(ctx,node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    setAttribute(ctx,node,"ErrorID","E_UNKNOWNITEMID");
    appendChild(ctx,pnode,node);
    node1=createElementNS(ctx,nssoap,"Value");
    appendChild(ctx,node,node1);
    setAttribute(ctx,node1,"xsi:nil","true");

    node=createElementNS(ctx,nssoap,"Items");
    setAttribute(ctx,node,"ItemPath","/Reals");
    setAttribute(ctx,node,"ItemName","Float1");
    setAttribute(ctx,node,"ValueType","xsd:float");
    setAttribute(ctx,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    appendChild(ctx,pnode,node);
    node1=createElementNS(ctx,nssoap,"Value");
    appendChild(ctx,node,node1);
    setAttribute(ctx,node1,"xsi:type","xsd:float");
    appendChild(ctx,node1,createTextNode(ctx,"10.0141414"));

    node=createElementNS(ctx,nssoap,"Items");
    setAttribute(ctx,node,"ItemPath","/Reals");
    setAttribute(ctx,node,"ItemName","Float2");
    setAttribute(ctx,node,"ValueType","xsd:float");
    setAttribute(ctx,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    setAttribute(ctx,node,"SuccessID","S_CLAMP");
    appendChild(ctx,pnode,node);
    node1=createElementNS(ctx,nssoap,"Value");
    appendChild(ctx,node,node1);
    setAttribute(ctx,node1,"xsi:type","xsd:float");
    appendChild(ctx,node1,createTextNode(ctx,"1.07"));

    for (i=0;i<td->inc;i++) {
        node=createElementNS(ctx,nssoap,"Items");
	setAttribute(ctx,node,"ItemPath","/Integer");
        setAttribute(ctx,node,"ItemName","IntN");
	setAttribute(ctx,node,"ValueType","xsd:int");
        setAttribute(ctx,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
        setAttribute(ctx,node,"SuccessID","S_CLAMP");
	appendChild(ctx,pnode,node);
        node1=createElementNS(ctx,nssoap,"Value");
	appendChild(ctx,node,node1);
	setAttribute(ctx,node1,"xsi:type","xsd:int");
	sprintf(str[i],"%u",rand());
        appendChild(ctx,node1,createTextNode(ctx,str[i]));
    }

    printBuffer(mem,memsize,doc,0,0);
    
//    if (iter==td->iterations) puts(mem);

//	xmlclean(ctx);
    xmlterm(ctx);
    ctx = xmlinit(&ecode, 0, 0, 0, 0, 0, 0, 0, 0);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
