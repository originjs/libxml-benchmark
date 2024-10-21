#include <string.h>
#include <math.h>
#include "random.h"

#define strlength 12
#define xmlsec_maxpri 10000000
#define xmlsec_maxsec 25
#define xmlsec_minpri 10
#define xmlsec_basesize 500
#define xmlsec_secsize 300
#define xmlsec_min_maxsize 1024
char xmlgen_s[xmlsec_basesize];
char xmlgen_ss[xmlsec_secsize];
char *xmlgen_mem;
char *xmlgen_feel_mem;
long xmlgen_real_maxsec;
unsigned long xmlgen_maxsize;
unsigned long xmlgen_header_size;

char *xmlgen_strgen(int size) {
    int i;
    char *s;
    
    s=(char*)malloc(size+1);
    for (i=0;i<size;i++) s[i]=rnd_char();
    s[size]=0;
    return s;
}

void xmlgen_gensec(char *str) {
    char *s1,*s2;
    
    s1=xmlgen_strgen(strlength);
    s2=xmlgen_strgen(strlength);
    sprintf(xmlgen_ss,"<item><title>%s</title><note>%s</note><quantity>%u</quantity><price>%.2f</price></item>\n",
	s1,s2,1+rand()/(RAND_MAX/98),0.1+((double)rand())/(RAND_MAX/99));
    free(s1);
    free(s2);
    strcat(str,xmlgen_ss);
}

int xmlgen_genfirst(char *str,int maxsize,int maxsec) {
    int i,max,size,fullsize;
    char *s1,*s2,*s3,*s4,*s5;

    s1=xmlgen_strgen(strlength);
    s2=xmlgen_strgen(strlength);
    s3=xmlgen_strgen(strlength);
    s4=xmlgen_strgen(strlength);
    s5=xmlgen_strgen(strlength);
    sprintf(xmlgen_s,"<shiporder orderid=\"%06u\"><orderperson>%s</orderperson><shipto><name>%s</name><address>%s</address><city>%s</city><country>%s</country></shipto>\n",
	    rand()/(RAND_MAX/100000),s1,s2,s3,s4,s5);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    strcat(str,xmlgen_s);
    fullsize=strlen(xmlgen_s);
    
    xmlgen_gensec(str);
    size=strlen(xmlgen_ss)+10;
    fullsize+=(size-10);
        
    max=(maxsize-fullsize-13)/size;
    if (max>maxsec) max=maxsec;
    max=rand()/(RAND_MAX/max);

    for (i=0;i<max;i++) {
	xmlgen_gensec(str);
	fullsize+=strlen(xmlgen_ss);
    }
    strcat(str,"</shiporder>\n");
    fullsize+=strlen("</shiporder>\n");
    return fullsize;

}

char *xmlgen_init(int maxsize) {
    
    if (maxsize<xmlsec_min_maxsize) maxsize=xmlsec_min_maxsize;
    
    xmlgen_mem=(char*)malloc(maxsize+1);
    if (!xmlgen_mem) {
	fprintf(stderr,"Can't allocate %lu bytes of memory!\n",maxsize+1);
	exit(0);
    }

    xmlgen_real_maxsec = (long)( ( maxsize / xmlsec_minpri ) - xmlsec_basesize ) / xmlsec_secsize;
    if (2*xmlgen_real_maxsec<xmlsec_minpri) {
	xmlgen_real_maxsec = (long)(sqrt((double)(xmlsec_basesize*xmlsec_basesize+4*xmlsec_secsize*maxsize))-xmlsec_basesize)/(2*xmlsec_secsize);
    }
    if (xmlgen_real_maxsec<2) xmlgen_real_maxsec=2;
    if (xmlgen_real_maxsec>xmlsec_maxsec) xmlgen_real_maxsec=xmlsec_maxsec;
    
#ifdef ORACLE_PARSER
    strcpy(xmlgen_mem,"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"../xml.files/generated.xsl\"?>\n<data xmlns:xsi=\"http://www.w3.org/2000/08/XMLSchema-instance\">\n");
#else
    strcpy(xmlgen_mem,"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"../xml.files/generated.xsl\"?>\n<data xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"../xml.files/generated.xsd\">\n");
#endif
    xmlgen_header_size = strlen(xmlgen_mem);
    
    xmlgen_feel_mem=xmlgen_mem + xmlgen_header_size;

    xmlgen_maxsize=maxsize - xmlgen_header_size;

    return xmlgen_mem;
}

void xmlgen_deinit() {
    free(xmlgen_mem);
}

unsigned long xmlgen() {
    int i;
    char *s=xmlgen_feel_mem;
    unsigned long maxsize=xmlgen_maxsize;
    unsigned long size;
    *s=0;    
    for (i=0;((i<xmlsec_maxpri)&&(maxsize>xmlsec_basesize));i++) {
	size=xmlgen_genfirst(s,maxsize,xmlgen_real_maxsec);
	maxsize-=size;
	s+=size;
    }
    strcat(s,"</data>");
    return xmlgen_header_size + (xmlgen_maxsize - maxsize) + 7;
}
