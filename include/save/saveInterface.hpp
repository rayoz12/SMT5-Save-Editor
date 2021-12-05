#pragma once

#include <stdint.h>
#include <pu/pu_String.hpp>

namespace editor::save {
    class SaveInterface {
    
    public:
        pu::String getString(long offset, int size);
        uint8_t getByte(long offset);
        uint16_t get2Bytes(long offset);
        uint32_t get4Bytes(long offset);
        uint64_t get8Bytes(long offset);

        void putString(long offset, int size, pu::String value);
        void putByte(long offset, uint8_t value);
        void put2Bytes(long offset, uint16_t value);
        void put4Bytes(long offset, uint32_t value);
        void put8Bytes(long offset, uint64_t value);

    private:

    };
}