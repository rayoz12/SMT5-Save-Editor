#include "save/saveInterface.hpp"
#include "util/state.hpp"

#include "util/debug.hpp"

#include <inttypes.h>

namespace editor::save
{
    pu::String SaveInterface::getString(long offset, int size) {
        auto start = globalState.saveData.begin() + offset;
        auto end = start + size;
        // editor::debug::printBytes(offset, size);

        std::vector<char16_t> array;

        for (size_t i = offset; i < offset + size; i+=2) {
            char16_t value = (((unsigned short)globalState.saveData[i]) << 0) | (((unsigned short)globalState.saveData[i+1]) << 8);
            array.push_back(value);
        }
        
        std::u16string str(std::begin(array), std::end(array));
        return pu::String(str);
    }

    uint8_t SaveInterface::getByte(long offset) {
        return globalState.saveData[offset];
    }

    // All bytes in the save file are little endian.

    uint16_t SaveInterface::get2Bytes(long offset) {
        uint16_t result = globalState.saveData[offset];
        result |= globalState.saveData[offset + 1] << 8;
        return result;
    }

    int16_t SaveInterface::get2BytesSigned(long offset) {
        int16_t result = globalState.saveData[offset];
        result |= globalState.saveData[offset + 1] << 8;
        return result;
    }

    uint32_t SaveInterface::get4Bytes(long offset) {
        uint32_t result = globalState.saveData[offset];
        result |= globalState.saveData[offset + 1] << 8;
        result |= globalState.saveData[offset + 2] << 16;
        result |= globalState.saveData[offset + 3] << 24;
        return result;
    }

    uint64_t SaveInterface::get8Bytes(long offset) {
        auto first = (globalState.saveData[offset]) | (globalState.saveData[offset+1] << 8) | (globalState.saveData[offset+2] << 16) | (globalState.saveData[offset+3] << 24);
        auto second = (globalState.saveData[offset+4]) | (globalState.saveData[offset+5] << 8) | (globalState.saveData[offset+6] << 16) | (globalState.saveData[offset+7] << 24);
        return (long long)((unsigned int) first | ((unsigned long long) second << 32));
    }

    void SaveInterface::putString(long offset, int size, pu::String value) {
        auto str = value.AsUTF16();
        auto data = str.data();
        int letterCounter = 0;
        for (int i = 0; i < size; i+=2)
        {
            if (letterCounter < str.size()) {
                put2Bytes(offset + i, data[letterCounter]);
                letterCounter++;
            }
            else {
                put2Bytes(offset + i, 0);
            }
        }        
    }

    void SaveInterface::putByte(long offset, uint8_t value) {
        globalState.saveData[offset] = value;
    }

    void SaveInterface::put2Bytes(long offset, uint16_t value) {
        globalState.saveData[offset] = value & 0x000000ff;
        globalState.saveData[offset + 1] = (value & 0x0000ff00) >> 8;
    }

    void SaveInterface::put2BytesSigned(long offset, int16_t value) {
        globalState.saveData[offset] = value & 0x000000ff;
        globalState.saveData[offset + 1] = (value & 0x0000ff00) >> 8;
    }

    void SaveInterface::put4Bytes(long offset, uint32_t value) {
        globalState.saveData[offset + 0] = (value & 0x000000ff);
        globalState.saveData[offset + 1] = (value & 0x0000ff00) >> 8;
        globalState.saveData[offset + 2] = (value & 0x00ff0000) >> 16;
        globalState.saveData[offset + 3] = (value & 0xff000000) >> 24; 
    }

    void SaveInterface::put8Bytes(long offset, uint64_t value) {
        globalState.saveData[offset + 0] = (value & 0x00000000000000ff);
        globalState.saveData[offset + 1] = (value & 0x000000000000ff00) >> 8;
        globalState.saveData[offset + 2] = (value & 0x0000000000ff0000) >> 16;
        globalState.saveData[offset + 3] = (value & 0x00000000ff000000) >> 24; 
        globalState.saveData[offset + 4] = (value & 0x000000ff00000000) >> 32; 
        globalState.saveData[offset + 5] = (value & 0x0000ff0000000000) >> 40; 
        globalState.saveData[offset + 6] = (value & 0x00ff000000000000) >> 48; 
        globalState.saveData[offset + 7] = (value & 0xff00000000000000) >> 56; 
    }


} // namespace editor::save
