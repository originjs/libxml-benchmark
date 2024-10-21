/* Huge speed optimization posible:
	Replace corelation matrix on square of correlation matrix, it will
	remove need of cpu-consuming sqrt function
*/
#include <math.h>


struct _disp {
    unsigned long disp_n;
    unsigned long disp_s;
    double disp_d;
    double disp_m;
};

typedef struct _disp *disp;

disp disp_init() {
	disp d = (disp)malloc(sizeof(struct _disp));
	d->disp_n=0;
	d->disp_s=0;
	d->disp_d=0;
	return d;
}

void disp_deinit(disp d) {
    free(d);
}

void disp_event(disp d,unsigned long disp_v) {
	unsigned long t;
	
	d->disp_n++;
	t=d->disp_n*(d->disp_n-1);
	
	d->disp_s+=disp_v;
	disp_v*=d->disp_n;

	if (t) d->disp_d+=(double)(((d->disp_s-disp_v)*(d->disp_s-disp_v)))/t;
}

void disp_post(disp d) {
    if (d->disp_n>0) {
	d->disp_m = ((double)d->disp_s) / d->disp_n;
        if (d->disp_n>1) {
    	    d->disp_d /= (d->disp_n-1);
	    d->disp_d = sqrt(d->disp_d);
	}
    }
}	
