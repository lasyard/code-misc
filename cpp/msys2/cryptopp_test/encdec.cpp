#include <iostream>
#include <string>

#include <aes.h>
#include <files.h>
#include <gcm.h>

#define KEY_LEN 16
#define IV_LEN  16

using namespace CryptoPP;

static const unsigned char *const KEY = (const unsigned char *)"0123456789ABCDEF";
static const unsigned char *const IV = (const unsigned char *)"FEDCBA9876543210";

static void encrypt(const std::string &input,
                    std::string &output,
                    const unsigned char key[KEY_LEN],
                    const unsigned char iv[IV_LEN]);
static void decrypt(const char *buf,
                    size_t length,
                    std::string &output,
                    const unsigned char key[KEY_LEN],
                    const unsigned char iv[IV_LEN]);

int main()
{
    std::string crypted, decrypted;
    encrypt("Hello, World", crypted, KEY, IV);
    decrypt(crypted.c_str(), crypted.length(), decrypted, KEY, IV);
    std::cout << decrypted << std::endl;
}

void encrypt(const std::string &input,
             std::string &output,
             const unsigned char key[KEY_LEN],
             const unsigned char iv[IV_LEN])
{
    GCM_Final<AES, GCM_2K_Tables, true> gcm;
    gcm.SetKeyWithIV(key, IV_LEN, iv);
    StringSource(input, true, new AuthenticatedEncryptionFilter(gcm, new StringSink(output)));
}

void decrypt(const char *buf,
             size_t length,
             std::string &output,
             const unsigned char key[KEY_LEN],
             const unsigned char iv[IV_LEN])
{
    GCM_Final<AES, GCM_2K_Tables, false> gcm;
    gcm.SetKeyWithIV(key, IV_LEN, iv);
    ArraySource(
        (const unsigned char *)buf, length, true, new AuthenticatedDecryptionFilter(gcm, new StringSink(output)));
}
