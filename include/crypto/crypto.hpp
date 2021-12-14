#pragma once

#include <stdint.h>
#include <vector>
#include <string>

namespace editor::crypto
{
    int backupSave(std::string filePath);

    int encrypt(std::string filePath, std::vector<uint8_t>& src);

    int decrypt(std::string filePath, std::vector<uint8_t>& dest);
} // namespace editor::crypto
