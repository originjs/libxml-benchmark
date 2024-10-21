#include <assert.h>
/**
 * load_rsa_keys:
 * @key_file:		the key filename.
 *
 * Creates simple keys manager and load RSA key from #key_file in it.
 * The caller is responsible for destroing returned keys manager using
 * @xmlSecKeysMngrDestroy.
 *
 * Returns the pointer to newly created keys manager or NULL if an error
 * occurs.
 */
 
xmlSecKeysMngrPtr 
load_rsa_keys(const char* key_file, const char* cert_file, const char* key_name) {
    xmlSecKeysMngrPtr mngr;
    xmlSecKeyPtr key;
    
    assert(key_file);
    assert(key_name);
    
    /* create and initialize keys manager, we use a simple list based
     * keys manager, implement your own xmlSecKeysStore klass if you need
     * something more sophisticated 
     */
    mngr = xmlSecKeysMngrCreate();
    if(mngr == NULL) {
	fprintf(stderr, "Error: failed to create keys manager.\n");
	return(NULL);
    }
    if(xmlSecCryptoAppDefaultKeysMngrInit(mngr) < 0) {
	fprintf(stderr, "Error: failed to initialize keys manager.\n");
	xmlSecKeysMngrDestroy(mngr);
	return(NULL);
    }    
    
    /* load private RSA key */

#if XMLSEC_VERSION_MINOR >= 2
    if (!cert_file)
	key = xmlSecCryptoAppKeyLoad(key_file, xmlSecKeyDataFormatCertPem /*Der,Binary,Unknown*/, NULL/*pwd*/, NULL/*pwd callback*/, NULL/*pwd callback ctx*/);
    else
#endif
	key = xmlSecCryptoAppKeyLoad(key_file, xmlSecKeyDataFormatPem /*Der,Binary,Unknown*/, NULL/*pwd*/, NULL/*pwd callback*/, NULL/*pwd callback ctx*/);
    
    if(key == NULL) {
        fprintf(stderr,"Error: failed to load rsa key from file \"%s\"\n", key_file);
        xmlSecKeysMngrDestroy(mngr);
        return(NULL);
    }
    
    if (cert_file) {
        if(xmlSecCryptoAppKeyCertLoad(key, cert_file, xmlSecKeyDataFormatPem) < 0) {
		fprintf(stderr,"Error: failed to load pem certificate \"%s\"\n", cert_file);
		return(NULL);
	}
    }
    

    /* set key name to the file name, this is just an example! */
    if(xmlSecKeySetName(key, BAD_CAST key_name) < 0) {
        fprintf(stderr,"Error: failed to set key name for key from \"%s\"\n", key_file);
        xmlSecKeyDestroy(key);	
	xmlSecKeysMngrDestroy(mngr);
	return(NULL);
    }
	
    /* add key to keys manager, from now on keys manager is responsible 
     * for destroying key 
     */
    if(xmlSecCryptoAppDefaultKeysMngrAdoptKey(mngr, key) < 0) {
        fprintf(stderr,"Error: failed to add key from \"%s\" to keys manager\n", key_file);
        xmlSecKeyDestroy(key);
        xmlSecKeysMngrDestroy(mngr);
        return(NULL);
    }

    return(mngr);
}
