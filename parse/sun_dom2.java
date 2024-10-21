import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class sun_dom2 extends bench {

    DocumentBuilder parser;
    DocumentBuilderFactory factory;
    
    public void InitXML() {
    	factory = DocumentBuilderFactory.newInstance();
	try {
    	    parser = factory.newDocumentBuilder();
	}
	catch (Throwable err) {
    	    err.printStackTrace ();
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
  
    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_dom2();
	mybench.Bench(argv);
    }
}
