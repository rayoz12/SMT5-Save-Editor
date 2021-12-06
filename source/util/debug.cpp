#include "util/debug.hpp"
#include "util/state.hpp"

#include <ostream>

namespace editor::debug
{
    void printBytes(long offset, int length) {
        for (int i = offset; i < offset + length; i++) {
            printf("%02X ", globalState.saveData[i]);
        }
        printf("\n");
    }
} // namespace editor::debug

