#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGReference.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyRSA.hpp>

#ifdef _APACHE_XML_SECURITY_1
#include <xsec/xenc/XENCCipher.hpp>
#include <xsec/xenc/XENCEncryptedData.hpp>
#include <xsec/xenc/XENCEncryptedKey.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoSymmetricKey.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>

#include <openssl/rand.h>
#endif /* _APACHE_XML_SECURITY_1 */

#include <xsec/enc/XSECCryptoException.hpp>

#include "xerces-dom.h"

#include "tools.h"

#define keyfile "../ssl/test.key"
#define crtfile "../ssl/test.crt"


XSEC_USING_XERCES(DOMImplementation);
XSEC_USING_XERCES(DOMWriter);
XSEC_USING_XERCES(XMLPlatformUtils);
XSEC_USING_XERCES(XMLException);
XSEC_USING_XERCES(DOMImplementationRegistry);
XSEC_USING_XERCES(MemBufFormatTarget);
XSEC_USING_XERCES(DOMImplementationLS);
XSEC_USING_XERCES(XercesDOMParser);
XSEC_USING_XERCES(MemBufInputSource);

#ifdef _APACHE_XML_SECURITY_1
XERCES_CPP_NAMESPACE_USE
#endif /* _APACHE_XML_SECURITY_1 */

XSECProvider prov;

OpenSSLCryptoKeyRSA *key;
OpenSSLCryptoKeyRSA *vkey;

#ifdef _APACHE_XML_SECURITY_1
OpenSSLCryptoSymmetricKey *skey;
unsigned char keyBuf[24];
#endif /* _APACHE_XML_SECURITY_1 */

XercesDOMParser *parser;
DOMImplementation *dom; 
DOMDocument *signdoc;
DOMElement *sigNode;

DOMWriter *writer;
XMLFormatTarget *xft;

void initXML(struct TestData *td) {
    XMLPlatformUtils::Initialize();
    XSECPlatformUtils::Initialise();

    dom = DOMImplementationRegistry::getDOMImplementation(MAKE_UNICODE_STRING("Core"));
/*
    writer = ((DOMImplementationLS*)dom)->createDOMWriter();
    xft = new MemBufFormatTarget();
*/
}


void releaseXML(struct TestData *td) {
    delete key;
    delete vkey;

#ifdef _APACHE_XML_SECURITY_1
    delete skey;
#endif /* _APACHE_XML_SECURITY_1 */
    
//    delete sigNode; SEGFAULT
//    delete signdoc;

/*    
    delete xft;
    delete writer;
*/
    
    XSECPlatformUtils::Terminate();
//    XMLPlatformUtils::Terminate(); SEGFAULT
}


void initXML_Security(struct TestData *td) {
/*
    signdoc = dom->createDocument(0, MAKE_UNICODE_STRING("Signature"), NULL);  
    DSIGSignature *sig = prov.newSignature();
    sigNode = sig->createBlankSignature(signdoc, CANON_C14N_COM, SIGNATURE_RSA, HASH_SHA1);
    DSIGReference * ref = sig->createReference(MAKE_UNICODE_STRING(""));
    ref->appendEnvelopedSignatureTransform();
*/    

#ifdef _APACHE_XML_SECURITY_1
	// Initialising Random Generator
    if (RAND_status() != 1) {
	fprintf(stderr,"OpenSSL random generation not properly initialised");
	exit(1);
    }
	// Generating Symmetric Key
    if (RAND_bytes(keyBuf, 24) == 0) {
	fprintf(stderr,"Error obtaining 24 bytes of random from OpenSSL");
	exit(1);
    }
 
    skey = new OpenSSLCryptoSymmetricKey(XSECCryptoSymmetricKey::KEY_3DES_192);
    skey->setKey(keyBuf, 24);
#endif /* _APACHE_XML_SECURITY_1 */


    EVP_PKEY *okey = LoadKey(keyfile, NULL, 1);
    if (!okey) {
	fprintf(stderr,"Error: can't load private key\n");
	exit(1);
    }
    key = new OpenSSLCryptoKeyRSA(okey);
    EVP_PKEY_free(okey);

    okey = LoadKey(crtfile, NULL, 0);
    if (!okey) {
	fprintf(stderr,"Error: can't load certificate\n");
	exit(1);
    }
    vkey = new OpenSSLCryptoKeyRSA(okey);
    EVP_PKEY_free(okey);
}


void parseXML(struct TestData *td, unsigned long iter) {
    const char id[5]="ID1\0";
    MemBufInputSource *buffer;

    parser = new XercesDOMParser;
    buffer=new MemBufInputSource((XMLByte*)td->xml,td->xmllen,(const char*)&id);
    buffer->setCopyBufToStream(false);
    parser->parse(*buffer);
    delete buffer;
}


