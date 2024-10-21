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

    xmlSecSignatureDestroy(signature);
    
    xmlSecDSigCtxDestroy(dsigCtx);
    xmlSecSimpleKeysMngrDestroy(keysMngr);
    xmlSecDSigCtxDestroy(vdsigCtx);
    xmlSecSimpleKeysMngrDestroy(vkeysMngr);
    
    xmlSecEncCtxDestroy(encCtx);
    xmlSecEncCtxDestroy(decCtx);

    xmlSecShutdown();

    xmlCleanupParser();

    RAND_cleanup();
    ERR_clear_error();
}


xmlNodePtr	encKey;

void initXML_Security(struct TestData *td) {
    int rndseed = 0;
    xmlNodePtr	si_node,cm_node,sm_node,r_node,dm_node,t_node;
    xmlNodePtr	em_node,cv_node,ki_node,kn_node;
    xmlNodePtr	node_k_em,node_k_cv,node_k_ki,node_k_kn;
    
	/* Initialising OpenSSL */
    while (RAND_status() != 1) {
	RAND_seed(&rndseed, sizeof(rndseed));
    }

	/* Initialising XML Security */
    xmlSecInit();    

    keysMngr = xmlSecSimpleKeysMngrCreate();    
    if(keysMngr == NULL) {
	fprintf(stderr, "Error: failed to create keys manager!\n");
	exit(1);
    }

    key=xmlSecSimpleKeysMngrLoadPemKey(keysMngr, keyfile, 0/*password*/, 0/*password callback*/, 1/*private key*/);
    if(key == NULL) {
	fprintf(stderr, "Error: failed to load key from \"%s\"\n", keyfile);
	exit(1);
    }
    key->name = xmlStrdup(BAD_CAST "rsakey");

    vkeysMngr = xmlSecSimpleKeysMngrCreate();    
    if(vkeysMngr == NULL) {
	fprintf(stderr, "Error: failed to create keys manager!\n");
	exit(1);
    }

    crt=xmlSecSimpleKeysMngrLoadPemKey(vkeysMngr, crtfile, 0/*password*/, 0/*password callback*/, 0/*private key*/);
    if(crt == NULL) {
	fprintf(stderr, "Error: failed to load certificate from \"%s\"\n", crtfile);
	exit(1);
    }
    crt->name = xmlStrdup(BAD_CAST "rsapubkey");

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

	/* Creating symmetric DES key */    
    skey = xmlSecKeyCreate(xmlSecDesKey, xmlSecKeyOriginDefault);
    if(skey == NULL) {
	fprintf(stderr, "Error: failed to create des3 key (init structure)\n"); 
	exit(1);
    }        
    
    if (xmlSecDesKeyGenerate(skey, NULL, 24)<0) {
	fprintf(stderr, "Error: failed to create des3 key (generate)\n"); 
	exit(1);
    }    

    skey->name = xmlStrdup(BAD_CAST "skey");

    if (xmlSecSimpleKeysMngrAddKey(vkeysMngr, skey)<0) {
	fprintf(stderr, "Error: failed to add des3 key into KeyManager\n"); 
	exit(1);
    }

	/* Creating Signature */    
    signature = xmlSecSignatureCreate(NULL);
    if(signature == NULL) {
    	fprintf(stderr,"Error: failed to create signature node\n");
	exit(1);
    }
    
    si_node = xmlSecSignatureAddSignedInfo(signature, NULL);
    if(si_node == NULL) {
    	fprintf(stderr,"Error: failed to create SignedInfo node\n");
	exit(1);
    }

    cm_node = xmlSecSignedInfoAddC14NMethod(si_node, xmlSecC14NInclusive /* algorithm */);
    if(cm_node == NULL) {
    	fprintf(stderr,"Error: failed to create CanocalizationMethods node\n");
	exit(1);
    }
    
    sm_node = xmlSecSignedInfoAddSignMethod(si_node, xmlSecSignRsaSha1 /* key type */);
    if(sm_node == NULL) {
    	fprintf(stderr,"Error: failed to create SignMethod node\n");
	exit(1);
    }

    r_node = xmlSecSignedInfoAddReference(si_node,0/*node_id*/,0/*node_uri*/,0/*node_type*/);
    if(r_node == NULL) {
    	fprintf(stderr,"Error: failed to create Reference node\n");
	exit(1);
    }

    t_node = xmlSecReferenceAddTransform(r_node, xmlSecTransformEnveloped /* Signing enveloped element */);
    if(t_node == NULL) {
    	fprintf(stderr,"Error: failed to add enveloped transform\n");
	exit(1);
    }

    dm_node = xmlSecReferenceAddDigestMethod(r_node, xmlSecDigestSha1);
    if(dm_node == NULL) {
    	fprintf(stderr,"Error: failed to add DigestMethod node\n");
	exit(1);
    }

	/* Creating encryption Node */

    enc = xmlSecEncDataCreate(NULL, xmlSecEncTypeElement, NULL, NULL);
    if(enc == NULL) {
	fprintf(stderr, "Error: EncryptedData node creation failed\n");
	exit(1);
    }

    em_node=xmlSecEncDataAddEncMethod(enc, xmlSecEncDes3Cbc);
    if(em_node == NULL) {
	fprintf(stderr, "Error: failed to add EncryptionMethod node\n");
	exit(1);
    }

    cv_node = xmlSecEncDataAddCipherValue(enc);    
    if(cv_node == NULL) {
	fprintf(stderr, "Error: failed to add CipherValue node\n");
	exit(1);
    }

    ki_node = xmlSecEncDataAddKeyInfo(enc);
    if(ki_node == NULL) {
	fprintf(stderr, "Error: failed to add KeyInfo node\n");
	exit(1);
    }

/*    kn_node = xmlSecKeyInfoAddKeyName(ki_node);
    if(kn_node == NULL) {
	fprintf(stderr, "Error: failed to add KeyName node\n");
	exit(1);
    }*/

    encKey = xmlSecKeyInfoAddEncryptedKey(ki_node, NULL, NULL, NULL);
    if(encKey == NULL) {
	fprintf(stderr, "Error: failed to add EncryptedKey node\n");
	exit(1);
    }
    
    node_k_em = xmlSecEncDataAddEncMethod(encKey, xmlSecEncRsaPkcs1);
    if(node_k_em == NULL) {
	fprintf(stderr, "Error: failed to add EncryptedMethod node to EncryptedKey\n");
	exit(1);
    }

    node_k_cv = xmlSecEncDataAddCipherValue(encKey);    
    if(node_k_cv == NULL) {
	fprintf(stderr, "Error: failed to add CipherValue node to EncryptedKey \n");
	exit(1);
    }

    node_k_ki = xmlSecEncDataAddKeyInfo(encKey);
    if(node_k_ki == NULL) {
	fprintf(stderr, "Error: failed to add KeyInfo node to EncryptedKey\n");
	exit(1);
    }

    node_k_kn = xmlSecKeyInfoAddKeyName(node_k_ki);
    if(node_k_kn == NULL) {
	fprintf(stderr, "Error: failed to add KeyName node to EncryptedKey\n");
	exit(1);
    }
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
    xmlSecDSigResultPtr result;
    
    node=xmlCopyNode(signature,1);

    if (!node) {
	fprintf(stderr,"Error: failed copy Signature Node!\n");
	exit(1);
    }
    
    if(xmlAddChild(xmlDocGetRootElement(doc), node) == NULL) {
    	fprintf(stderr,"Error: failed to add Signature into the Document!\n");
	exit(1);
    }
    
    if (xmlSecDSigGenerate(dsigCtx, NULL, key, node, &result)<0) {
    	fprintf(stderr,"Error: signature failed\n");
	exit(1);
    }     

    xmlSecDSigResultDestroy(result);

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
    xmlSecDSigResultPtr result;

    node = xmlSecFindNode(xmlDocGetRootElement(doc), BAD_CAST "Signature", xmlSecDSigNs);
    if(node == NULL) {
        fprintf(stderr,"Error: failed to find Signature node in Document\n");
	exit(1);
    }    
     
    if (xmlSecDSigValidate(vdsigCtx, NULL, crt, node, &result)<0) {
    	fprintf(stderr,"Error: Verification failed (processing error)\n");
	exit(1);
    }     
    
    if (result->result!=xmlSecTransformStatusOk) {
    	fprintf(stderr,"Error: Verification failed (verification error)\n");
	exit(1);
    }
    
//    xmlSecDSigResultDebugDump(result, stdout); 
    
    xmlSecDSigResultDestroy(result);
}

