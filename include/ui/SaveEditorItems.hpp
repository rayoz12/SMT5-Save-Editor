#pragma once

#include "save/items.hpp"
#include "util/keyboard.hpp"

#include <pu/Plutonium>



namespace editor::ui {
    
    class SaveEditorItemLayout : public pu::ui::Layout
    {
        public:

            SaveEditorItemLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(SaveEditorItemLayout)

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

            std::vector<int> menuIDs;
            editor::save::ItemManager itemManager;
            editor::util::keyboard::Keyboard keyboard;
    };
}
