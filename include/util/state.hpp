#pragma once

// Glorified Global Variable

#include "save/demon.hpp"

#include <string>
#include <vector>
#include <optional>

namespace editor::state
{
    class GlobalState {
    public:
        // Selected Save Path
        std::string savePath;

        // Decrypted(!) Save Data 
        std::vector<uint8_t> saveData;

        // Reference for Demon that's being edited right now.
        std::optional<editor::save::Demon> demon;
        
    };
} // namespace editor::state

extern editor::state::GlobalState globalState;
