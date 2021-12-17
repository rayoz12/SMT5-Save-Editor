#pragma once

#include <string>
#include <vector>

#include <pu/Plutonium>

#include "util/keyboard.hpp"
#include "save/demon.hpp"
#include "save/skillsDB.hpp"

#include "ui/demon/demonBase.hpp"



namespace editor::ui {
    
    class DemonSkillsLayout : public DemonBaseLayout
    {
        public:

            DemonSkillsLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonSkillsLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

            void initialiseFromSave();

            void refreshScreen();

            // Used by refreshScreen to display a skills list or a demon skills list
            bool isInSkillSelectionMode = false;
            
            // The skill that we're going to overwrite with the selected skill.
            int editedSkillIndex = -1;


        private:

            save::skills::SkillsDB skillsDB;
            std::vector<save::skills::SkillsDBEntry> demonSkills;
    };
}
