#pragma once

// Glorified Global Variable

#include <string>
#include <vector>

namespace editor::state
{
    class GlobalState {
    public:
        // Selected Save Path
        std::string savePath;

        // Decrypted(!) Save Data 
        std::vector<uint8_t> saveData;
    };
} // namespace editor::state

extern editor::state::GlobalState globalState;
