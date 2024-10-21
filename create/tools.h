#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../tools/disp.h"

struct TestData {
    unsigned long iterations;
    unsigned long inc;
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
    fprintf(stderr,"Usage:\n\t%s <iterations> [size increase]\n",myname);
    exit(0);
}

int Test(int argc, char *argv[]) {
    int i,j;
    struct timeval pre_time,post_time;
    struct timezone tz;
    unsigned long time;
    struct TestData td;

    if (argc>=2) td.iterations=atol(argv[1]);
    else Usage(argv[0]);
    if (argc==3) td.inc=atol(argv[2]);
    else td.inc=0;

    initXML(&td);
    parseXML(&td,0);
    
    disp_init();
    for (i=1;i<=td.iterations;i++) {
	gettimeofday(&pre_time,&tz);
	parseXML(&td,i);
	gettimeofday(&post_time,&tz);
	time=(post_time.tv_sec-pre_time.tv_sec)*1000000+(post_time.tv_usec-pre_time.tv_usec);
	disp_event(time);
//	printf("%lu\n",time);
    }
    disp_post();
    
    releaseXML(&td);
    
    printf("Building DOM tree in %.3lf(%.2lf) ms!\n",((double)disp_m) / 1000,300*disp_d/disp_m);

    return 0;
}

