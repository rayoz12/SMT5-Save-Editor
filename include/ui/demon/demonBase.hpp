#pragma once

#include "save/items.hpp"
#include "util/keyboard.hpp"
#include "save/demonDB.hpp"

#include <pu/Plutonium>



namespace editor::ui {
    
    /**
     * Base Layout for the demon editor.
     */
    class DemonBaseLayout : public pu::ui::Layout
    {
        public:

            DemonBaseLayout(int pageIndex);

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonBaseLayout)


            void initialiseFromSave();
            bool isSaveLoaded = false;

            void refreshScreen();

        protected:

            // An easy way to keep objects is to have them as private members
            // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
            pu::ui::elm::TextBlock::Ref butText;
            pu::ui::elm::Rectangle::Ref topRect;
            pu::ui::elm::Rectangle::Ref botRect;
            pu::ui::elm::Menu::Ref generalMenu;                        

            // Utils
            editor::util::keyboard::Keyboard keyboard;
            editor::save::SaveInterface saveInterface;

            // UI Vars
            editor::save::demon::DemonDB demonDB;


        private:

            pu::ui::elm::TextBlock::Ref generalSectionText;
            pu::ui::elm::TextBlock::Ref statsSectionText;
            pu::ui::elm::TextBlock::Ref potentialSectionText;
            pu::ui::elm::TextBlock::Ref skillsSectionText;

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