/* In case if EncryptedData "type" attribute isn't specified!

void encryptXML(struct TestData *td, unsigned long iter) { 
    xmlDocPtr doctmp;
    xmlNodePtr node,enode;
    xmlSecEncResultPtr result = 0;
    
    node=xmlCopyNode(enc,1);
    enode=xmlDocGetRootElement(doc);

	// If this 2 commands place in other direction, - not all subnodes
	// of node will attached to right doc. Why?
    xmlSetTreeDoc(node,doc);
    xmlDocSetRootElement(doc, node);

    if (xmlSecEncryptXmlNode(encCtx, NULL, skey, node, enode, &result)<0) {
	fprintf(stderr, "Error: Encryption Failed!\n");
	exit(1);
    }
    xmlSecEncResultDestroy(result);
    xmlFreeNode(enode);
}
*/

void encryptXML(struct TestData *td, unsigned long iter) { 
    xmlDocPtr doctmp;
    xmlNodePtr node,enode;
    xmlSecEncResultPtr result = 0;
    
    node=xmlCopyNode(enc,1);
    enode=xmlDocGetRootElement(doc);
    xmlAddChild(enode,node);

    if (xmlSecEncryptXmlNode(encCtx, NULL, skey, node, enode, &result)<0) {
	fprintf(stderr, "Error: Encryption Failed!\n");
	exit(1);
    }
    xmlSecEncResultDestroy(result);

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
    xmlSecEncResultPtr result = 0;

    if (xmlSecDecrypt(decCtx, NULL, NULL, xmlDocGetRootElement(doc), &result)<0) {
	fprintf(stderr, "Error: Decryption Failed!\n");
	exit(1);
    }
    
    node = xmlSecFindNode(xmlDocGetRootElement(doc), BAD_CAST "EncryptedData", xmlSecEncNs);    
    if (node==NULL) {
	fprintf(stderr,"Error: Can't find EncryptedData node\n");
	exit(0);
    }
    xmlUnlinkNode(node);
    xmlFreeNode(node);

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
