#include <stdio.h>
#include <sys/time.h>

#define CHAR_SIZE 8
#include <xmlparser.h>
#include <stdio16.h>
#include <input.h>

#include "tools.h"

void initXML(struct TestData *td) {
    init_parser();
}

void releaseXML(struct TestData *td) {
    deinit_parser();
}

void parseXML(struct TestData *td, unsigned long iter) {
    Parser doc;
    FILE16 *data;
    XBit tree;
    InputSource source;
    
    doc=NewParser();
    data=MakeFILE16FromString(td->xml,td->xmllen,"r");
    source=SourceFromFILE16("membuf",data);
    ParserPush(doc,source);
    tree=ReadXTree(doc);
    while ((tree->type!=XBIT_start)&&(tree->type!=XBIT_end)&&(tree->type!=XBIT_eof)) {
	if (tree->type==XBIT_error) {
	    ParserPerror(doc, tree);
	    exit(1);
	}
	FreeXTree(tree);
	tree=ReadXTree(doc);
    }
    FreeXTree(tree);
    FreeParser(doc); /* Closes source and data */
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
