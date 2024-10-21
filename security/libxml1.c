#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include <libxml/xmlmemory.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

#include <openssl/err.h>
#include <openssl/rand.h>

#include <xmlsec/xmlsec.h>
#include <xmlsec/xmldsig.h> 
#include <xmlsec/xmlenc.h> 
#include <xmlsec/keys.h>
#include <xmlsec/keysmngr.h>
#include <xmlsec/transforms.h>
#include <xmlsec/xmltree.h>
#include <xmlsec/crypto.h>
#include <xmlsec/templates.h>


#include "libxml1.h"

#include "tools.h"

#define keyfile "../ssl/test.key"
#define crtfile "../ssl/test.crt"

xmlDocPtr 		doc = 0;
xmlSecKeysMngrPtr	keysMngr = 0; 
xmlSecKeysMngrPtr	vkeysMngr = 0; 
xmlSecDSigCtxPtr 	dsigCtx = 0;
xmlSecDSigCtxPtr 	vdsigCtx = 0;
xmlSecEncCtxPtr 	encCtx = 0;
xmlSecEncCtxPtr 	decCtx = 0;
xmlNodePtr		signature = 0;
xmlNodePtr		enc = 0;
xmlSecKeyPtr		key,crt,skey;

void initXML(struct TestData *td) {
    xmlInitParser();
}

void releaseXML(struct TestData *td) {
    xmlFreeDoc(doc);    

    xmlFreeNode(signature);
    
    xmlSecDSigCtxDestroy(dsigCtx);
    xmlSecKeysMngrDestroy(keysMngr);
    xmlSecDSigCtxDestroy(vdsigCtx);
    xmlSecKeysMngrDestroy(vkeysMngr);
    
    xmlSecEncCtxDestroy(encCtx);
    xmlSecEncCtxDestroy(decCtx);

    xmlSecCryptoShutdown();
    xmlSecCryptoAppShutdown();
    xmlSecShutdown();

    xmlCleanupParser();
}


xmlNodePtr	encKey;

