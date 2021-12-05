#include "util/debug.hpp"
#include "util/state.hpp"

namespace editor::debug
{
    void printBytes(long offset, int length) {
        for (int i = offset; i < length; i++) {
            printf("%02X", globalState.saveData[i]);
        }
    }
} // namespace editor::debug

