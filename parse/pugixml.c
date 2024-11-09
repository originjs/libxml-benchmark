#include <stdio.h>
#include <sys/time.h>
#include "pugixml.hpp"
#include "tools.h"

static void pugixml_free_doc(void* doc) {
    delete static_cast<pugi::xml_document*>(doc);
}

void initXML(struct TestData *td) {
    td->free_doc = pugixml_free_doc;  // 设置释放函数
}

void releaseXML(struct TestData *td) {
    // pugixml 不需要显式清理
}

void* parseXML(struct TestData *td, unsigned long iter) {  // 返回类型改为 void*
    // 创建文档对象并分配到堆上,由调用者负责释放
    pugi::xml_document* doc = new pugi::xml_document();
    pugi::xml_parse_result result;

    // 根据是否有文件名选择加载方式
    if (td->fn) {
        result = doc->load_file(td->fn);
    } else {
        result = doc->load_buffer(td->xml, td->xmllen);
    }

    // 检查解析结果
    if (!result) {
        printf("Error parsing document: %s\n", result.description());
        delete doc;
        exit(0);
    }

    return static_cast<void*>(doc);  // 转换为 void* 返回
}

void saveXML(struct TestData *td, void* doc) {  // 参数类型改为 void*
    // 保存到文件,启用格式化
    pugi::xml_document* xml_doc = static_cast<pugi::xml_document*>(doc);
    bool result = xml_doc->save_file("output-test.rdf", "  ", pugi::format_default | pugi::format_indent);
    if (!result) {
        printf("Error saving document!\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    return Test(argc, argv);
}
