import java.io.*;
import java.util.*;
import java.text.*;
import oracle.xml.parser.v2.DOMParser;
import oracle.xml.parser.v2.XMLDocument;


public class oracle_dom2 extends bench {
    DOMParser parser;

    public void InitXML() {
	parser=new DOMParser();
    }
    
    public void ParseXML(FileInputStream is, int iters, int iter) {
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
	parser.reset();
    }
    
    static public void main(String argv[]) throws IOException {
	bench mybench = new oracle_dom2();
	mybench.Bench(argv);
    }

}