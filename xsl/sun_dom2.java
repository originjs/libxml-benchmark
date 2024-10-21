import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 
import org.w3c.dom.Document;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.dom.DOMSource; 
import javax.xml.transform.stream.StreamSource; 
import javax.xml.transform.stream.StreamResult; 


public class sun_dom2 extends bench {

    DocumentBuilder parser;
    DocumentBuilderFactory factory;
    TransformerFactory tFactory;
    Transformer transformer;
    StreamSource stylesource;
    Document doc;
    
    public void InitXML() {
    	factory = DocumentBuilderFactory.newInstance();
	try {
    	    parser = factory.newDocumentBuilder();
	}
	catch (Exception e) {
    	    System.err.println(e.toString());
        }
    }

    public void InitXML_Transformation(FileInputStream is) {
	try {
    	    stylesource = new StreamSource(is); 
	    tFactory=TransformerFactory.newInstance();
	    transformer = tFactory.newTransformer(stylesource);
	}
	catch (Exception e) {
    	    System.err.println(e.toString());
        }
    }
    
    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    doc = parser.parse(is);		
	}
	catch (Exception e) {
    	    System.err.println(e.toString());
        }
    }

    public void TransformXML(FileInputStream is, int iters, int iter) {
	try {
	    ByteArrayOutputStream mem = new ByteArrayOutputStream();
	    DOMSource source = new DOMSource(doc);
	    StreamResult result = new StreamResult(mem);
	    transformer.transform(source, result); 
//	    if (iter==iters) System.out.println(mem);
	}
	catch (Exception e) {
    	    System.err.println(e.toString());
        }
    }
  
    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom2();
	mybench.Bench(argv);
    }
}
