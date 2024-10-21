import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class sun_dom2 extends bench {
    DocumentBuilderFactory factory;
    DocumentBuilder parser;
    final String JAXP_SS="http://java.sun.com/xml/jaxp/properties/schemaSource";
    final String JAXP_SL="http://java.sun.com/xml/jaxp/properties/schemaLanguage";
    final String W3C_Schema="http://www.w3.org/2001/XMLSchema";

    
    public void InitXML() {
	    factory = DocumentBuilderFactory.newInstance();
	    factory.setNamespaceAware(false);
	    factory.setValidating(false);
	    try {
    		parser = factory.newDocumentBuilder();
	    }
	    catch (Throwable err) {
    		err.printStackTrace ();
		return;
	    }

    }
    
    public void InitXML_Validation() {
	    factory = DocumentBuilderFactory.newInstance();
	    factory.setNamespaceAware(true);
	    factory.setValidating(true);
	    try {
		factory.setAttribute(JAXP_SL,W3C_Schema);
	    }
	    catch (IllegalArgumentException x) {
		System.out.println("JAXP 1.2 Unsupported!");
	    }

//	    factory.setAttribute(JAXP_SS,new File("test.xsd"));
	    try {
    		parser = factory.newDocumentBuilder();
	    }
	    catch (Throwable err) {
    		err.printStackTrace ();
		return;
	    }

    }

    
    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
    }

    public void ValidateXML(FileInputStream is, int iters, int iter) {
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
    }
    
    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom2();
	mybench.Bench(argv);
    }
}