void signXML(struct TestData *td, unsigned long iter) { 
    DOMDocument *doc = parser->getDocument();
    DOMElement *rootElem = doc->getDocumentElement();
/*
    DOMNode *node = doc->importNode(sigNode,1);
    rootElem->appendChild(node);
    DSIGSignature *sig = prov.newSignatureFromDOM(doc);
    try {
	sig->load();
	sig->setSigningKey(key->clone());    
	sig->sign();
    }
*/
    DSIGSignature *sig = prov.newSignature();
    DOMNode *node = sig->createBlankSignature(doc, CANON_C14N_NOC, SIGNATURE_RSA, HASH_SHA1);
    DSIGReference * ref = sig->createReference(MAKE_UNICODE_STRING(""));
    ref->appendEnvelopedSignatureTransform();
    rootElem->appendChild(node);
    try {
	sig->setSigningKey(key->clone());    
	sig->sign();
    }
    catch (XSECException &e)
    {
	fprintf(stderr,"Error signing: %s\n", (char*)e.getMsg());
	exit(1);
    }
    catch (XSECCryptoException &e) {
    	fprintf(stderr,"Error signing: %s\n", e.getMsg());
	exit(1);
    }

/*    
    if (iter==td->iterations) 
    {
        XMLByte *mem;
	writer->writeNode(xft,*doc);
	mem=(XMLByte*)((MemBufFormatTarget*)xft)->getRawBuffer();
	puts((char*)mem);
	((MemBufFormatTarget*)xft)->reset();
    }
*/
    prov.releaseSignature(sig);
}

void verifyXML(struct TestData *td, unsigned long iter) { 
    DOMDocument *doc = parser->getDocument();

    DSIGSignature *vsig = prov.newSignatureFromDOM(doc);

    try {
	vsig->load();
	vsig->setSigningKey(vkey->clone());

	if (!vsig->verify()) {
	    fprintf(stderr,"Error: Verification Failed\n");
	    exit(1);
	}
    }
    catch (XSECException &e)
    {
	fprintf(stderr,"Error validating: %s\n", (char*)e.getMsg());
	exit(1);
    }
    catch (XSECCryptoException &e) {
    	fprintf(stderr,"Error validating: %s\n", e.getMsg());
	exit(1);
    }
    prov.releaseSignature(vsig);

    delete parser;
}

void encryptXML(struct TestData *td, unsigned long iter) { 
#ifdef _APACHE_XML_SECURITY_1
	DOMDocument *doc = parser->getDocument();
	DOMElement *rootElem = doc->getDocumentElement();

	try {
		/* Create the cipher object that we need */
		XENCCipher *cipher;
		cipher = prov.newCipher(doc);
		cipher->setKey(skey->clone());
		cipher->encryptElement(rootElem, ENCRYPT_3DES_CBC);
		cipher->setKEK(vkey->clone());

		XENCEncryptedKey * encryptedKey = cipher->encryptKey(keyBuf, 24, ENCRYPT_RSA_15);
		XENCEncryptedData * encryptedData = cipher->getEncryptedData();
		encryptedData->appendEncryptedKey(encryptedKey);
		prov.releaseCipher(cipher);
	}
	catch (XSECException &e)
	{
	    fprintf(stderr, "Error encrypting: %s\n",e.getMsg());
	    exit(1);
	}
/*
	if (iter==0) 
	{
    	    XMLByte *mem;
	    writer->writeNode(xft,*doc);
	    mem=(XMLByte*)((MemBufFormatTarget*)xft)->getRawBuffer();
	    puts((char*)mem);
	    ((MemBufFormatTarget*)xft)->reset();
	}
*/
#endif /* _APACHE_XML_SECURITY_1 */

    return;
}

void decryptXML(struct TestData *td, unsigned long iter) { 
#ifdef _APACHE_XML_SECURITY_1
    DOMDocument *doc = parser->getDocument();
    
    try {    
	XENCCipher *cipher;
	cipher = prov.newCipher(doc);
	cipher->setKEK(key->clone());
	DOMNode *encryptedNode = findXENCNode(doc, "EncryptedData");

	    // As for CVS 08.02.2004 randomly drops core... Offten.. Don't vary on size...
	cipher->decryptElement((DOMElement *) encryptedNode);

	    // Here is problem. We are realsing Root Element, New Element is not set as root.
	    // Fix for this silly thing
	if (!doc->getDocumentElement()) {
	    DOMNode *tmpnode=doc->getFirstChild();
	    while ((tmpnode)&&(tmpnode->getNodeType()!=DOMNode::ELEMENT_NODE)) tmpnode=tmpnode->getNextSibling();
	    if (tmpnode) {
		doc->removeChild(tmpnode);
		doc->appendChild(tmpnode);
	    }
	    else {
		fprintf(stderr,"Error: Broken DOM tree after encryption/decryption!\n");
	        exit(1);
	    }
	}
	prov.releaseCipher(cipher);
    }
    catch (XSECException &e)
    {
	fprintf(stderr, "Error decrypting: %s\n",e.getMsg());
	exit(1);
    }
/*
    if (iter==0) 
    {
        XMLByte *mem;
	writer->writeNode(xft,*doc);
	mem=(XMLByte*)((MemBufFormatTarget*)xft)->getRawBuffer();
	puts((char*)mem);
	((MemBufFormatTarget*)xft)->reset();
    }
*/
#endif /* _APACHE_XML_SECURITY_1 */
    return;
}


int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
