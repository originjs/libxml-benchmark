public class disp {
    long disp_n=0;
    double disp_s=0;
    double disp_d=0;
    double disp_m=0;

    void disp_init() {
	disp_n=0;
	disp_s=0;
	disp_d=0;
    }
    
    void disp() {
	disp_init();
    }

    void disp_event(double disp_v) {
	long t;
	
	disp_n++;
	t=disp_n*(disp_n-1);
	
	disp_s+=disp_v;
	disp_v*=disp_n;

	if (t>0) disp_d+=(double)(((disp_s-disp_v)*(disp_s-disp_v)))/t;
    }

    void disp_post() {
	if (disp_n>0) {
	    disp_m = ((double)disp_s) / disp_n;
    	    if (disp_n>1) {
    		disp_d /= (disp_n-1);
		disp_d = java.lang.Math.sqrt(disp_d);
	    }
	}
    }	
}