void initXML_Security(struct TestData *td) {
    xmlNodePtr	si_node,cm_node,sm_node,r_node,dm_node,t_node;
    xmlNodePtr	em_node,cv_node,ki_node,kn_node;
    xmlNodePtr	node_k_em,node_k_cv,node_k_ki,node_k_kn;
    

    /* Init xmlsec library */
    if(xmlSecInit() < 0) {
	fprintf(stderr, "Error: xmlsec initialization failed.\n");
	exit(1);
    }

#ifdef XMLSEC_CRYPTO_DYNAMIC_LOADING
    if(xmlSecCryptoDLLoadLibrary(BAD_CAST XMLSEC_CRYPTO) < 0) {
	fprintf(stderr, "Error: unable to load default xmlsec-crypto library.\n");
	exit(1);	
    }
#endif /* XMLSEC_CRYPTO_DYNAMIC_LOADING */

    /* Init crypto library */
    if(xmlSecCryptoAppInit(NULL) < 0) {
	fprintf(stderr, "Error: crypto initialization failed.\n");
	exit(1);
    }

    /* Init xmlsec-crypto library */
    if(xmlSecCryptoInit() < 0) {
	fprintf(stderr, "Error: xmlsec-crypto initialization failed.\n");
	exit(1);
    }

	/* Initialising XML Security */

    keysMngr = load_rsa_keys(keyfile,crtfile,"rsakey");
    if(keysMngr == NULL) {
	fprintf(stderr, "Error: loading private key!\n");
	exit(1);
    }

    vkeysMngr = load_rsa_keys(crtfile,NULL,"rsapubkey");
    if(vkeysMngr == NULL) {
	fprintf(stderr, "Error: loading public key!\n");
	exit(1);
    }

//    keysMngr->allowedOrigins = xmlSecKeyOriginKeyManager | xmlSecKeyOriginKeyName;
//    vkeysMngr->allowedOrigins = xmlSecKeyOriginKeyManager | xmlSecKeyOriginKeyName;

    dsigCtx = xmlSecDSigCtxCreate(keysMngr);
    if(dsigCtx == NULL) {
    	fprintf(stderr,"Error: failed to create dsig context\n");
	exit(1);
    }                

    vdsigCtx = xmlSecDSigCtxCreate(vkeysMngr);
    if(dsigCtx == NULL) {
    	fprintf(stderr,"Error: failed to create dsig context\n");
	exit(1);
    }                

    encCtx = xmlSecEncCtxCreate(vkeysMngr);
    if(encCtx == NULL) {
	fprintf(stderr, "Error: failed to create encryption context\n");
	exit(1);
    }

    decCtx = xmlSecEncCtxCreate(keysMngr);
    if(encCtx == NULL) {
	fprintf(stderr, "Error: failed to create encryption context\n");
	exit(1);
    }

	/* Creating symmetric Triple DES key (24 * 8 = 192) */    
    skey = xmlSecKeyGenerate(xmlSecKeyDataDesId, 192, xmlSecKeyDataTypeSession);
    if(skey == NULL) {
	fprintf(stderr, "Error: failed to create des3 key (init structure)\n"); 
	exit(1);
    }        
    encCtx->encKey=skey;
//    encCtx->encKey,name = xmlStrdup(BAD_CAST "skey");

	/* Creating Signature */    

#ifdef XMLSEC_CRYPTO_DYNAMIC_LOADING
    signature = xmlSecTmplSignatureCreate(NULL, xmlSecTransformExclC14NId, xmlSecTransformRsaSha1Id, NULL);
#else
    signature = xmlSecTmplSignatureCreate(NULL, xmlSecTransformExclC14NId, xmlSecOpenSSLTransformRsaSha1Id, NULL);
#endif
    if (!signature) {
	fprintf(stderr, "Error: Signature node creation failed\n");
	exit(1);
    }

    r_node = xmlSecTmplSignatureAddReference(signature, xmlSecTransformSha1Id, NULL, NULL, NULL);
    if (!r_node) {
	fprintf(stderr, "Error: Reference node creation failed\n");
	exit(1);
    }

    if(xmlSecTmplReferenceAddTransform(r_node, xmlSecTransformEnvelopedId) == NULL) {
	fprintf(stderr, "Error: failed to add enveloped transform to reference\n");
	exit(1);
    }


	/* Creating encryption Node */
    enc = xmlSecTmplEncDataCreate(NULL, xmlSecTransformDes3CbcId, NULL, xmlSecTypeEncElement, NULL, NULL);
    if(enc == NULL) {
	fprintf(stderr, "Error: EncryptedData node creation failed\n");
	exit(1);
    }

    if(xmlSecTmplEncDataEnsureCipherValue(enc) == NULL) {
	fprintf(stderr, "Error: failed to add CipherValue node\n");
	exit(1);
    }

    ki_node = xmlSecTmplEncDataEnsureKeyInfo(enc, NULL);
    if(ki_node == NULL) {
	fprintf(stderr, "Error: failed to add key info\n");
	exit(1);
    }

#ifdef XMLSEC_CRYPTO_DYNAMIC_LOADING
    encKey = xmlSecTmplKeyInfoAddEncryptedKey(ki_node, xmlSecTransformRsaPkcs1Id, NULL, NULL, NULL);
#else
    encKey = xmlSecTmplKeyInfoAddEncryptedKey(ki_node, xmlSecOpenSSLTransformRsaPkcs1Id, NULL, NULL, NULL);
#endif
    if(encKey == NULL) {
	fprintf(stderr, "Error: failed to add key info\n");
	exit(1);
    }
    
    if(xmlSecTmplEncDataEnsureCipherValue(encKey) == NULL) {
	fprintf(stderr, "Error: failed to add CipherValue node\n");
	exit(1);
    }

    node_k_ki = xmlSecTmplEncDataEnsureKeyInfo(encKey, NULL);
    if(node_k_ki == NULL) {
	fprintf(stderr, "Error: failed to add key info\n");
	exit(1);
    }

    if(xmlSecTmplKeyInfoAddKeyName(node_k_ki, BAD_CAST "rsapubkey") == NULL) {
	fprintf(stderr, "Error: failed to add key name\n");
	exit(1);
    }

/*    node_k_em = xmlSecEncDataAddEncMethod(encKey, xmlSecEncRsaPkcs1);
    if(node_k_em == NULL) {
	fprintf(stderr, "Error: failed to add EncryptedMethod node to EncryptedKey\n");
	exit(1);
    }*/

}

void parseXML(struct TestData *td, unsigned long iter) {
    if (doc) {
	xmlFreeDoc(doc);    
    }

    doc=xmlParseMemory(td->xml,td->xmllen);
    if (!doc) {
        fprintf(stderr,"Error parsing document!\n");
        exit(1);
    }
}

