#include <stdio.h>
#include <sys/time.h>
#include <tinyxml2.h>
#include "tools.h"

using namespace tinyxml2;

static void tinyxml2_free_doc(void* doc) {
    delete static_cast<XMLDocument*>(doc);
}

void initXML(struct TestData *td) {
    td->free_doc = tinyxml2_free_doc;
    td->is_sax_parser = 0;  // 设置为 DOM 解析器
}

void releaseXML(struct TestData *td) {
    // TinyXML-2 不需要显式清理
}

void* parseXML(struct TestData *td, unsigned long iter) {
    XMLDocument* doc = new XMLDocument();
    XMLError result;
    
    if (td->fn) {
        result = doc->LoadFile(td->fn);
    } else {
        result = doc->Parse(td->xml, td->xmllen);
    }

    if (result != XML_SUCCESS) {
        printf("Error parsing document: %d\n", result);
        delete doc;
        exit(0);
    }

    return static_cast<void*>(doc);
}

void saveXML(struct TestData *td, void* doc) {
    XMLDocument* xml_doc = static_cast<XMLDocument*>(doc);
    XMLError result = xml_doc->SaveFile("output-test.rdf");
    
    if (result != XML_SUCCESS) {
        printf("Error saving document!\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    return Test(argc, argv);
} 