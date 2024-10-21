import java.io.*;

//import org.w3c.dom.*;
import com.japisoft.fastparser.*;
import com.japisoft.fastparser.document.*;
import com.japisoft.fastparser.dom.*;


public class fp_dom extends bench {
    Parser p;
    
    public void InitXML() {
	p  = new Parser();
	p.setNodeFactory( new DomNodeFactory() );
    }

    public void ParseXML(FileInputStream is, int iters, int iter) {
//	Parser p  = new Parser();
//	p.setNodeFactory( new DomNodeFactory() );
	try {
	    p.setInputStream( is );
	    p.parse();
	}
	catch (Exception e)
        {
    	    System.out.println(e.toString());
        }
    }

    public void ReleaseXML() {
	System.exit( 0 );
    };
  
    static public void main(String argv[]) throws IOException {
	bench mybench = new fp_dom();
	mybench.Bench(argv);
    }
}
