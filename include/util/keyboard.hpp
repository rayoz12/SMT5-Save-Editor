#pragma once

#include <string>
#include <stdint.h>

namespace editor::util::keyboard
{
    class Keyboard {
    public:
        std::string inputString(std::string currentValue);
        uint8_t inputByte(uint8_t currentValue);
        uint16_t input2Bytes(uint16_t currentValue);
        uint32_t input4Bytes(uint32_t currentValue);
        uint64_t input8Bytes(uint64_t currentValue);
    };
} // namespace editor::util::keyboard
