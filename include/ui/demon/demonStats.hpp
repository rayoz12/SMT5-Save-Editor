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

            // Demon Info
            pu::ui::elm::TextBlock::Ref levelText;
            pu::ui::elm::TextBlock::Ref raceText;
            pu::ui::elm::TextBlock::Ref nameText;

            pu::ui::elm::TextBlock::Ref expText;
            pu::ui::elm::TextBlock::Ref hpText;
            pu::ui::elm::TextBlock::Ref mpText;
            
            pu::ui::elm::TextBlock::Ref physText;
            pu::ui::elm::TextBlock::Ref fireText;
            pu::ui::elm::TextBlock::Ref iceText;
            pu::ui::elm::TextBlock::Ref elecText;
            pu::ui::elm::TextBlock::Ref forceText;
            pu::ui::elm::TextBlock::Ref lightText;
            pu::ui::elm::TextBlock::Ref darkText;

            pu::ui::elm::TextBlock::Ref strengthText;
            pu::ui::elm::TextBlock::Ref vitalityText;
            pu::ui::elm::TextBlock::Ref magicText;
            pu::ui::elm::TextBlock::Ref agilityText;
            pu::ui::elm::TextBlock::Ref luckText;
    };
}
