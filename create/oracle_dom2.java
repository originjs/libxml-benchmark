import java.io.*;
import java.util.*;
import java.text.*;
import java.lang.String;
import oracle.xml.parser.v2.XMLDocument;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

public class oracle_dom2 extends bench {
    String nsxsi="http://www.w3.org/2001/XMLSchema-instance";
    String nsenc="http://www.w3.org/2001/12/soap-encoding";
    String nssoap="http://www.w3.org/2001/12/soap-envelope";
    String nsopc="http://opcfoundation.org/webservices/OPCDA/";
    Random generator;

    public void InitXML(int enlarge) {
	if (enlarge>0) generator = new Random();
    }

    public void ParseXML(int enlarge, int iters, int iter) {
	XMLDocument doc;
	Element proot,pnode,node,node1,node2;
	ByteArrayOutputStream mem = new ByteArrayOutputStream();
	int i;
	
	try {
	    doc = new XMLDocument();
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
	    doc.print(mem);
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }

//	if (iter==iters) System.out.println(mem);
    }

    static public void main(String argv[]) throws IOException {
	bench mybench = new oracle_dom2();
	mybench.Bench(argv);
    }
    
}