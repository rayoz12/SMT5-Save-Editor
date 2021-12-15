#pragma once

#include "save/items.hpp"
#include "util/keyboard.hpp"
#include "save/demonDB.hpp"

#include <pu/Plutonium>



namespace editor::ui {
    
    class DemonSelectorLayout : public pu::ui::Layout
    {
        public:

            DemonSelectorLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonSelectorLayout)

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

            // Utils
            editor::util::keyboard::Keyboard keyboard;
            editor::save::SaveInterface saveInterface;

            // UI Vars
            // Keep track of which offsets we've added to the menu
            std::vector<long> menuOffsets;
            editor::save::demon::DemonDB demonDB;
    };
}
