#include <stdio.h>
#include <stdlib.h>

#define ORACLE_PARSER
#include "opcgen.h"

/* Usage:
    opcgen [<number of repeatable elements>]
*/

main(int argc, char *argv[]) {
    unsigned long rpt=0;
    unsigned long i,iters=0;
    FILE *f;
    char fn[32];

    if (argc>=2) rpt=atol(argv[1]);
    if (argc==3) iters=atol(argv[2]);
    if (rpt<=0) rpt=1;

    rnd_init();
    opcgen_init(rpt);
    opcgen();

    if (!iters)	puts(opcgen_msg);
    else {
	for (i=0;i<=iters;i++) {
	    sprintf(fn,"../xml.tmp/%u.xml",i);
	    f=fopen(fn,"w");
	    fputs(opcgen_msg,f);
	    fclose(f);
	    opcgen();
	}
    }
    opcgen_deinit();
}
