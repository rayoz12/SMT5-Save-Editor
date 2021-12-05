#pragma once

#include <vector>

#include <pu/Plutonium>


namespace editor::ui {
    
    class SaveSelectorLayout : public pu::ui::Layout
    {
        public:

            SaveSelectorLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(SaveSelectorLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

        private:

            // An easy way to keep objects is to have them as private members
            // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
            pu::ui::elm::TextBlock::Ref butText;
            pu::ui::elm::Rectangle::Ref topRect;
            pu::ui::elm::Rectangle::Ref botRect;
            pu::ui::elm::Menu::Ref saveMenu;

            std::vector<std::string> saveItems;
    };
}
