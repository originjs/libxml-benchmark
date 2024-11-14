#include <stdio.h>
#include <sys/time.h>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "tools.h"

XERCES_CPP_NAMESPACE_USE

// 释放文档的函数
static void xerces_free_doc(void* doc) {
    if (doc) {
        DOMDocument* xmlDoc = static_cast<DOMDocument*>(doc);
        xmlDoc->release();
    }
}

void initXML(struct TestData *td) {
    try {
        XMLPlatformUtils::Initialize();
        td->free_doc = xerces_free_doc;  // 设置释放函数
        td->is_sax_parser = 0;  // 设置为 DOM 解析器
    }
    catch (const XMLException& e) {
        char* message = XMLString::transcode(e.getMessage());
        printf("XML initialization error: %s\n", message);
        XMLString::release(&message);
        exit(1);
    }
}

void releaseXML(struct TestData *td) {
    try {
        XMLPlatformUtils::Terminate();
    }
    catch (const XMLException& e) {
        char* message = XMLString::transcode(e.getMessage());
        printf("XML termination error: %s\n", message);
        XMLString::release(&message);
    }
}

void* parseXML(struct TestData *td, unsigned long iter) {
    try {
        XercesDOMParser* parser = new XercesDOMParser();
        parser->setValidationScheme(XercesDOMParser::Val_Never);
        parser->setDoNamespaces(true);
        parser->setDoSchema(false);
        parser->setLoadExternalDTD(false);

        // 设置错误处理
        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);

        // 根据输入方式选择解析方法
        if (td->fn) {
            parser->parse(td->fn);
        } else {
            MemBufInputSource memBufIS((const XMLByte*)td->xml, 
                                     td->xmllen, 
                                     "memBuf");
            parser->parse(memBufIS);
        }

        // 获取文档所有权
        DOMDocument* doc = parser->adoptDocument();

        // 清理解析器和错误处理器
        delete parser;
        delete errHandler;

        return static_cast<void*>(doc);
    }
    catch (const XMLException& e) {
        char* message = XMLString::transcode(e.getMessage());
        printf("XML parsing error: %s\n", message);
        XMLString::release(&message);
        exit(1);
    }
    catch (...) {
        printf("Unexpected error during parsing\n");
        exit(1);
    }
    return nullptr;
}

void saveXML(struct TestData *td, void* doc) {
    try {
        DOMDocument* xmlDoc = static_cast<DOMDocument*>(doc);
        
        // 获取实现
        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        DOMImplementation *impl = 
            DOMImplementationRegistry::getDOMImplementation(tempStr);
        
        // 创建序列化器
        DOMLSSerializer *serializer = 
            ((DOMImplementationLS*)impl)->createLSSerializer();
        
        // 配置序列化器
        DOMConfiguration *conf = serializer->getDomConfig();
        conf->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
        
        // 创建输出目标
        XMLFormatTarget *target = 
            new LocalFileFormatTarget("output-test.rdf");
        DOMLSOutput *output = 
            ((DOMImplementationLS*)impl)->createLSOutput();
        output->setByteStream(target);
        
        // 序列化到文件
        serializer->write(xmlDoc, output);
        
        // 清理
        output->release();
        serializer->release();
        delete target;
    }
    catch (const XMLException& e) {
        char* message = XMLString::transcode(e.getMessage());
        printf("XML serialization error: %s\n", message);
        XMLString::release(&message);
        exit(1);
    }
    catch (...) {
        printf("Unexpected error during serialization\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    return Test(argc, argv);
}
