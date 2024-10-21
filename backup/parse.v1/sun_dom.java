import java.io.*;
import java.util.*;
import java.text.*;
import org.xml.sax.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class sun_dom {
    static DocumentBuilder parser;

    static public void ParseXML(char[] xml, int xmllen, int iters, int iter) {
	if (iter==0) {
	    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	    try {
    		parser = factory.newDocumentBuilder();
	    }
	    catch (Throwable err) {
    		err.printStackTrace ();
	    }
	}

	String str=new String(xml,0,xmllen);
	StringBufferInputStream is = new StringBufferInputStream(str);
	try {
	    parser.parse(is);		
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
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
	    result=(post.getTime()-pre.getTime())/1000.0;
	    System.err.println(iterations);
	    System.err.println(result);
    	}
	
    }
}