xmlChar *mem;
int memsize;

void signXML(struct TestData *td, unsigned long iter) { 
    xmlNodePtr node;
     
    node=xmlCopyNode(signature,1);

    if (!node) {
	fprintf(stderr,"Error: failed copy Signature Node!\n");
	exit(1);
    }
    
    if(xmlAddChild(xmlDocGetRootElement(doc), node) == NULL) {
    	fprintf(stderr,"Error: failed to add Signature into the Document!\n");
	exit(1);
    }

    if(xmlSecDSigCtxSign(dsigCtx, node) < 0) {
    	fprintf(stderr,"Error: signature failed\n");
	exit(1);
    }     

    xmlSecDSigCtxFinalize(dsigCtx);
    if (xmlSecDSigCtxInitialize(dsigCtx,keysMngr)<0) {
    	fprintf(stderr,"Error: failed to reinitialize Sign Signature Context\n");
	exit(1);
    }              

/*    
    if (iter==td->iterations) {
        xmlDocDumpMemory(doc,&mem,&memsize);
	puts(mem);
	free(mem);
    }
*/
}

void verifyXML(struct TestData *td, unsigned long iter) { 
    xmlNodePtr node;

    node = xmlSecFindNode(xmlDocGetRootElement(doc), BAD_CAST "Signature", xmlSecDSigNs);
    if(node == NULL) {
        fprintf(stderr,"Error: failed to find Signature node in Document\n");
	exit(1);
    }    

    if(xmlSecDSigCtxVerify(vdsigCtx, node) < 0) {
        fprintf(stderr,"Error: signature verify\n");
	exit(1);
    }

    if(vdsigCtx->status != xmlSecDSigStatusSucceeded) {
	fprintf(stdout, "Signature is INVALID\n");
	exit(1);
    }    

    xmlSecDSigCtxFinalize(vdsigCtx);
    if (xmlSecDSigCtxInitialize(vdsigCtx,vkeysMngr)<0) {
    	fprintf(stderr,"Error: failed to reinitialize Verify Signature Context\n");
	exit(1);
    }              
}


void encryptXML(struct TestData *td, unsigned long iter) { 
    xmlDocPtr doctmp;
    xmlNodePtr node,enode;
    
    node=xmlCopyNode(enc,1);
    enode=xmlDocGetRootElement(doc);
    xmlAddChild(enode,node);

    if(xmlSecEncCtxXmlEncrypt(encCtx, node, enode) < 0) {
        fprintf(stderr,"Error: encryption failed\n");
	exit(1);
    }

    encCtx->encKey=NULL;
    xmlSecEncCtxFinalize(encCtx);
    if (xmlSecEncCtxInitialize(encCtx,vkeysMngr)<0) {
    	fprintf(stderr,"Error: failed to reinitialize Decrypt Context\n");
	exit(1);
    }              
    encCtx->encKey=skey;

/*
    if (iter==td->iterations) {
        xmlDocDumpMemory(doc,&mem,&memsize);
	puts(mem);
        free(mem);
    }
*/
}

void decryptXML(struct TestData *td, unsigned long iter) { 
    xmlNodePtr node;

    if((xmlSecEncCtxDecrypt(decCtx, xmlDocGetRootElement(doc)) < 0) || (decCtx->result == NULL)) {
        fprintf(stderr,"Error: decryption failed\n");
	exit(1);
    }

    node = xmlSecFindNode(xmlDocGetRootElement(doc), BAD_CAST "EncryptedData", xmlSecEncNs);    
    if (node==NULL) {
	fprintf(stderr,"Error: Can't find EncryptedData node\n");
	exit(0);
    }
    xmlUnlinkNode(node);
    xmlFreeNode(node);

    xmlSecEncCtxFinalize(decCtx);
    if (xmlSecEncCtxInitialize(decCtx,keysMngr)<0) {
    	fprintf(stderr,"Error: failed to reinitialize Decrypt Context\n");
	exit(1);
    }              
/*
    if (iter==td->iterations) {
        xmlDocDumpMemory(doc,&mem,&memsize);
	puts(mem);
        free(mem);
    }
*/
}

int main(int argc, char *argv[]) {
    return Test(argc,argv);
}
