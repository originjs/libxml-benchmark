import java.io.*;
import java.util.*;
import java.text.*;
import java.lang.String;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

/*
    Code differs depending on XML Pack used or not!
    Defaults to use with XML Pack!
    For details see forward!
*/


public class sun_dom2 extends bench {
    DocumentBuilderFactory factory;
    DocumentBuilder parser;
    Random generator;
    String nsxsi="http://www.w3.org/2001/XMLSchema-instance";
    String nsenc="http://www.w3.org/2001/12/soap-encoding";
    String nssoap="http://www.w3.org/2001/12/soap-envelope";
    String nsopc="http://opcfoundation.org/webservices/OPCDA/";

    public void InitXML(int enlarge) {
	    factory = DocumentBuilderFactory.newInstance();
	    try {
    		parser = factory.newDocumentBuilder();
	    }
	    catch (Throwable err) {
    		err.printStackTrace ();
	    }
	    if (enlarge>0) generator = new Random();
    }

    public void ParseXML(int enlarge, int iters, int iter) {
	Document doc;
	Element proot,pnode,node,node1,node2;
	String mem="";
	int i;
	
	try {
	    doc = parser.newDocument();
	    proot = doc.createElementNS(nssoap,"Envelope");
	    proot.setAttribute("xmlns",nssoap);
	    proot.setAttribute("xmlns:xsi",nsxsi);
	    proot.setAttribute("xmlns:enc",nsenc);
	    doc.appendChild(proot);
	    pnode = doc.createElementNS(nssoap,"Body");
	    proot.appendChild(pnode);

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
    
    for (i=0;i<enlarge;i++) {
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
        node1.appendChild(doc.createTextNode(Integer.toString(generator.nextInt())));
    }

	// Use this in case of pure J2SE 1.4 used (without XML Pack - Crismon parser)
//	    mem=proot.toString();

	// Use this in case of J2SE 1.4 + XML Pack used (Xerces parser)
//	    org.apache.xerces.dom3.ls.DOMWriter dw = new org.apache.xml.serialize.XMLSerializer();
//	    mem = dw.writeToString(doc);

	// Use this in case of J2SE 1.4 + Java WebService Developer Pack 1.2
	    java.io.StringWriter sw = new StringWriter();
	    org.apache.xml.serialize.XMLSerializer dw = new org.apache.xml.serialize.XMLSerializer(sw,null);
	    dw.serialize(doc);
	    dw.asDOMSerializer();
	    mem = sw.toString();
	    
	}
	catch (Exception e)
	{
    	    System.out.println(e.toString());
	}

//	if (iter==iters) System.out.println(mem);
    }
    

    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom2();
	mybench.Bench(argv);
    }
}