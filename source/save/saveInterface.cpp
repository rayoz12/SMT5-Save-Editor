#include "save/saveInterface.hpp"
#include "util/state.hpp"

#include <inttypes.h>

namespace editor::save
{
    pu::String SaveInterface::getString(long offset, int size) {
        auto start = globalState.saveData.begin() + offset;
        auto end = start + size;
        std::u16string str(start, end);
        return pu::String(str);
    }

    uint8_t SaveInterface::getByte(long offset) {
        return globalState.saveData[offset];
    }

    // All bytes in the save file are big endian.

    uint16_t SaveInterface::get2Bytes(long offset) {
        uint16_t result = globalState.saveData[offset + 1];
        result |= globalState.saveData[offset + 0]<<8;
        return result;
    }

    uint32_t SaveInterface::get4Bytes(long offset) {
        //uint32_t result = (int)globalState.saveData[3] | (int)globalState.saveData[2]<<8 | (int)globalState.saveData[1]<<16 | (int)globalState.saveData[0]<<24;
        uint32_t result = globalState.saveData[offset + 3];
        result |= globalState.saveData[offset + 2] << 8;
        result |= globalState.saveData[offset + 1] << 16;
        result |= globalState.saveData[offset + 0] << 24;
        return result;
    }

    uint64_t SaveInterface::get8Bytes(long offset) {
        uint64_t result = globalState.saveData[offset + 7];
        result |= globalState.saveData[offset + 6] << 8;
        result |= globalState.saveData[offset + 5] << 16;
        result |= globalState.saveData[offset + 4] << 24;
        result |= globalState.saveData[offset + 3] << 32;
        result |= globalState.saveData[offset + 2] << 40;
        result |= globalState.saveData[offset + 1] << 48;
        result |= globalState.saveData[offset + 0] << 56;
        return result;
    }

    void SaveInterface::putString(long offset, int size, pu::String value) {
        auto str = value.AsUTF16();
        int letterCounter = 0;
        for (int i = 0; i < size; i+=2)
        {
            if (letterCounter < str.size()) {
                put2Bytes(offset + i, str[letterCounter]);
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
        globalState.saveData[offset + 1] = value & 0x0000ff00 >> 8;
    }

    void SaveInterface::put4Bytes(long offset, uint32_t value) {
        globalState.saveData[offset + 0] = value & 0x000000ff;
        globalState.saveData[offset + 1] = value & 0x0000ff00 >> 8;
        globalState.saveData[offset + 2] = value & 0x00ff0000 >> 16;
        globalState.saveData[offset + 3] = value & 0xff000000 >> 24; 
    }

    void SaveInterface::put8Bytes(long offset, uint64_t value) {
        globalState.saveData[offset + 0] = value & 0x00000000000000ff;
        globalState.saveData[offset + 1] = value & 0x000000000000ff00 >> 8;
        globalState.saveData[offset + 2] = value & 0x0000000000ff0000 >> 16;
        globalState.saveData[offset + 3] = value & 0x00000000ff000000 >> 24; 
        globalState.saveData[offset + 4] = value & 0x000000ff00000000 >> 32; 
        globalState.saveData[offset + 5] = value & 0x0000ff0000000000 >> 40; 
        globalState.saveData[offset + 6] = value & 0x00ff000000000000 >> 48; 
        globalState.saveData[offset + 7] = value & 0xff00000000000000 >> 56; 
    }


} // namespace editor::save
