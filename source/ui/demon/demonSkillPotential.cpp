 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonSkillPotential.hpp"
#include "ui/mainApplication.hpp"
#include "util/state.hpp"
#include "util/keyboard.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace editor::ui {
    extern MainApplication* mainApp;

    using namespace editor::save;
    using namespace editor::util::keyboard;

    DemonSkillPotentialLayout::DemonSkillPotentialLayout() : DemonBaseLayout(2) {

        //std::cout << "Constructing DemonSkillPotentialLayout" << std::endl;

        

    }

    void DemonSkillPotentialLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = generalMenu->GetSelectedIndex();
            auto potential = potentials[idx];
            auto& currentValue = potential.value;
            printf("Current Value: %d\n", currentValue);
            auto newValue = keyboard.input2BytesSigned(currentValue);
            if (newValue == currentValue) {
                return;
            }

            currentValue = newValue;

            globalState.demon->save();
            refreshScreen();
        }
        else if (Down & HidNpadButton_Right) {
            auto idx = generalMenu->GetSelectedIndex();
            if ((idx + 6) < generalMenu->GetItemSize())
                generalMenu->SetSelectedIndex(idx + 6);
        }
        else if (Down & HidNpadButton_Left) {
            auto idx = generalMenu->GetSelectedIndex();
            if ((idx - 6) < generalMenu->GetItemSize())
                generalMenu->SetSelectedIndex(idx - 6);
        }
    }

    void DemonSkillPotentialLayout::refreshScreen() {
        DemonBaseLayout::refreshScreen();
        printf("DemonStats: refreshScreen\n");
        
        generalMenu->ClearItems();

        for (int i = 0; i < potentials.size(); i++) {
            auto potential = potentials[i];
            pu::String nameString = potential.name + pu::String(": ");
            if (isSaveLoaded) {
                int16_t baseValue = potential.value;
                nameString += std::to_string(baseValue);
            }

            pu::ui::elm::MenuItem::Ref potentialMenuItem = pu::ui::elm::MenuItem::New(nameString);
            potentialMenuItem->SetColor(COLOR("#FFFFFFFF"));
            this->generalMenu->AddItem(potentialMenuItem);
        }

        mainApp->CallForRender();
        // printf("DemonStats: refreshScreen Finished\n");
    }

    void DemonSkillPotentialLayout::initialiseFromSave() { 
        printf("Init DemonMain\n");
        DemonBaseLayout::initialiseFromSave();

        auto& demon = globalState.demon.value();

        potentials.clear();
        potentials.push_back({"Physical", demon.potential_physical});
        potentials.push_back({"Fire", demon.potential_fire});
        potentials.push_back({"Ice", demon.potential_ice});
        potentials.push_back({"Electric", demon.potential_electric});
        potentials.push_back({"Force", demon.potential_force});
        potentials.push_back({"Light", demon.potential_light});
        potentials.push_back({"Dark", demon.potential_dark});
        potentials.push_back({"Almighty", demon.potential_almighty});
        potentials.push_back({"Ailment", demon.potential_ailment});
        potentials.push_back({"Healing", demon.potential_healing});
        potentials.push_back({"Support", demon.potential_support});

        refreshScreen();
    }
}