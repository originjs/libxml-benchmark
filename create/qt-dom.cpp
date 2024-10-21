#include <stdio.h>
#include <sys/time.h>
#include <qxml.h>
#include <qwindowdefs.h>
#include <qstring.h>
#include <qcstring.h>
#include <qdom.h>

#include "tools.h"


QString prefix="<?xml version=\"1.0\"?>";

QString nsxsi="http://www.w3.org/2001/XMLSchema-instance";
QString nsenc="http://www.w3.org/2001/12/soap-encoding";
QString nssoap="http://www.w3.org/2001/12/soap-envelope";
QString nsopc="http://opcfoundation.org/webservices/OPCDA/";

void initXML(struct TestData *td) {
}

void releaseXML(struct TestData *td) {
}

void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    QDomDocument doc;
    QDomElement pnode,node,node1,node2;
    QString mem;
    char str[16];
    int i;
    
    pnode=doc.createElementNS(nssoap,"soap:Envelope");
    doc.appendChild(pnode);
    pnode.setAttribute("xmlns:xsi",nsxsi);
    pnode.setAttribute("xmlns:enc",nsenc);
    node=doc.createElementNS(nssoap,"Body");
    node.setPrefix("soap");
    pnode.appendChild(node);pnode=node;

    node=doc.createElementNS(nsopc,"WriteResponse");
    pnode.appendChild(node);pnode=node;
    node=doc.createElementNS(nsopc,"WriteResult");
    node.setAttribute("RcvTime","2002-04-29T10:16:26.6806250+02:00");
    node.setAttribute("ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    node.setAttribute("ClientRequestHandle","WriteError");
    node.setAttribute("RevisedLocaleID","en");
    node.setAttribute("ServerState","running");
    pnode.appendChild(node);
    node1=doc.createElementNS(nsopc,"RItemList");
    pnode.appendChild(node1);
    node=doc.createElementNS(nsopc,"Errors");
    node.setAttribute("ID","E_UNKNOWNITEMID");
    pnode.appendChild(node);
    node2=doc.createElementNS(nsopc,"Text");
    node.appendChild(node2);    
    node2.appendChild(doc.createTextNode("The item does not exist in the server address space."));
    node=doc.createElementNS(nsopc,"Errors");
    node.setAttribute("ID","S_CLAMP");
    pnode.appendChild(node);
    node2=doc.createElementNS(nsopc,"Text");
    node.appendChild(node2);    
    node2.appendChild(doc.createTextNode("The value written was accepted but the output was clamped."));

    pnode=node1;
    node=doc.createElementNS(nsopc,"Items");
    node.setAttribute("ItemPath","");
    node.setAttribute("ItemName","WrongItemID1");
    node.setAttribute("Timestamp","0001-01-01T00:00:00.0000000+01:00");
    node.setAttribute("ErrorID","E_UNKNOWNITEMID");
    pnode.appendChild(node);
    node1=doc.createElementNS(nsopc,"Value");
    node.appendChild(node1);
    node.setAttribute("xsi:nil","true");

    node=doc.createElementNS(nsopc,"Items");
    node.setAttribute("ItemPath","");
    node.setAttribute("ItemName","WrongItemID2");
    node.setAttribute("Timestamp","0001-01-01T00:00:00.0000000+01:00");
    node.setAttribute("ErrorID","E_UNKNOWNITEMID");
    pnode.appendChild(node);
    node1=doc.createElementNS(nsopc,"Value");
    node.appendChild(node1);
    node.setAttribute("xsi:nil","true");

    node=doc.createElementNS(nsopc,"Items");
    node.setAttribute("ItemPath","/Reals");
    node.setAttribute("ItemName","Float1");
    node.setAttribute("ValueType","xsd:float");
    node.setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
    pnode.appendChild(node);
    node1=doc.createElementNS(nsopc,"Value");
    node.appendChild(node1);
    node.setAttribute("xsi:type","xsd:float");
    node1.appendChild(doc.createTextNode("10.0141414"));

    node=doc.createElementNS(nsopc,"Items");
    node.setAttribute("ItemPath","/Reals");
    node.setAttribute("ItemName","Float2");
    node.setAttribute("ValueType","xsd:float");
    node.setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
    node.setAttribute("SuccessID","S_CLAMP");
    pnode.appendChild(node);
    node1=doc.createElementNS(nsopc,"Value");
    node.appendChild(node1);
    node.setAttribute("xsi:type","xsd:float");
    node1.appendChild(doc.createTextNode("1.07"));
    
    for (i=0;i<td->inc;i++) {
        node=doc.createElementNS(nsopc,"Items");
	node.setAttribute("ItemPath","/Integer");
        node.setAttribute("ItemName","IntN");
	node.setAttribute("ValueType","xsd:int");
        node.setAttribute("Timestamp","2002-04-29T11:47:18.1493750+02:00");
        node.setAttribute("SuccessID","S_CLAMP");
	pnode.appendChild(node);
        node1=doc.createElementNS(nsopc,"Value");
	node.appendChild(node1);
	node.setAttribute("xsi:type","xsd:int");
	sprintf(str,"%u",rand());
        node1.appendChild(doc.createTextNode(str));
    }

    mem=doc.toString();
    
//    if (iter==td->iterations) cout<<prefix<<mem;

}



int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
