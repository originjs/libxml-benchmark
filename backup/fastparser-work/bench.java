import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class bench {
    public void InitXML() {};
    public void ReleaseXML() {};
    public void ParseXML(FileInputStream is, int iters, int iter) {};
    
    public void Bench(String argv[]) throws IOException {
	int iterations,size,mode;
	
	if (argv.length<2) {
	    System.err.println("Usage:\n\tme <iterations> <xml file|xmlgen|opcgen> [size]");
	} else {
	    iterations = Integer.parseInt(argv[0]);

	    Collator mc = Collator.getInstance();
	    if (mc.compare(argv[1],"xmlgen")==0) mode=1;
	    else if (mc.compare(argv[1],"opcgen")==0) mode=2;
	    else mode=0;

	    if (mode>0) size = Integer.parseInt(argv[2]);

	    double a,b;
	    Date pre,post;
	    SimpleDateFormat s,ms;
	    disp d = new disp();
	    double result,init_result,init_result2, init_dtime, init_d;
	    s=new SimpleDateFormat("ss");
	    ms=new SimpleDateFormat("SSS");
	    FileInputStream file;
	    
	    pre=new Date();
	    InitXML();
	    post=new Date();
	    a=Double.valueOf(s.format(post)).doubleValue();
	    b=Double.valueOf(s.format(pre)).doubleValue();
	    init_result=(post.getTime()-pre.getTime());
	    
	    pre=new Date();
	    if (mode==0)
	        file = new FileInputStream(argv[1]);
	    else 
	        file = new FileInputStream("../xml.tmp/0.xml");
	    ParseXML(file,iterations,0);
	    post=new Date();
	    a=Double.valueOf(s.format(post)).doubleValue();
	    b=Double.valueOf(s.format(pre)).doubleValue();
	    init_result2=(post.getTime()-pre.getTime());
	    
	    for (int i=1;i<=iterations;i++) {
		pre=new Date();
		if (mode==0)
		    file = new FileInputStream(argv[1]);
		else 
		    file = new FileInputStream("../xml.tmp/" + i + ".xml");
		    
		ParseXML(file,iterations,i);
		post=new Date();
		a=Double.valueOf(s.format(post)).doubleValue();
		b=Double.valueOf(s.format(pre)).doubleValue();
		result=(post.getTime()-pre.getTime());
		d.disp_event(result);
//		System.err.println(result);
	    }
	    d.disp_post();

	    if (mode==2)
	    	System.err.println("Parsing Time "+d.disp_s+" ms for " + iterations + " messages");
	    else {
	    	if ((init_result2 - d.disp_m)<0.1) {
		    init_d=0;
		    init_dtime=0;
		} else {
		    init_dtime=(init_result2 - d.disp_m);
		    init_d=300 * d.disp_d / init_dtime;
		}
		System.err.println("Initialisation time " + init_result + " + " + init_dtime + "(" + init_d + "%) ms");
		System.err.println("Parsing Time " + d.disp_m + "(" + (300*d.disp_d/d.disp_m) + "%)");
	    }
	    
	    ReleaseXML();
	}
    }
}