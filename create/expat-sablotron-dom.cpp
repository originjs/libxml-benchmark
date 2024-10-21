#include <stdio.h>
#include <sys/time.h>
#include <sablot.h>
#include <sdom.h>

#include "tools.h"

SablotSituation *parser;

void initXML(struct TestData *td) {
    parser = new SablotSituation;
    SablotCreateSituation(parser);
}

void releaseXML(struct TestData *td) {
    SablotDestroySituation(*parser);
    delete parser;
}


void parseXML(struct TestData *td, unsigned long iter) {
    SDOM_Document dom;
    SDOM_Node pnode,node,tnode,node1,node2;
    SDOM_char *xmldoc;
    char s[16];
    unsigned long i;

    SablotCreateDocument(*parser, &dom);
    SDOM_createElementNS(*parser,dom,&pnode,"http://www.w3.org/2001/12/soap-envelope","Envelope");
    SDOM_appendChild(*parser,dom,pnode);
//    SDOM_setAttribute(*parser,pnode,"xmlns:soap","http://www.w3.org/2001/12/soap-envelope");
    SDOM_setAttribute(*parser,pnode,"xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    SDOM_setAttribute(*parser,pnode,"xmlns:enc","http://www.w3.org/2001/12/soap-encoding");
    SDOM_createElement(*parser,dom,&node,"Body");
    SDOM_appendChild(*parser,pnode,node); pnode=node;
    SDOM_createElementNS(*parser,dom,&node,"http://opcfoundation.org/webservices/OPCDA/","WriteResponse");
    SDOM_appendChild(*parser,pnode,node); pnode=node;
    SDOM_createElement(*parser,dom,&node,"WriteResult");
    SDOM_setAttribute(*parser,node,"RcvTime","2002-04-29T10:16:26.6806250+02:00");
    SDOM_setAttribute(*parser,node,"ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    SDOM_setAttribute(*parser,node,"ClientRequestHandle","WriteError");
    SDOM_setAttribute(*parser,node,"RevisedLocaleID","en");
    SDOM_setAttribute(*parser,node,"ServerState","running");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node1,"RItemList");
    SDOM_appendChild(*parser,pnode,node1);
    SDOM_createElement(*parser,dom,&node,"Errors");
    SDOM_setAttribute(*parser,node,"ID","E_UNKNOWNITEMID");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node2,"Text");
    SDOM_appendChild(*parser,node,node2);    
    SDOM_createTextNode(*parser,dom,&tnode,"The item does not exist in the server address space.");
    SDOM_appendChild(*parser,node2,tnode);
    SDOM_createElement(*parser,dom,&node,"Errors");
    SDOM_setAttribute(*parser,node,"ID","S_CLAMP");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node2,"Text");
    SDOM_appendChild(*parser,node,node2);    
    SDOM_createTextNode(*parser,dom,&tnode,"The value written was accepted but the output was clamped.");
    SDOM_appendChild(*parser,node2,tnode);

    pnode=node1;
    SDOM_createElement(*parser,dom,&node,"Items");
    SDOM_setAttribute(*parser,node,"ItemPath","");
    SDOM_setAttribute(*parser,node,"ItemName","WrongItemID1");
    SDOM_setAttribute(*parser,node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    SDOM_setAttribute(*parser,node,"ErrorID","E_UNKNOWNITEMID");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node1,"Value");
    SDOM_appendChild(*parser,node,node1);
    SDOM_setAttribute(*parser,node1,"xsi:nil","true");

    SDOM_createElement(*parser,dom,&node,"Items");
    SDOM_setAttribute(*parser,node,"ItemPath","");
    SDOM_setAttribute(*parser,node,"ItemName","WrongItemID2");
    SDOM_setAttribute(*parser,node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    SDOM_setAttribute(*parser,node,"ErrorID","E_UNKNOWNITEMID");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node1,"Value");
    SDOM_appendChild(*parser,node,node1);
    SDOM_setAttribute(*parser,node1,"xsi:nil","true");

    SDOM_createElement(*parser,dom,&node,"Items");
    SDOM_setAttribute(*parser,node,"ItemPath","/Reals");
    SDOM_setAttribute(*parser,node,"ItemName","Float1");
    SDOM_setAttribute(*parser,node,"ValueType","xsd:float");
    SDOM_setAttribute(*parser,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node1,"Value");
    SDOM_appendChild(*parser,node,node1);
    SDOM_setAttribute(*parser,node1,"xsi:type","xsd:float");
    SDOM_createTextNode(*parser,dom,&tnode,"10.0141414");
    SDOM_appendChild(*parser,node1,tnode);

    SDOM_createElement(*parser,dom,&node,"Items");
    SDOM_setAttribute(*parser,node,"ItemPath","/Reals");
    SDOM_setAttribute(*parser,node,"ItemName","Float2");
    SDOM_setAttribute(*parser,node,"ValueType","xsd:float");
    SDOM_setAttribute(*parser,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    SDOM_setAttribute(*parser,node,"SuccessID","S_CLAMP");
    SDOM_appendChild(*parser,pnode,node);
    SDOM_createElement(*parser,dom,&node1,"Value");
    SDOM_appendChild(*parser,node,node1);
    SDOM_setAttribute(*parser,node1,"xsi:type","xsd:float");
    SDOM_createTextNode(*parser,dom,&tnode,"1.07");
    SDOM_appendChild(*parser,node1,tnode);
    
    for (i=0;i<td->inc;i++) {
        SDOM_createElement(*parser,dom,&node,"Items");
	SDOM_setAttribute(*parser,node,"ItemPath","/Integer");
        SDOM_setAttribute(*parser,node,"ItemName","IntN");
	SDOM_setAttribute(*parser,node,"ValueType","xsd:int");
        SDOM_setAttribute(*parser,node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
        SDOM_setAttribute(*parser,node,"SuccessID","S_CLAMP");
	SDOM_appendChild(*parser,pnode,node);
        SDOM_createElement(*parser,dom,&node1,"Value");
	SDOM_appendChild(*parser,node,node1);
	SDOM_setAttribute(*parser,node1,"xsi:type","xsd:int");
	sprintf(s,"%u",rand());
        SDOM_createTextNode(*parser,dom,&tnode,s);
        SDOM_appendChild(*parser,node1,tnode);
    }
    
    SDOM_docToString(*parser,dom,&xmldoc);
//    if (iter==td->iterations) puts(xmldoc);
    free(xmldoc);
    SablotDestroyDocument(*parser,dom);
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
