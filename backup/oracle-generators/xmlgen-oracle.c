#include <stdio.h>
#include <stdlib.h>

#define ORACLE_PARSER
#include "xmlgen.h"


/* Usage:
    xmlgen [<size>]
*/

main(int argc, char *argv[]) {
    unsigned long size=0;
    char *s;
    
    if (argc==2) size=atol(argv[1]);
    if (size<500) size=1024;

    rnd_init();
    s=xmlgen_init(size);
    xmlgen();
    puts(s);
    xmlgen_deinit();
}
