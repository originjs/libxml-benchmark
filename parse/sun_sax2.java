import java.io.*;
import java.util.*;
import java.text.*;

import org.xml.sax.*;
import org.xml.sax.helpers.*;
import javax.xml.parsers.SAXParserFactory; 
import javax.xml.parsers.SAXParser;

public class sun_sax2 extends bench {
    SaxHandlers handler;
    XMLReader parser;
    SAXParserFactory factory;
    
    public void InitXML() {
	factory = SAXParserFactory.newInstance();
	handler = new SaxHandlers();
	try {
	    parser=factory.newSAXParser().getXMLReader();
	}
	catch (Throwable err) {
    	    System.err.println(err.getMessage());
	}
	parser.setContentHandler(handler);
    }

    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    parser.parse(new InputSource(is));		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
    }
  
    static public void main(String argv[]) throws IOException {
	bench mybench = new sun_sax2();
	mybench.Bench(argv);
    }
}
