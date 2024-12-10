#include <stdio.h>
#include <stdlib.h>

#include "xmlgen.h"


/* Usage:
    xmlgen [<size>] [<iterations>]
*/

int main(int argc, char *argv[]) {
    unsigned long size=0;
    unsigned long i,iters=0;
    FILE *f;
    char fn[32];
    char *s;
    
    if (argc>=2) size=atol(argv[1]);
    if (argc==3) iters=atol(argv[2]);
    if (size<500) size=1024;

    rnd_init();
    s=xmlgen_init(size);
    xmlgen();
    if (!iters) puts(s);
    else {
    	for (i=1;i<=iters;i++) {
	    sprintf(fn,"../xml.tmp/%u.xml",i);
	    f=fopen(fn,"w");
	    fputs(s,f);
	    fclose(f);
	    xmlgen();
	}
    }
    xmlgen_deinit();
}
