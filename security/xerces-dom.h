#include <evp.h>
#include <pem.h>
#include <x509.h>

EVP_PKEY *LoadKey(const char *keyfile, const char *keyPwd, int privateKey) {
    EVP_PKEY *pKey = NULL;    
    X509 *pCert = NULL;
    FILE *f;

    f = fopen(keyfile, "r");
    if(f == NULL) return NULL;

    if(privateKey) {
	pKey = PEM_read_PrivateKey(f, NULL, NULL, (void*)keyPwd);
    } else {	
        pKey = PEM_read_PUBKEY(f, NULL, NULL, (void*)keyPwd);
	if (!pKey) {
	    rewind(f);
	    pCert = PEM_read_X509(f,NULL,NULL,NULL);
	    if (pCert) {
		pKey = X509_get_pubkey(pCert);
		X509_free(pCert);
	    }
	}
    }
    fclose(f);
    return(pKey);
}
