#include <stdio.h>
#include <sys/time.h>
#include "pugixml.hpp"
#include "tools.h"

void initXML(struct TestData *td) {
    // pugixml 不需要显式初始化
}

void releaseXML(struct TestData *td) {
    // pugixml 不需要显式清理
}

void parseXML(struct TestData *td, unsigned long iter) {
    pugi::xml_document doc;
    pugi::xml_parse_result result;

    // 根据是否有文件名选择加载方式
    if (td->fn) {
        result = doc.load_file(td->fn);
    } else {
        result = doc.load_buffer(td->xml, td->xmllen);
    }

    // 检查解析结果
    if (!result) {
        printf("Error parsing document: %s\n", result.description());
        exit(0);
    }

    // doc 对象会在函数结束时自动释放
}

int main(int argc, char *argv[]) {
    return Test(argc, argv);
}
