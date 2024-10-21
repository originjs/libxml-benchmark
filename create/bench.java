import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class bench {
    public void InitXML(int enlarge) {};
    public void ReleaseXML() {};
    public void ParseXML(int enlarge, int iters, int iter) {};
    
    public void Bench(String argv[]) throws IOException {
	int iterations,size,mode;
	
	if (argv.length<1) {
	    System.err.println("Usage:\n\tme <iterations> [size]");
	} else {
	    iterations = Integer.parseInt(argv[0]);
	    size = Integer.parseInt(argv[1]);

	    double a,b;
	    Date pre,post;
	    SimpleDateFormat s,ms;
	    disp d = new disp();
	    double result;
	    s=new SimpleDateFormat("ss");
	    ms=new SimpleDateFormat("SSS");
	    
	    InitXML(size);
	    ParseXML(size,iterations,0);
	    
	    for (int i=1;i<=iterations;i++) {
		pre=new Date();
		ParseXML(size,iterations,i);
		post=new Date();
		a=Double.valueOf(s.format(post)).doubleValue();
		b=Double.valueOf(s.format(pre)).doubleValue();
		result=(post.getTime()-pre.getTime());
		d.disp_event(result);
//		System.err.println(result);
	    }
	    d.disp_post();

	    System.err.println("Creating DOM Tre Time " + d.disp_m + "(" + (300*d.disp_d/d.disp_m) + "%) ms");

	    ReleaseXML();
	}
    }
}