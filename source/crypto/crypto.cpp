#include "crypto/crypto.hpp"

#include <stdio.h>
#include <filesystem>
#include <ctime>

#include "switch.h"

#include "util/config.hpp"

namespace editor::crypto
{
    int copy(std::string srcPath, std::string destPath) {
        int err;
        FILE *srcFilePtr, *destFilePtr;
        long filelen;
        srcFilePtr = fopen(srcPath.c_str(), "rb");  // Open the file in binary mode
        destFilePtr = fopen(destPath.c_str(), "wb");  // Open the file in binary mode
        
        if (srcFilePtr == NULL || destFilePtr == NULL) {
            printf("copy: Failed to open files!\n");
            return errno;
        }
        err = fseek(srcFilePtr, 0, SEEK_END);          // Jump to the end of the file
        if (err < 0) {
            printf("copy: Failed to seek file!\n");
            fclose(srcFilePtr);
            fclose(destFilePtr);
            return errno;
        }
        filelen = ftell(srcFilePtr);             // Get the current byte offset in the file
        rewind(srcFilePtr);                      // Jump back to the beginning of the file

        std::vector<uint8_t> buffer;
        buffer.reserve(filelen);
        buffer.resize(filelen);
        printf("File Len: %d\n", filelen);

        fread(&buffer[0], filelen, 1, srcFilePtr);

        fclose(srcFilePtr);

        // Write to the backup file
        fwrite(&buffer[0], filelen, 1, destFilePtr);

        fclose(destFilePtr);
        
        return 0;
    };

    int backupSave(std::string filePath) {
        std::filesystem::path savePath = filePath;
        std::filesystem::path backupSaveDirPath = editor::config::saveBackupFolder;
        std::filesystem::path backupSavePath = backupSaveDirPath / savePath.filename();
        backupSavePath += ".backup";

        // get time and date
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d%m%Y_%H_%M_%S",timeinfo);
        std::string dateTime(buffer);

        backupSavePath += dateTime;

        printf("Backup Path: %s\n", backupSavePath.c_str());

        return copy(filePath, backupSavePath.string());
    }

    

    int encrypt(std::string filePath, std::vector<uint8_t>& src) {
        int filelen = src.size();
        
        std::vector<uint8_t> fileBytes;
        fileBytes.reserve(filelen);
        fileBytes.resize(filelen);

        auto fileData = fileBytes.data();
        auto srcData = src.data();

        uint8_t key[32] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66};

        Aes256Context ctx;
        aes256ContextCreate(&ctx, key, /* is_encryptor */ true);
        // Encrypt in 16 byte sized blocks
        for (size_t i = 0; i < filelen; i+=16) {
            // printf("i: %d\n", i);
            aes256EncryptBlock(&ctx, &fileData[i], &srcData[i]);
            // printf("Source: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", srcData[i], srcData[i+1], srcData[i+2], srcData[i+3], srcData[i+4], srcData[i+5], srcData[i+6], srcData[i+7], srcData[i+8], srcData[i+9], srcData[i+10], srcData[i+11], srcData[i+12], srcData[i+13], srcData[i+14], srcData[i+15]);
            // printf("File: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", fileData[i], fileData[i+1], fileData[i+2], fileData[i+3], fileData[i+4], fileData[i+5], fileData[i+6], fileData[i+7], fileData[i+8], fileData[i+9], fileData[i+10], fileData[i+11], fileData[i+12], fileData[i+13], fileData[i+14], fileData[i+15]);
        }


        int err = backupSave(filePath);
        if (err != 0) {
            printf("Failed to backup file!");
            return -1;
        }

        FILE *fileptr;
        fileptr = fopen(filePath.c_str(), "wb");  // Open the file in binary mode
        if (fileptr == NULL) {
            return errno;
        }
        
        fwrite(fileData, filelen, 1, fileptr);
        fflush(fileptr);
        
        fclose(fileptr);

        return 0;
    }

    int decrypt(std::string filePath, std::vector<uint8_t>& dest) {

        // I'm using C File API's because newlib doesn't have good support for
        // C++ streams. I've learned first hand how useless they are...
        int err;
        FILE *fileptr;
        long filelen;
        fileptr = fopen(filePath.c_str(), "rb");  // Open the file in binary mode
        if (fileptr == NULL) {
            return errno;
        }
        err = fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
        if (err < 0) {
            fclose(fileptr);
            return errno;
        }
        filelen = ftell(fileptr);             // Get the current byte offset in the file
        rewind(fileptr);                      // Jump back to the beginning of the file

        std::vector<uint8_t> fileBytes;

        fileBytes.reserve(filelen);
        dest.reserve(filelen);
        dest.resize(filelen);

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
