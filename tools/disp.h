/* Huge speed optimization posible:
	Replace corelation matrix on square of correlation matrix, it will
	remove need of cpu-consuming sqrt function
*/
#include <math.h>

unsigned long disp_n;
unsigned long disp_s;
double disp_d;
double disp_m;

void disp_init() {
	disp_n=0;
	disp_s=0;
	disp_d=0;
}


void disp_event(unsigned long disp_v) {
	unsigned long t;
	
	disp_n++;
	t=disp_n*(disp_n-1);
	
	disp_s+=disp_v;
	disp_v*=disp_n;

	if (t) disp_d+=(double)(((disp_s-disp_v)*(disp_s-disp_v)))/t;
}

void disp_post() {
    if (disp_n>0) {
	disp_m = ((double)disp_s) / disp_n;
        if (disp_n>1) {
    	    disp_d /= (disp_n-1);
	    disp_d = sqrt(disp_d);
	}
    }
}	
