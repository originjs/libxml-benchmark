import java.io.*;
import java.util.*;
import java.text.*;
import oracle.xml.parser.v2.SAXParser;
import oracle.xml.parser.v2.XMLDocument;
import org.xml.sax.Parser;
import org.xml.sax.AttributeList;
import org.xml.sax.HandlerBase;
import org.xml.sax.InputSource;
import org.xml.sax.SAXParseException;


public class oracle_sax extends HandlerBase {
    static SAXParser parser;

    static public void ParseXML(char[] xml, int xmllen, int iters, int iter) {
	if (iter==0) {
	    parser=new SAXParser();
	    oracle_sax handler = new oracle_sax();
            parser.setDocumentHandler(handler);
	}

	String str=new String(xml,0,xmllen);
	StringBufferInputStream is = new StringBufferInputStream(str);
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
    	    System.out.println(((SAXParseException)e).getLineNumber());
        }

	if (iter+1==iters) {
	}
    }
    
    static public void main(String argv[]) throws IOException {
        char[] xml=new char[65535];
	int  xmllen;
	int iterations;
	
	if (argv.length!=1) {
	    System.err.println("Usage:\n\tme <xml file>");
	} else {
	    File file = new File(argv[0]);
	    FileReader fstream = new FileReader(file);
	    BufferedReader in = new BufferedReader(fstream);
	    xmllen=in.read(xml,0,65535);
	    if (xmllen<1) {
		System.err.println("Usage:\n\tme <xml file>");
	    }
	    in.close();
	    
	    File fconfig = new File("config");
	    FileReader fstream2 = new FileReader(fconfig);
	    BufferedReader fc = new BufferedReader(fstream2);
	    iterations = Integer.parseInt(fc.readLine());
	    fc.close();
	    
	    Date pre,post;
	    SimpleDateFormat s,ms;
	    double result;
	    s=new SimpleDateFormat("ss");
	    ms=new SimpleDateFormat("SSS");
	    pre=new Date();
	    for (int i=0;i<iterations;i++) {
		ParseXML(xml,xmllen,iterations,i);
	    }
	    post=new Date();
	    double a,b;
	    a=Double.valueOf(s.format(post)).doubleValue();
	    b=Double.valueOf(s.format(pre)).doubleValue();
/*	    result =	(
			    -
			    Double.valueOf(s.format(pre)).doubleValue()
			) +
			(
			    Double.valueOf(ms.format(post)).doubleValue()-
    			    Double.valueOf(ms.format(pre)).doubleValue()
			) / 1000;*/
	    result=(post.getTime()-pre.getTime())/1000.;
	    System.err.println(iterations);
	    System.err.println(result);
    	}
	
    }

   public void startDocument() 
   {
    return;
   }

   public void endDocument()
   {
    return;
   }
      
   public void startElement(String name, AttributeList atts) 
   {
    return;
   }

   public void endElement(String name)
   {
    return;
   }

   public void characters(char[] cbuf, int start, int len) 
   {
    return;
   }
}