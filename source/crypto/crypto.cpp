#include "crypto/crypto.hpp"

#include "switch.h"
#include <stdio.h>

namespace editor::crypto
{
    int encrypt(std::string filePath, std::vector<uint8_t>& src) {
        return -1;
    }

    int decrypt(std::string filePath, std::vector<uint8_t>& dest) {

        // I'm using C File API's because newlib doesn't have good support for
        // C++ streams. I've learned first had how useless they are...
        int err;
        FILE *fileptr;
        long filelen;
        fileptr = fopen(filePath.c_str(), "rb");  // Open the file in binary mode
        if (fileptr == NULL) {
            return errno;
        }
        err = fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
        if (err < 0) {
            return errno;
        }
        filelen = ftell(fileptr);             // Get the current byte offset in the file
        rewind(fileptr);                      // Jump back to the beginning of the file

        std::vector<uint8_t> fileBytes;

        fileBytes.reserve(filelen);
        dest.reserve(filelen);

        fread(&fileBytes[0], filelen, 1, fileptr);

        fclose(fileptr);
        
        auto fileData = fileBytes.data();
        auto destData = dest.data();

        uint8_t key[32] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66};

        Aes256Context ctx;
        aes256ContextCreate(&ctx, key, /* is_encryptor */ false);
        // Decypt in 16 byte sized blocks
        for (size_t i = 0; i < filelen; i+=16) {
            aes256DecryptBlock(&ctx, &destData[i], &fileData[i]);
        }
        
        return 0;        
    }
} // namespace editor::crypto
