import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 
import org.w3c.dom.*;


import java.security.*;
import java.security.cert.*;
/*
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
*/

import org.apache.xpath.XPathAPI;

import com.ibm.dom.util.DOMUtil;
import com.ibm.xml.dsig.IDResolver;
import com.ibm.xml.dsig.XSignatureException;
import com.ibm.xml.enc.AlgorithmFactoryExtn;
import com.ibm.xml.enc.EncryptedKeyRetriever;
import com.ibm.xml.enc.EncryptionContext;
import com.ibm.xml.enc.EncryptionEngine;
import com.ibm.xml.enc.DecryptionContext;
import com.ibm.xml.enc.KeyInfoResolver;
import com.ibm.xml.enc.KeyInfoResolvingException;
import com.ibm.xml.enc.StructureException;
import com.ibm.xml.enc.type.EncryptedData;
import com.ibm.xml.enc.util.AdHocIdResolver;
import com.ibm.xml.enc.util.KeyStoreKeyInfoResolver;
import com.ibm.xml.enc.util.SameDocumentEncryptedKeyRetriever;

import org.bouncycastle.jce.provider.BouncyCastleProvider;
import com.ibm.xml.enc.KeyInfoResolverBase;
import com.ibm.xml.enc.type.KeyInfo;
import com.ibm.xml.enc.type.EncryptedKey;
import org.bouncycastle.crypto.AsymmetricCipherKeyPair;
import org.bouncycastle.crypto.generators.RSAKeyPairGenerator;
import org.bouncycastle.crypto.params.RSAKeyGenerationParameters;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.SecretKey;
import java.security.spec.KeySpec;

public class sun_dom3 extends bench {
    DocumentBuilderFactory factory;
    DocumentBuilder parser;
    Document doc;
    Document tmpl;
//    XMLSignature sig;
    KeyPair key;
//    AsymmetricCipherKeyPair rsakey;
    
    EncryptionContext ectx;
    DecryptionContext dctx;
    AlgorithmFactoryExtn af; 

    public void InitXML() {
	    KeyPairGenerator kpg;
	    factory = DocumentBuilderFactory.newInstance();
	    factory.setNamespaceAware(true);
	    factory.setValidating(false);
	    try {
		Security.addProvider(new BouncyCastleProvider());

    		parser = factory.newDocumentBuilder();
		kpg = KeyPairGenerator.getInstance("RSA","BC");
		kpg.initialize(2048);
		key = kpg.genKeyPair();
		
		ectx = new EncryptionContext();
		af = new AlgorithmFactoryExtn();
		af.setProvider("BC");
		ectx.setAlgorithmFactory(af);


		tmpl = parser.parse(new FileInputStream("../xml.files/enc-template.xml"));


		dctx = new DecryptionContext();
		dctx.setAlgorithmFactory(af);
		dctx.setKey(key.getPrivate());
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
/*	Element root;
	
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
	}*/
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
/*	try {
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
*/
    }
    
    public void EncryptXML(FileInputStream is, int iters, int iter) {
	System.out.println("Starting:");
	try {
	    Element root=(Element)(tmpl.getDocumentElement()).cloneNode(true);
	    Element ek=(Element)root.getElementsByTagName("EncryptedKey").item(0);
	    ectx.setEncryptedType(root,"http://www.w3.org/2001/04/xmlenc#Element",null,null);
	    Key rkey = ectx.generateKey();
	    ectx.setKey(rkey);
	    ectx.setData(doc.getDocumentElement());
	    ectx.encrypt();
	    ectx.replace();
	System.out.println("1:");
	    ectx.setEncryptedType(ek,null,null,null);
	    ectx.setData(rkey);
	    ectx.setKey(key.getPublic());
	System.out.println("2:");
	    ectx.encrypt();
	    ectx.replace();
	System.out.println("3:");
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

    public void DecryptXML(FileInputStream is, int iters, int iter) {
/*	try {
	    Element root=doc.getDocumentElement();
	    dctx.setEncryptedType(root,"http://www.w3.org/2001/04/xmlenc#Element",null,null);
	    dctx.decrypt();
	    dctx.replace();
	}
	catch (Exception e) {	
	    System.err.println(e.toString());
	}


	org.apache.xerces.dom3.ls.DOMWriter dw = new org.apache.xml.serialize.XMLSerializer();
	String mem = dw.writeToString(doc);
	System.out.println(mem);*/

    }


    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom3();
	mybench.Bench(argv);
    }
}