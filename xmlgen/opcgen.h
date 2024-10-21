#include <string.h>
#include <math.h>
#include "random.h"

#define opcgen_xmls "../xml.files/opc.xmls"
#define opcgen_max_string_size 255
#define opcgen_max_message_size 4096
#define opcgen_max_submessage_size 2048
#define opcgen_max_message_number 50

char opcgen_xmlns[1024];
unsigned short int opcgen_messages=0;
char* opcgen_message[opcgen_max_message_number];
char opcgen_tmpstr[opcgen_max_string_size]; 
unsigned long int opcgen_max_items=0;
unsigned long int opcgen_max_subitems=0;
char *opcgen_msg=0;
unsigned long opcgen_msg_size;


void opcgen_reader() {
    FILE *f;
    unsigned char status = 0; /* 0 - idle, 1 - parsing message */
    unsigned char flag;
    int i;
    
    f=fopen(opcgen_xmls,"r");
    if (!f) {
	fprintf(stderr,"Can't open message file!\n");
	exit(1);
    }
    while (!feof(f)) {
	if (!fgets(opcgen_tmpstr,opcgen_max_string_size,f)) break;

	for(i=0;((opcgen_tmpstr[i]!=0)&&((opcgen_tmpstr[i]==' ')||
		(opcgen_tmpstr[i]=='\t')||(opcgen_tmpstr[i]=='\n')||
		(opcgen_tmpstr[i]=='\r')));i++);
	if (opcgen_tmpstr[i]!=0) {
	    if (status==0) {
		if (opcgen_messages==opcgen_max_message_number) {
		    fprintf(stderr,"Number of messages exceeded!\n");
		    exit(0);
		}
		opcgen_message[opcgen_messages]=(char*)malloc(opcgen_max_message_size);
		opcgen_message[opcgen_messages++][0]=0;
		for (i=0,flag=0;((opcgen_tmpstr[i]!=0)&&(flag!=2));i++) {
		    if (opcgen_tmpstr[i]=='<') flag=1;
		    else if ((flag==1)&&((opcgen_tmpstr[i]==' ')||
			(opcgen_tmpstr[i]=='\t')||(opcgen_tmpstr[i]=='\n')||
			(opcgen_tmpstr[i]=='\r')||(opcgen_tmpstr[i]=='>')||
			(opcgen_tmpstr[i]=='/'))) {
			    strncpy(opcgen_message[opcgen_messages-1],opcgen_tmpstr,i);
			    strcpy(opcgen_message[opcgen_messages-1]+i,opcgen_xmlns);
			    flag=2;
		    }
		}
		if (flag!=2) {
		    fprintf(stderr,"Error in messages file format!\n");
		    exit(0);
		}
		strcat(opcgen_message[opcgen_messages-1],opcgen_tmpstr+i-1);
		status=1;
	    }
	    else strcat(opcgen_message[opcgen_messages-1],opcgen_tmpstr);
	} else if (status==1) status=0;
    }
    fclose(f);
}

void opcgen_freemem() {
    int i;
    for (i=0;i<opcgen_messages;i++) free(opcgen_message[i]);
    free(opcgen_msg);
}

char *opcgen_init(unsigned long items) {
    strcpy(opcgen_xmlns," xmlns=\"http://opcfoundation.org/webservices/XMLDA/1.0/\"\n");
    strcat(opcgen_xmlns,"xmlns:enc='http://www.w3.org/2001/12/soap-encoding'\n");
#ifndef ORACLE_PARSER
    strcat(opcgen_xmlns,"xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'\n");
    strcat(opcgen_xmlns,"xmlns:xsd='http://www.w3.org/2001/XMLSchema'\n");
    strcat(opcgen_xmlns,"xsi:schemaLocation=\"http://opcfoundation.org/webservices/XMLDA/1.0/ ../xml.files/opc.xsd\" ");
#else /* oracle benchmark */
    strcat(opcgen_xmlns,"xmlns:xsi='http://www.w3.org/2000/08/XMLSchema-instance'\n");
    strcat(opcgen_xmlns,"xmlns:xsd='http://www.w3.org/2000/08/XMLSchema'\n");
    strcat(opcgen_xmlns,"xsi:schemaLocation=\"http://opcfoundation.org/webservices/XMLDA/1.0/ ../xml.files/opc-oracle.xsd\" ");
#endif
    opcgen_reader();
    opcgen_max_items=items;    
    opcgen_max_subitems = (long int)log((double)items);
    
    opcgen_msg_size = opcgen_max_message_size + (opcgen_max_items+1)*(opcgen_max_subitems+1)*opcgen_max_submessage_size;
    opcgen_msg = (char*)malloc(opcgen_msg_size);
    if (!opcgen_msg) {
	fprintf(stderr,"Can't allocate %u bytes of memory\n",opcgen_msg_size);
	exit(0);
    }
    return opcgen_msg;
}

