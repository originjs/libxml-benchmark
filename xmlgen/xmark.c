#include <stdio.h>
#include <stdlib.h>

#include "xmark.h"


/* Usage:
    xmark [<size>] [<iterations>]
*/

main(int argc, char *argv[]) {
    unsigned long size=1;
    unsigned long i,iters=0;
    FILE *f;
    char fn[32];
    char *s;
    
    if (argc>=2) size=atol(argv[1]);
    if (argc==3) iters=atol(argv[2]);

    s=xmark_init(size);
    xmark(0);
    if (!iters) puts(s);
    else {
    	for (i=0;i<=iters;i++) {
	    sprintf(fn,"../xml.tmp/%u.xml",i);
	    f=fopen(fn,"w");
	    fputs(s,f);
	    fclose(f);
	    xmark(0);
	}
    }
    xmark_deinit();
}
