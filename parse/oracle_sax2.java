import java.io.*;
import java.util.*;
import java.text.*;

import oracle.xml.parser.v2.*;
import org.xml.sax.SAXParseException;

public class oracle_sax2 extends bench {
    SAXParser parser;
    SaxHandlers handler;

    public void InitXML() {
	parser=new SAXParser();
	handler = new SaxHandlers();
        parser.setContentHandler(handler);
    
    }
    
    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.err.println(e.toString());
    	    System.err.println(((SAXParseException)e).getLineNumber());
        }
    }

    static public void main(String argv[]) throws IOException {
	bench mybench = new oracle_sax2();
	mybench.Bench(argv);
    }

}