#pragma once

#include <string>
#include <stdint.h>

#include <pu/Plutonium>

namespace editor::util::keyboard
{
    class Keyboard {
    public:
        Keyboard();
        pu::String inputString(pu::String currentValue);

        uint8_t inputByte(uint8_t currentValue);

        uint64_t inputNumber(uint64_t currentValue, uint64_t maxValue);

        uint16_t input2Bytes(uint16_t currentValue);
        uint32_t input4Bytes(uint32_t currentValue);
        uint64_t input8Bytes(uint64_t currentValue);

        Result makeKeyboard(SwkbdConfig& kbd);
    };
} // namespace editor::util::keyboard
