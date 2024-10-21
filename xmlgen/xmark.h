#include "unix.h"

#define xmark_kb_size 20000
#define xmark_kb_min  250000

static char *xmarkBuffer=NULL, *xmarkBufferPtr=NULL;
static void *xmarkSave=NULL;

int xmark_printf(FILE *stream, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    xmarkBufferPtr+=vsprintf(xmarkBufferPtr,format,ap);
    va_end(ap);
}

static ObjDesc *xmarkRoot;

char *xmark_init(unsigned long size) {
    scale_factor=(1.*size/10000);
    if (correction) scale_factor=correction(scale_factor);

    xmlprintf=xmark_printf;
    
    size*=xmark_kb_size;
    if (size<xmark_kb_min) size=xmark_kb_min;
    xmarkBuffer = (char*)malloc(size*sizeof(char));
    xmarkSave = malloc(sizeof(objs));
    if ((!xmarkBuffer)||(!xmarkSave)) {
	fprintf(stderr,"Can't allocate memory!");
	exit(1);
    }
    memcpy(xmarkSave,objs,sizeof(objs));

    return xmarkBuffer;
}

void xmark_deinit() {
    if (xmarkBuffer) free(xmarkBuffer);
    if (xmarkSave) free(xmarkSave);
}

int xmark(int dtd) {
    int document_type;
    if (dtd) document_type=2;
    else document_type=1;
    xmarkBufferPtr=xmarkBuffer;

    memcpy(objs,xmarkSave,sizeof(objs));
    AlignObjs();
    xmarkRoot=objs+1;

    FixSetSize(xmarkRoot);
    ClearFlags();
    FixReferenceSets(xmarkRoot);
    ClearFlags();
    CheckRecursion();
    ClearFlags();
    if (InitHook) InitHook();
    Preamble(document_type);
    GenSubtree(xmarkRoot);
    return xmarkBufferPtr-xmarkBuffer;
}

/* main are here, 
Functions: Usage should be removed 
Symbols: Debug should be removed
*/
