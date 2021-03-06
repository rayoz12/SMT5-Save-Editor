#pragma once

#include "save/items.hpp"
#include "util/keyboard.hpp"
#include "save/demonDB.hpp"

#include "ui/demon/demonBase.hpp"

#include <pu/Plutonium>
namespace editor::ui {

    /**
     * Describes stats on the player
     */
    struct DemonStat {
        pu::String name;
        uint16_t& base;
        uint16_t& balm;
        uint16_t& combined;
    };
    
    class DemonStatsLayout : public DemonBaseLayout
    {
        public:

            DemonStatsLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonStatsLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

            void initialiseFromSave();

            void refreshScreen();



        private:

            std::vector<DemonStat> stats;
    };
}