void opcgen_deinit() {
    opcgen_freemem();
}

unsigned long opcgen() {
    unsigned long i,j;
    unsigned long msg,rpt=0,rptpos,rpt2=0,rptpos2;
    char *s,*stmp;
    msg=rnd_int_max(opcgen_messages);
    s=opcgen_message[msg];
    
    strcpy(opcgen_msg,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    for (i=0,j=strlen(opcgen_msg);s[i];i++) {
//	printf("%u - %u : %lu, ",i,j,opcgen_msg_size);
	switch(s[i]) {
	    case '#':
		opcgen_msg[j++]=rnd_digit();
	    break;
	    case '$':
		opcgen_msg[j++]=rnd_char();
	    break;
	    case '&':
		switch (s[++i]) {
		    case 'd':
			strcpy(opcgen_msg+j,rnd_datetime());
			j+=strlen(rnd_string);
		    break;
		    case 't':
			strcpy(opcgen_msg+j,rnd_duration());
			j+=strlen(rnd_string);
		    break;
		    case 'b':
			strcpy(opcgen_msg+j,rnd_boolean());
			j+=strlen(rnd_string);
		    break;
		    case 'p':
			strcpy(opcgen_msg+j,rnd_path());
			j+=strlen(rnd_string);
		    break;
		    case 'n':
			strcpy(opcgen_msg+j,rnd_name());
			j+=strlen(rnd_string);
		    break;
		    case 'f':
			strcpy(opcgen_msg+j,rnd_number_float());
			j+=strlen(rnd_string);
		    break;
		    case 'i':
			strcpy(opcgen_msg+j,rnd_number_unsigned());
			j+=strlen(rnd_string);
		    break;
		    case 's':
			strcpy(opcgen_msg+j,rnd_long_string(0));
			j+=strlen(rnd_string);
		    break;
		    case 'u':
			strcpy(opcgen_msg+j,rnd_uri());
			j+=strlen(rnd_string);
		    break;
		    case 'l':
			strcpy(opcgen_msg+j,rnd_last_type());
			j+=strlen(rnd_string);
		    break;
		    case 'q':
			strcpy(opcgen_msg+j,rnd_type());
			j+=strlen(rnd_string);
		    break;
		}
	    break;
	    case '@':
		strcpy(opcgen_msg+j,rnd_duration());
		j+=strlen(rnd_string);
	    break;
	    case '!':
		stmp=rnd_qualitystatus();
		strcpy(opcgen_msg+j,stmp);
		j+=strlen(stmp);
	    break;
	    case '?':
		stmp=rnd_type();
		strcpy(opcgen_msg+j,stmp);
		j+=strlen(stmp);
	    break;
	    case '[':
		if (rpt) {
		    rpt2=rpt;
		    rptpos2=rptpos;
		    rpt=rnd_int_max(opcgen_max_subitems)+1;
		} else {
		    rpt=rnd_int_max(opcgen_max_items)+1;
		}
		rptpos=i;
	    break;
	    case ']':
		if (rpt>0) {
		    i=rptpos;
		    rpt--;
		} else {
		    rpt=rpt2;
		    rptpos=rptpos2;
		    rpt2=0;
		}
	    break;
	    default:
		opcgen_msg[j++]=s[i];
	}
    }
    opcgen_msg[j]=0;
    return j;
}

