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
        int64_t inputSignedNumber(int64_t currentValue, int64_t minValueIn, int64_t maxValueIn);

        uint16_t input2Bytes(uint16_t currentValue);
        int16_t input2BytesSigned(int16_t currentValue);
        uint32_t input4Bytes(uint32_t currentValue);
        uint64_t input8Bytes(uint64_t currentValue);

        Result makeKeyboard(SwkbdConfig& kbd);
    };
} // namespace editor::util::keyboard
