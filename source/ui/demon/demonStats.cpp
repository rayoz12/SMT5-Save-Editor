 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonStats.hpp"
#include "ui/mainApplication.hpp"
#include "util/state.hpp"
#include "util/keyboard.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace editor::ui {
    extern MainApplication* mainApp;

    using namespace editor::save;
    using namespace editor::util::keyboard;

    DemonStatsLayout::DemonStatsLayout() : DemonBaseLayout(1) {

        //std::cout << "Constructing DemonStatsLayout" << std::endl;

        

    }

    void DemonStatsLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = generalMenu->GetSelectedIndex();
            int statIdx = idx / 2; // Should be floor'd already due to int casting
            auto stat = stats[statIdx];
            uint16_t currentValue;

            bool isBase = idx % 2 == 0;

            if (isBase) {
                // Even so it's the base values
                currentValue = stat.base;
            }
            else {
                currentValue = stat.balm;
            }


            auto newValue = keyboard.input2Bytes(currentValue);
            if (newValue == currentValue) {
                return;
            }

            // Recalculate combined
            if (isBase) {
                auto balm = stat.balm;
                stat.base = newValue;
                stat.combined = newValue + stat.balm;
            }
            else {
                auto base = stat.base;
                stat.balm = newValue;
                stat.combined = newValue + stat.base;
            }
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

    void DemonStatsLayout::refreshScreen() {
        DemonBaseLayout::refreshScreen();
        printf("DemonStats: refreshScreen\n");
        
        generalMenu->ClearItems();

        for (int i = 0; i < stats.size(); i++) {
            auto stat = stats[i];
            pu::String baseString = stat.name + pu::String(" Base: ");
            pu::String balmString = stat.name + pu::String(" Balm: ");
            if (isSaveLoaded) {
                uint16_t baseValue = stat.base;
                uint16_t balmValue = stat.balm;
                uint16_t combinedValue = stat.combined;
                baseString += std::to_string(baseValue);
                balmString += std::to_string(balmValue) + 
                    "                                                 Combined: " + std::to_string(combinedValue);
            }

            pu::ui::elm::MenuItem::Ref base = pu::ui::elm::MenuItem::New(baseString);
            pu::ui::elm::MenuItem::Ref balm = pu::ui::elm::MenuItem::New(balmString);
            base->SetColor(COLOR("#FFFFFFFF"));
            balm->SetColor(COLOR("#FFFFFFFF"));

            this->generalMenu->AddItem(base);
            this->generalMenu->AddItem(balm);
        }

        mainApp->CallForRender();
        // printf("DemonStats: refreshScreen Finished\n");
    }

    void DemonStatsLayout::initialiseFromSave() { 
        printf("Init DemonMain\n");
        DemonBaseLayout::initialiseFromSave();

        save::Demon& demon = globalState.demon.value();
        
        stats.clear();
        stats.push_back({"HP", demon.hp, demon.hp_item, demon.hp_combined});
        stats.push_back({"MP", demon.mp, demon.mp_item, demon.mp_combined});
        stats.push_back({"Strength", demon.base_strength, demon.strength_item, demon.strength_combined});
        stats.push_back({"Vitality", demon.base_vitality, demon.vitality_item, demon.vitality_combined});
        stats.push_back({"Magic", demon.base_magic, demon.magic_item, demon.magic_combined});
        stats.push_back({"Agility", demon.base_agility, demon.agility_item, demon.agility_combined});
        stats.push_back({"Luck", demon.base_luck, demon.luck_item, demon.luck_combined});

        

        refreshScreen();
    }
}