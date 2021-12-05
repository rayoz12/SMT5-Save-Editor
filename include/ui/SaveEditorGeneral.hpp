#pragma once

#include <pu/Plutonium>

#include "save/saveInterface.hpp"
#include "util/keyboard.hpp"


namespace editor::ui {
    
    class SaveEditorGeneralLayout : public pu::ui::Layout
    {
        public:

            SaveEditorGeneralLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(SaveEditorGeneralLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

            void initialiseFromSave();
            bool isSaveLoaded = false;
            
            void refreshMenuItems();

        private:

            // An easy way to keep objects is to have them as private members
            // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
            pu::ui::elm::TextBlock::Ref butText;
            pu::ui::elm::Rectangle::Ref topRect;
            pu::ui::elm::Rectangle::Ref botRect;
            pu::ui::elm::Menu::Ref generalMenu;

            pu::ui::elm::TextBlock::Ref generalSectionText;
            pu::ui::elm::TextBlock::Ref playerSectionText;
            pu::ui::elm::TextBlock::Ref itemsSectionText;
            pu::ui::elm::TextBlock::Ref demonsSectionText;

            pu::ui::elm::MenuItem::Ref firstName;
            pu::ui::elm::MenuItem::Ref lastName;
            pu::ui::elm::MenuItem::Ref macca;
            pu::ui::elm::MenuItem::Ref glory;
            pu::ui::elm::MenuItem::Ref difficulty;
            pu::ui::elm::MenuItem::Ref playTime;
            pu::ui::elm::MenuItem::Ref dateSaved;

            editor::save::SaveInterface saveInterface;
            editor::util::keyboard::Keyboard keyboard;

            
    };
}
