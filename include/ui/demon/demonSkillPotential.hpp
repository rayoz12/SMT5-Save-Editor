#pragma once

#include <string>
#include <vector>

#include "util/keyboard.hpp"
#include "save/demon.hpp"

#include "ui/demon/demonBase.hpp"

#include <pu/Plutonium>
namespace editor::ui {

    struct SkillPotential {
        std::string name;
        int16_t& value;
    };
    
    class DemonSkillPotentialLayout : public DemonBaseLayout
    {
        public:

            DemonSkillPotentialLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonSkillPotentialLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

            void initialiseFromSave();

            void refreshScreen();



        private:

            std::vector<SkillPotential> potentials;
    };
}
