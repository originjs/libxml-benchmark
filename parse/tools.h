#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../tools/disp.h"
#include "../xmlgen/xmlgen.h"
#include "../xmlgen/opcgen.h"

#ifdef GENERATOR_XMARK
#include "../xmlgen/xmark.h"
#endif /* GENERATOR_XMARK */

struct TestData {
    unsigned long iterations;
    unsigned long size;
    
    char *fn;
    char *xml;
    unsigned long xmllen;
};

char *ReadFile(char *fn) {
    FILE *f;
    struct stat st;
    char *buf;
    
    f=fopen(fn,"r");
    if (!f) {
	printf("Can't open XML file!\n");
	exit(1);
    }
    fstat(fileno(f), &st);
    buf=(char*)malloc(st.st_size+5);
    if (!buf) {
	printf("Can't allocate memory!\n");
	exit(1);
    }
    ((unsigned long*)buf)[0]=st.st_size;
    fread(buf+4,st.st_size,1,f);
    fclose(f);
    buf[st.st_size+4]=0;
    return buf;
}

void ReadConfig(struct TestData *td) {
    FILE *f;
    f=fopen("config","r");
    if (!f) {
	printf("Error opening config file!\n");
	exit(1);
    }
    fscanf(f,"%lu",&(td->iterations));
    fclose(f);
}

void initXML(struct TestData *td);
void releaseXML(struct TestData *td);
void parseXML(struct TestData *td, unsigned long iter);

void Usage(char *myname) {

    printf("Usage:\n\t%s <iterations> [<xml file>|xmlgen|opcgen",myname);
#ifdef GENERATOR_XMARK
    printf("|xmark");
#ifdef DTD_VALIDATION
#ifdef DTD_VALIDATION_SUPPORTED
    printf("|xmarkdtd");
#endif
#endif
#endif /* GENERATOR_XMARK */
    printf("] <size>\n");
    exit(0);
}

int Test(int argc, char *argv[]) {
    int i,j;
    struct timeval pre_time,post_time;
    struct timezone tz;
    unsigned long init_time,init_time2,time;
    double init_dtime,init_d;
    unsigned char mode=0;	/* 0 - file, 1 - xmlgen, 2 - opcgen */
    struct TestData td;
    char *xmlbuf;

    if ((argc<3)||(argc>4)) Usage(argv[0]);
    
    td.iterations = atol(argv[1]);
    if (td.iterations<=0) Usage(argv[0]);

#ifdef DTD_VALIDATION
#ifndef DTD_VALIDATION_SUPPORTED
    fprintf(stderr,"DTD validation not implemented yet or not supported by parser!\n");
    exit(1);
#endif
#endif

    if (!strncmp(argv[2],"xmlgen",6)) mode=1;
    else if (!strncmp(argv[2],"opcgen",6)) mode=2;
#ifdef GENERATOR_XMARK
    else if (!strncmp(argv[2],"xmark",8)) mode=3;
#ifdef DTD_VALIDATION
    else if (!strncmp(argv[2],"xmarkdtd",8)) mode=4;
#endif
#endif /* GENERATOR_XMARK */

    td.fn=argv[2];
    
    if (mode) {
	if (argc==4) td.size = atol(argv[3]);
	else Usage(argv[0]);
	if (td.size<1) Usage(argv[0]);

        rnd_init();	/* Initialising Random Generator */
    }
    
//    ReadConfig(&td);
    
    switch (mode) {
	case 0:
	    xmlbuf=ReadFile(argv[2]);
	    if (!xmlbuf) {
		fprintf(stderr,"Can't read XML file!\n");
		exit(0);
	    }
	    td.xml=xmlbuf+4;
	    td.xmllen=((unsigned long*)xmlbuf)[0];
	break;
	case 1:
	    xmlbuf=xmlgen_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=xmlgen();
	break;
	case 2:
	    xmlbuf=opcgen_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=opcgen();
	break;
#ifdef GENERATOR_XMARK
	case 3:
	    xmlbuf=xmark_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=xmark(0);
	break;
	case 4:
	    xmlbuf=xmark_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=xmark(1);
	break;
#endif /* GENERATOR_XMARK */

    }

    gettimeofday(&pre_time,&tz);
    initXML(&td);
    gettimeofday(&post_time,&tz);
    init_time=(post_time.tv_sec-pre_time.tv_sec)*1000000+(post_time.tv_usec-pre_time.tv_usec);

    gettimeofday(&pre_time,&tz);
    parseXML(&td,0);
    gettimeofday(&post_time,&tz);
    init_time2=(post_time.tv_sec-pre_time.tv_sec)*1000000+(post_time.tv_usec-pre_time.tv_usec);
        
    disp_init();
    for (i=1;i<=td.iterations;i++) {
	switch (mode) {
	    case 1:
		td.xmllen=xmlgen();
	    break;
	    case 2:
		td.xmllen=opcgen();
	    break;
#ifdef GENERATOR_XMARK
	    case 3:
		td.xmllen=xmark(0);
	    break;
	    case 4:
		td.xmllen=xmark(1);
	    break;
#endif /* GENERATOR_XMARK */
	}
	gettimeofday(&pre_time,&tz);
	parseXML(&td,i);
	gettimeofday(&post_time,&tz);
	time=(post_time.tv_sec-pre_time.tv_sec)*1000000+(post_time.tv_usec-pre_time.tv_usec);
	disp_event(time);
//	printf("%lu\n",time);
    }
    disp_post();
    releaseXML(&td);
    
    switch (mode) {
	case 0:
	    free(xmlbuf);
	break;
	case 1:
	    xmlgen_deinit();
	break;
	case 2:
	    opcgen_deinit();
	break;
#ifdef GENERATOR_XMARK
	    case 3:
	    case 4:
		xmark_deinit();
	    break;
#endif /* GENERATOR_XMARK */
    }

    if (mode==2) 
	printf("Parsing Time %lf ms for %lu messages\n", ((double)disp_s) / 1000,td.iterations);
    else {
	if ((init_time2 - disp_m)<10) {
	    init_d=0;
	    init_dtime=0;
	} else {
	    init_d=300 * disp_d / fabs(init_time2 - disp_m);
	    init_dtime=(init_time2 - disp_m)/1000;
	}
	printf("Initialisation time %.3lf + %.3lf(%.2lf%) ms, Parsing Time %.3lf(%.2lf%) ms\n",(1. * init_time) / 1000, init_dtime, init_d, disp_m / 1000, 300*disp_d/disp_m);
    }

    return 0;
}

