#pragma once

#include "save/items.hpp"
#include "util/keyboard.hpp"
#include "save/demonDB.hpp"

#include "ui/demon/demonBase.hpp"

#include <pu/Plutonium>



namespace editor::ui {
    
    class DemonMainLayout : public DemonBaseLayout
    {
        public:

            DemonMainLayout();

            // Have ::Ref alias and ::New() static constructor
            PU_SMART_CTOR(DemonMainLayout)

            void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

            void initialiseFromSave();

            void refreshScreen();



        private:
    };
}
