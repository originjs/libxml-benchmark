import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 
import org.w3c.dom.*;

import java.security.*;
import java.security.cert.*;

import org.apache.xml.security.algorithms.MessageDigestAlgorithm;
import org.apache.xml.security.c14n.*;
import org.apache.xml.security.exceptions.XMLSecurityException;
import org.apache.xml.security.signature.*;
import org.apache.xml.security.keys.*;
import org.apache.xml.security.keys.content.*;
import org.apache.xml.security.keys.content.x509.*;
import org.apache.xml.security.keys.keyresolver.*;
import org.apache.xml.security.keys.storage.*;
import org.apache.xml.security.keys.storage.implementations.*;
import org.apache.xml.security.utils.*;
import org.apache.xml.security.transforms.*;
import org.apache.xml.security.transforms.params.XPathContainer;
import org.apache.xml.security.Init;
import org.apache.xml.serialize.*;

import org.apache.xml.security.algorithms.encryption.*;
import org.apache.xml.security.encryption.EncryptedData;
import org.apache.xml.security.encryption.CipherData;
import org.apache.xml.security.encryption.EncryptionProperties;

import org.apache.xpath.XPathAPI;

public class sun_dom3 extends bench {
    DocumentBuilderFactory factory;
    DocumentBuilder parser;
    Document doc;
    XMLSignature sig;
    KeyPair key;
    
    public void InitXML() {
	    KeyPairGenerator kpg;
	    factory = DocumentBuilderFactory.newInstance();
	    factory.setNamespaceAware(true);
	    factory.setValidating(false);
	    try {
    		parser = factory.newDocumentBuilder();
		kpg = KeyPairGenerator.getInstance("RSA");
		key = kpg.genKeyPair();
	    }
	    catch (Throwable err) {
    		err.printStackTrace ();
		return;
	    }

    }
    
    public void InitXML_Security() {
	org.apache.xml.security.Init.init();
    }

    
    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    doc=parser.parse(is);
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
    }

    public void SignXML(FileInputStream is, int iters, int iter) {
	Element root;
	
	try {
	    sig = new XMLSignature(doc,"", XMLSignature.ALGO_ID_SIGNATURE_RSA);
	    root=doc.getDocumentElement();
	    root.appendChild(sig.getElement());
	    Transforms transforms = new Transforms(doc);
	    transforms.addTransform(Transforms.TRANSFORM_ENVELOPED_SIGNATURE);
	    transforms.addTransform(Transforms.TRANSFORM_C14N_WITH_COMMENTS);
	    sig.addDocument("", transforms, Constants.ALGO_ID_DIGEST_SHA1);
	    sig.sign(key.getPrivate());
	}
	catch (Exception e) {	
	    System.err.println(e.toString());
	}
/*
	org.apache.xerces.dom3.ls.DOMWriter dw = new org.apache.xml.serialize.XMLSerializer();
	String mem = dw.writeToString(doc);
	System.out.println(mem);
*/
    }

    public void VerifyXML(FileInputStream is, int iters, int iter) {
/*
	doc.getDocumentElement().appendChild(doc.createElement("test"));
*/
	try {
	    Element nscontext = XMLUtils.createDSctx(doc, "ds", Constants.SignatureSpecNS);
	    Element root=(Element) XPathAPI.selectSingleNode(doc,"//ds:Signature[1]", nscontext);
	    sig = new XMLSignature(root,"");
	    if (!sig.checkSignatureValue(key.getPublic())) {
		System.err.println("Error verifying signature");
	    }
	}
	catch (Exception e) {	
	    System.err.println(e.toString());
	}
	
    }
    
    public void EncryptXML(FileInputStream is, int iters, int iter) {
	try {
	    Document tmpl = parser.parse(new FileInputStream("../xml.files/enc-template.xml"));
	    EncryptedData ed = new EncryptedData(tmpl.getDocumentElement(),"ed1");
//	    ed.setType("http://www.w3.org/2001/04/xmlenc#Element");
//	    ed.encryptElementAndReplace(doc.getDocumentElement(),key.getPublic());
	    ed.encryptContentAndReplace(doc.getDocumentElement(),key.getPublic());
	}
	catch (Exception e) {	
	    System.err.println(e.toString());
	}
		
	org.apache.xerces.dom3.ls.DOMWriter dw = new org.apache.xml.serialize.XMLSerializer();
	String mem = dw.writeToString(doc);
	System.out.println(mem);
    }

    public void DecryptXML(FileInputStream is, int iters, int iter) {
    }

    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom3();
	mybench.Bench(argv);
    }
}