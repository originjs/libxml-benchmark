#include <stdio.h>
#include <sys/time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "tools.h"

void initXML(struct TestData *td) {
    xmlInitParser();
}

void releaseXML(struct TestData *td) {
	xmlCleanupParser();
}

void parseXML(struct TestData *td, unsigned long iter) {
    xmlDocPtr doc;
    xmlNodePtr pnode,node,node1;
    xmlNsPtr ns1,ns2;
    xmlChar *mem;
    int memsize;
    char s[16];
    int i;
    
    doc = xmlNewDoc("1.0");
    pnode = xmlNewChild((xmlNodePtr)doc,NULL,"Envelope",NULL);
    xmlNewNs(pnode,"http://www.w3.org/2001/12/soap-envelope",NULL);
    ns1=xmlNewNs(pnode,"http://www.w3.org/2001/XMLSchema-instance","xsi");
    ns2=xmlNewNs(pnode,"http://www.w3.org/2001/12/soap-encoding","enc");
    pnode=xmlNewChild(pnode,NULL,"Body",NULL);
    pnode=xmlNewChild(pnode,NULL,"WriteResponse",NULL);
    xmlNewNs(pnode,"http://opcfoundation.org/webservices/OPCDA/",NULL);
    node=xmlNewChild(pnode,NULL,"WriteResult",NULL);
    xmlSetProp(node,"RcvTime","2002-04-29T10:16:26.6806250+02:00");
    xmlSetProp(node,"ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    xmlSetProp(node,"ClientRequestHandle","WriteError");
    xmlSetProp(node,"RevisedLocaleID","en");
    xmlSetProp(node,"ServerState","running");
    node1=xmlNewChild(pnode,NULL,"RItemList",NULL);
    node=xmlNewChild(pnode,NULL,"Errors",NULL);
    xmlSetProp(node,"ID","E_UNKNOWNITEMID");
    xmlNewChild(node,NULL,"Text","The item does not exist in the server address space.");
    node=xmlNewChild(pnode,NULL,"Errors",NULL);
    xmlSetProp(node,"ID","S_CLAMP");
    xmlNewChild(node,NULL,"Text","The value written was accepted but the output was clamped.");

    pnode=node1;
    node=xmlNewChild(pnode,NULL,"Items",NULL);
    xmlSetProp(node,"ItemPath","");
    xmlSetProp(node,"ItemName","WrongItemID1");
    xmlSetProp(node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    xmlSetProp(node,"ErrorID","E_UNKNOWNITEMID");
    node1=xmlNewChild(node,NULL,"Value",NULL);
    xmlSetProp(node1,"xsi:nil","true");

    node=xmlNewChild(pnode,NULL,"Items",NULL);
    xmlSetProp(node,"ItemPath","");
    xmlSetProp(node,"ItemName","WrongItemID2");
    xmlSetProp(node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    xmlSetProp(node,"ErrorID","E_UNKNOWNITEMID");
    node1=xmlNewChild(node,NULL,"Value",NULL);
    xmlSetProp(node1,"xsi:nil","true");

    node=xmlNewChild(pnode,NULL,"Items",NULL);
    xmlSetProp(node,"ItemPath","/Reals");
    xmlSetProp(node,"ItemName","Float1");
    xmlSetProp(node,"ValueType","xsd:float");
    xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    node1=xmlNewChild(node,NULL,"Value","10.0141414");
    xmlSetNsProp(node1,ns1,"type","xsd:float");

    node=xmlNewChild(pnode,NULL,"Items",NULL);
    xmlSetProp(node,"ItemPath","/Reals");
    xmlSetProp(node,"ItemName","Float2");
    xmlSetProp(node,"ValueType","xsd:float");
    xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    xmlSetProp(node,"SuccessID","S_CLAMP");
    node1=xmlNewChild(node,NULL,"Value","1.07");
    xmlSetNsProp(node1,ns1,"type","xsd:float");

    for (i=0;i<td->inc;i++) {
	node=xmlNewChild(pnode,NULL,"Items",NULL);
	xmlSetProp(node,"ItemPath","/Integer");
        xmlSetProp(node,"ItemName","IntN");
	xmlSetProp(node,"ValueType","xsd:int");
        xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
        xmlSetProp(node,"SuccessID","S_CLAMP");
	sprintf(s,"%u",rand());
	node1=xmlNewChild(node,NULL,"Value",s);
        xmlSetNsProp(node1,ns1,"type","xsd:int");
    }

    xmlDocDumpMemory(doc,&mem,&memsize);
    xmlFreeDoc(doc);    

//    if (iter==td->iterations) puts(mem);
    free(mem);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
