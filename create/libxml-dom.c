#include <stdio.h>
#include <sys/time.h>
#include <gdome.h>

#include "tools.h"

GdomeDocument *doc;

void ds_xmlSetProp(GdomeNode *node, char *nm, char *val) {
    GdomeDOMString *dstr_nm, *dstr_val;
    GdomeException exc;
    dstr_nm=gdome_str_mkref_dup(nm);
    dstr_val=gdome_str_mkref_dup(val);
    gdome_el_setAttribute((GdomeElement*)node,dstr_nm,dstr_val,&exc);
    gdome_str_unref(dstr_nm);
    gdome_str_unref(dstr_val);
}

GdomeNode *ds_xmlNewChild(GdomeNode *node, char *nm, char *title, char *text) {
    GdomeDOMString *dstr;
    GdomeNode *rnode;
    GdomeException exc;

    dstr = gdome_str_mkref_dup(title);
    rnode=(GdomeNode*)gdome_doc_createElement(doc,dstr,&exc);
    gdome_str_unref(dstr);
    gdome_n_appendChild(node,(GdomeNode*)rnode,&exc);
    if (text) {
	dstr = gdome_str_mkref_dup(text);
	gdome_n_appendChild(rnode,(GdomeNode*)gdome_doc_createTextNode(doc,dstr,&exc),&exc);
	gdome_str_unref(dstr);
    }

    return rnode;
}

GdomeDOMImplementation *di;

void initXML(struct TestData *td) {
    di=gdome_di_mkref();
}

void releaseXML(struct TestData *td) {
    GdomeException exc;
    gdome_di_unref(di,&exc);
}

void parseXML(struct TestData *td, unsigned long iter) {
    GdomeNode *pnode,*node,*node1;
    GdomeException exc;
    GdomeDOMString *dstr;
    char *mem;
    char s[16];
    int i;

    dstr = gdome_str_mkref_dup("Envelope");
    doc=gdome_di_createDocument(di,NULL,dstr,NULL,&exc); gdome_str_unref(dstr); 
    pnode=(GdomeNode*)gdome_doc_documentElement(doc,&exc); 
    ds_xmlSetProp(pnode,"xmlns","http://www.w3.org/2001/12/soap-envelope");
    ds_xmlSetProp(pnode,"xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    ds_xmlSetProp(pnode,"xmlns:enc","http://www.w3.org/2001/12/soap-encoding");
    node=ds_xmlNewChild(pnode,NULL,"Body",NULL);
    pnode=ds_xmlNewChild(pnode,NULL,"WriteResponse",NULL);
    ds_xmlSetProp(pnode,"xmlns","http://opcfoundation.org/webservices/OPCDA/");
    node=ds_xmlNewChild(pnode,NULL,"WriteResult",NULL);
    ds_xmlSetProp(node,"RcvTime","2002-04-29T10:16:26.6806250+02:00");
    ds_xmlSetProp(node,"ReplyTime","2002-04-29T10:16:26.7806250+02:00");
    ds_xmlSetProp(node,"ClientRequestHandle","WriteError");
    ds_xmlSetProp(node,"RevisedLocaleID","en");
    ds_xmlSetProp(node,"ServerState","running");
    node1=ds_xmlNewChild(pnode,NULL,"RItemList",NULL);
    node=ds_xmlNewChild(pnode,NULL,"Errors",NULL);
    ds_xmlSetProp(node,"ID","E_UNKNOWNITEMID");
    ds_xmlNewChild(node,NULL,"Text","The item does not exist in the server address space.");
    node=ds_xmlNewChild(pnode,NULL,"Errors",NULL);
    ds_xmlSetProp(node,"ID","S_CLAMP");
    ds_xmlNewChild(node,NULL,"Text","The value written was accepted but the output was clamped.");

    pnode=node1;
    node=ds_xmlNewChild(pnode,NULL,"Items",NULL);
    ds_xmlSetProp(node,"ItemPath","");
    ds_xmlSetProp(node,"ItemName","WrongItemID1");
    ds_xmlSetProp(node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    ds_xmlSetProp(node,"ErrorID","E_UNKNOWNITEMID");
    node1=ds_xmlNewChild(node,NULL,"Value",NULL);
    ds_xmlSetProp(node1,"xsi:nil","true");

    node=ds_xmlNewChild(pnode,NULL,"Items",NULL);
    ds_xmlSetProp(node,"ItemPath","");
    ds_xmlSetProp(node,"ItemName","WrongItemID2");
    ds_xmlSetProp(node,"Timestamp","0001-01-01T00:00:00.0000000+01:00");
    ds_xmlSetProp(node,"ErrorID","E_UNKNOWNITEMID");
    node1=ds_xmlNewChild(node,NULL,"Value",NULL);
    ds_xmlSetProp(node1,"xsi:nil","true");

    node=ds_xmlNewChild(pnode,NULL,"Items",NULL);
    ds_xmlSetProp(node,"ItemPath","/Reals");
    ds_xmlSetProp(node,"ItemName","Float1");
    ds_xmlSetProp(node,"ValueType","xsd:float");
    ds_xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    node1=ds_xmlNewChild(node,NULL,"Value","10.0141414");
    ds_xmlSetProp(node1,"xsi:type","xsd:float");

    node=ds_xmlNewChild(pnode,NULL,"Items",NULL);
    ds_xmlSetProp(node,"ItemPath","/Reals");
    ds_xmlSetProp(node,"ItemName","Float2");
    ds_xmlSetProp(node,"ValueType","xsd:float");
    ds_xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
    ds_xmlSetProp(node,"SuccessID","S_CLAMP");
    node1=ds_xmlNewChild(node,NULL,"Value","1.07");
    ds_xmlSetProp(node1,"xsi:type","xsd:float");

    for (i=0;i<td->inc;i++) {
	node=ds_xmlNewChild(pnode,NULL,"Items",NULL);
	ds_xmlSetProp(node,"ItemPath","/Integer");
        ds_xmlSetProp(node,"ItemName","IntN");
	ds_xmlSetProp(node,"ValueType","xsd:int");
        ds_xmlSetProp(node,"Timestamp","2002-04-29T11:47:18.1493750+02:00");
        ds_xmlSetProp(node,"SuccessID","S_CLAMP");
	sprintf(s,"%u",rand());
	node1=ds_xmlNewChild(node,NULL,"Value",s);
        ds_xmlSetProp(node1,"xsi:type","xsd:int");
    }

    gdome_di_saveDocToMemory(di,doc,&mem,0,&exc);
    gdome_di_freeDoc(di,doc,&exc);
    
//    if (iter==td->iterations) puts(mem);
    free(mem);
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
