import java.io.*;
import java.util.*;
import java.text.*;
import javax.xml.parsers.DocumentBuilderFactory; 
import javax.xml.parsers.DocumentBuilder; 

public class bench {
    public void InitXML() {};
    public void InitXML_Security() {};
    public void ReleaseXML() {};
    public void ParseXML(FileInputStream is, int iters, int iter) {};
    public void SignXML(FileInputStream is, int iters, int iter) {};
    public void VerifyXML(FileInputStream is, int iters, int iter) {};
    public void EncryptXML(FileInputStream is, int iters, int iter) {};
    public void DecryptXML(FileInputStream is, int iters, int iter) {};
    
    public void Bench(String argv[]) throws IOException {
	int iterations,size,mode;
	
	if (argv.length<2) {
	    System.err.println("Usage:\n\tme <iterations> <xml file|xmlgen|opcgen> [<xsd file>|size]");
	} else {
	    iterations = Integer.parseInt(argv[0]);

	    Collator mc = Collator.getInstance();
	    if (mc.compare(argv[1],"xmlgen")==0) mode=1;
	    else if (mc.compare(argv[1],"opcgen")==0) mode=2;
	    else mode=0;

	    if (mode>0) size = Integer.parseInt(argv[2]);
	    else size=0;
	    	    
	    double a,b;
	    Date pre,post;
	    SimpleDateFormat s,ms;
	    disp d = new disp();
	    disp dv = new disp();
	    double result,init_result,init_result2, init_dtime, init_d;
	    double dv_init_result,dv_init_result2;
	    s=new SimpleDateFormat("ss");
	    ms=new SimpleDateFormat("SSS");
	    FileInputStream file;
	    
	    InitXML();
	    
	    pre=new Date();
	    InitXML_Security();
	    post=new Date();
	    a=Double.valueOf(s.format(post)).doubleValue();
	    b=Double.valueOf(s.format(pre)).doubleValue();
	    init_result=(post.getTime()-pre.getTime());
	    
	    if (mode==0)
	        file = new FileInputStream(argv[1]);
	    else 
	        file = new FileInputStream("../xml.tmp/0.xml");
	    ParseXML(file,iterations,0);

	    pre=new Date();
	    EncryptXML(file,iterations,0);
	    DecryptXML(file,iterations,0);
	    SignXML(file,iterations,0);
	    VerifyXML(file,iterations,0);
	    post=new Date();
	    a=Double.valueOf(s.format(post)).doubleValue();
	    b=Double.valueOf(s.format(pre)).doubleValue();
	    init_result2=(post.getTime()-pre.getTime());
	    
	    for (int i=1;i<=iterations;i++) {
		if (mode==0)
		    file = new FileInputStream(argv[1]);
		else 
		    file = new FileInputStream("../xml.tmp/" + i + ".xml");
		    
		ParseXML(file,iterations,0);
	
		pre=new Date();
		EncryptXML(file,iterations,0);
		DecryptXML(file,iterations,0);
		post=new Date();
		a=Double.valueOf(s.format(post)).doubleValue();
		b=Double.valueOf(s.format(pre)).doubleValue();
		result=(post.getTime()-pre.getTime());
		dv.disp_event(result);
//		System.err.println(result);

		pre=new Date();
		SignXML(file,iterations,0);
	        VerifyXML(file,iterations,0);
		post=new Date();
		a=Double.valueOf(s.format(post)).doubleValue();
		b=Double.valueOf(s.format(pre)).doubleValue();
		result=(post.getTime()-pre.getTime());
		d.disp_event(result);
//		System.err.println(result);
	    }
	    d.disp_post();
	    dv.disp_post();
	    
	    if (mode==2) {
	    	System.err.println("Signing/Verifiying Time: "+ d.disp_s+" ms for " + iterations + " messages");
	    	System.err.println("Encryption/Decryption Time: "+ dv.disp_s+" ms for " + iterations + " messages");
	    } else {
		init_dtime=(init_result2 - d.disp_m - dv.disp_m);
	    	if (init_dtime<0.1) {
		    init_d=0;
		    init_dtime=0;
		} else {
		    init_d=300 * (d.disp_d+dv.disp_d) / init_dtime;
		}
		System.err.println("Initialisation Time: " + init_result + " + " + init_dtime + "(" + init_d + "%) ms");
		System.err.println("Signing/Verifying Time: " + d.disp_m + "(" + (300*d.disp_d/d.disp_m) + "%)");
		System.err.println("Encryption/Decryption Time: " + dv.disp_m + "(" + (300*dv.disp_d/dv.disp_m) + "%)");
	    }
	    ReleaseXML();
	}
    }
}