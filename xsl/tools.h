#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../tools/disp.h"
#include "../xmlgen/xmlgen.h"
#include "../xmlgen/opcgen.h"

struct TestData {
    unsigned long iterations;
    
    char *fn;
    char *scfn;
    char *xml;
    unsigned long xmllen;
    char *xsl;
    unsigned long xsllen;
    unsigned long size;
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

void parseXML(struct TestData *td, unsigned long iter);
void transformXML(struct TestData *td, unsigned long iter);
void initXML_Transformation(struct TestData *td);
void initXML(struct TestData *td);
void releaseXML(struct TestData *td);


void Usage(char *myname) {
    printf("Usage:\n\t%s <iterations> [<xml file>|xmlgen|opcgen] [<xsl file>|<size>]\n",myname);
    exit(0);
}


int Test(int argc, char *argv[]) {
    int i,j;
    struct timeval pre_time,post_time;
    struct timezone tz;
    unsigned long init_time,init_time2,time;
    double init_dtime,init_d;
    unsigned long parse_s;
    double parse_m,parse_d;
    unsigned char mode=0;	/* 0 - file, 1 - xmlgen, 2 - opcgen */
    struct TestData td;
    char *xmlbuf,*xslbuf;

    if (argc!=4) Usage(argv[0]);

    td.iterations = atol(argv[1]);
    if (td.iterations<=0) Usage(argv[0]);
    
    if (!strncmp(argv[2],"xmlgen",6)) mode=1;
    else if (!strncmp(argv[2],"opcgen",6)) mode=2;
    td.fn=argv[2];

    if (mode) {
	td.size = atol(argv[3]);
	if (td.size<=0) Usage(argv[0]);
	td.scfn = (char*)malloc(32);
	
	rnd_init();	/* Initialising Random Generator */
    }

    switch (mode) {
	case 0:
	    xmlbuf=ReadFile(argv[2]);
	    if (!xmlbuf) {
		fprintf(stderr,"Can't read XML file!\n");
		exit(0);
	    }
	    td.xml=xmlbuf+4;
	    td.xmllen=((unsigned long*)xmlbuf)[0];

	    td.scfn=argv[3];
	break;
	case 1:
	    xmlbuf=xmlgen_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=xmlgen();

	    strcpy(td.scfn,"../xml.files/generated.xsl");
	break;
	case 2:
	    xmlbuf=opcgen_init(td.size);
	    td.xml=xmlbuf;
	    td.xmllen=opcgen();

	    strcpy(td.scfn,"../xml.files/opc.xsl");
	    fprintf(stderr,"OPC XML Transformation not supported!\n");
	    exit(0);
	break;
    }

    xslbuf=ReadFile(td.scfn);
    if (!xslbuf) {
	fprintf(stderr,"Can't read XSL file!\n");
	exit(0);
    }

    td.xsl=xslbuf+4;
    td.xsllen=((unsigned long*)xslbuf)[0];

    
    initXML(&td);
    parseXML(&td,0);

    gettimeofday(&pre_time,&tz);
    initXML_Transformation(&td);
    gettimeofday(&post_time,&tz);
    init_time=(post_time.tv_sec-pre_time.tv_sec)*1000000+(post_time.tv_usec-pre_time.tv_usec);

    gettimeofday(&pre_time,&tz);
    transformXML(&td,0);
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
	}
	parseXML(&td,i);
	gettimeofday(&pre_time,&tz);
	transformXML(&td,i);
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
    }
    free(xslbuf);
    if (mode) free(td.scfn);
    

    if (mode==2) 
	printf("XSL Transformation Time %lf ms for %lu messages\n", ((double)(disp_s)) / 1000,td.iterations);
    else {
	init_dtime=(init_time2 - disp_m);
	if (init_dtime<10) {
	    init_d=0;
	    init_dtime=0;
	} else {
	    init_d=300 * disp_d / init_dtime;
	    init_dtime/=1000;
	}
	printf("Initialisation time %.3lf + %.3lf(%.2lf%) ms\nXSL Transformation Time %.3lf(%.2lf%) ms\n",(1. * init_time) / 1000, init_dtime, init_d, (disp_m) / 1000, 300*(disp_d)/(disp_m));
    }

    return 0;
}

