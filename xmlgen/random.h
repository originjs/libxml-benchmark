#ifndef _RANDOM_H
#define _RANDOM_H

#define rnd_seed 1


char rnd_string[512];
char rnd_qsize=15;
char rnd_q[15][32]={"bad","badConfigurationError","badNotConnected",
    "badDeviceFailure","badSensorFailure","badLastKnownValue",
    "badCommFailure","badOutOfService","uncertain","uncertainLastUsableValue",
    "uncertainSensorNotAccurate","uncertainEUExceeded","uncertainSubNormal",
    "good","goodLocalOverride"};

char last_type=0;
char rnd_tsize=16;
char rnd_t[16][32]={"duration","dateTime","time","date","boolean",
    "base64Binary","hexBinary","float","double","anyURI",
    "QName","nonNegativeInteger","decimal","integer","string","normalizedString"};

void rnd_init() {
    srand(rnd_seed);
}


char rnd_digit() {
    return rand()/(RAND_MAX/9)+'0';
}

unsigned long rnd_int_max(unsigned long max) {
    return rand()/(RAND_MAX/max);
}

long rnd_int_minmax(long min,long max) {
    return min+rand()/(RAND_MAX/(max-min));
}

double rnd_double(double max) {
    return max * rand() / RAND_MAX;
}

char rnd_char() {
    if (rnd_int_max(2))
	return 65 + rand()/(RAND_MAX/(91-65));
    else 
	return 97 + rand()/(RAND_MAX/(123-97));
}

char *rnd_path() {
    int i, size;
    
    size = rnd_int_max(64)+1;
    rnd_string[0]='/';
    for (i=1;i<size;i++) rnd_string[i]=rnd_char();
    rnd_string[i]=0;
    return rnd_string;
}

char *rnd_name() {
    int i, size;
    
    size = rnd_int_max(24)+1;
    for (i=0;i<size;i++) rnd_string[i]=rnd_char();
    rnd_string[i]=0;
    return rnd_string;
}

char *rnd_long_string(int c) {
    int i, size;
    
    if (c) size=c;
    else size = rnd_int_max(96)+1;
    
    for (i=0;i<size;i++) rnd_string[i]=rnd_char();
    rnd_string[i]=0;
    return rnd_string;
}

char *rnd_datetime() {
    sprintf(rnd_string,"%u-%02u-%02uT%02u:%02u:%02u.%07u+0%u:00",
	1997+rnd_int_max(6),rnd_int_max(12)+1,rnd_int_max(28)+1,
	rnd_int_max(24),rnd_int_max(59),rnd_int_max(59),
	rnd_int_max(9999999),rnd_int_max(8));
    return rnd_string;
}

char *rnd_time() {
    sprintf(rnd_string,"%02u:%02u:%02u.%07u+0%u:00",
	rnd_int_max(24),rnd_int_max(59),rnd_int_max(59),
	rnd_int_max(9999999),rnd_int_max(8));
    return rnd_string;
}

char *rnd_date() {
    sprintf(rnd_string,"%u-%02u-%02u",
	1997+rnd_int_max(6),rnd_int_max(12)+1,rnd_int_max(28)+1);
    return rnd_string;
}

char *rnd_boolean() {
    if (rnd_int_max(2))
	strcpy(rnd_string,"true");
    else
	strcpy(rnd_string,"false");
    return rnd_string;
}

char *rnd_number_unsigned() {
    sprintf(rnd_string,"%u",rnd_int_max(65535));
    return rnd_string;
}

char *rnd_number_float() {
    sprintf(rnd_string,"%lf",rnd_double(1));
    return rnd_string;
}

char *rnd_duration() {
    sprintf(rnd_string,"P%uY%uM%uDT%uH%uM%uS",
	rnd_digit()+1,rnd_int_max(11)+1,rnd_int_max(27)+1,
	rnd_int_max(24),rnd_int_max(59),rnd_int_max(59));
    return rnd_string;
}

char *rnd_qualitystatus() {
    return rnd_q[rnd_int_max(rnd_qsize)];
}

char *rnd_type() {
    last_type=rnd_int_max(rnd_tsize);
    strcpy(rnd_string,rnd_t[last_type]);
    return rnd_string;
}

char *rnd_xsdtype() {
    last_type=rnd_int_max(rnd_tsize);
    strcpy(rnd_string,"xsd:");
    strcpy(rnd_string+4,rnd_t[last_type]);
    return rnd_string;
}

char *rnd_uri() {
    int i,size;
    strcpy(rnd_string,"http://");

    size = rnd_int_max(8)+8;
    for (i=7;i<size;i++) rnd_string[i]=rnd_char();
    strcpy(rnd_string+i,".ru/");

    size = rnd_int_max(16)+i+4;
    for (i+=4;i<size;i++) rnd_string[i]=rnd_char();
    if (rnd_int_max(2)) {
	rnd_string[i++]='?';
	size = rnd_int_max(32)+i;
	for (;i<size;i++) rnd_string[i]=rnd_char();
    }
    rnd_string[i]=0;
    return rnd_string;
}

char rnd_hex() {
    int i;
    
    i = rnd_int_max(16);
    if (i<10) return ('0'+i);
    else return ('A'+(i-10));
}

char *rnd_hexbinary(int size) {
    int i;
    if (!size) size=256;
    for (i=0;i<size;i++) rnd_string[i]=rnd_hex();
    rnd_string[i]=0;
    return rnd_string;
}

char *rnd_last_type() {
    switch (last_type) {
	case 0:
	    rnd_duration();
	break;
	case 1:
	    rnd_datetime();
	break;
	case 2:
	    rnd_time();
	break;
	case 3:
	    rnd_date();
	break;
	case 4:
	    rnd_boolean();
	break;
	case 5:
	case 6:
	    rnd_hexbinary(0);
	break;
	case 7:
	case 8:
	    rnd_number_float();
	break;
	case 9:
	    rnd_uri();
	break;
	case 10:
	    rnd_xsdtype();
	break;
	case 11:
	case 12:
	case 13:
	    rnd_number_unsigned();
	break;
	default:
	    rnd_long_string(0);
    }
    return rnd_string;
}

#endif /* _RANDOM_H */
