#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/SaveEditorPlayer.hpp"
#include "ui/mainApplication.hpp"
#include "util/config.hpp"
#include "util/debug.hpp"
#include "util/state.hpp"
#include "util/keyboard.hpp"
#include "crypto/crypto.hpp"
#include "save/offsets.hpp"
#include "save/saveInterface.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)


namespace editor::ui {
    extern MainApplication* mainApp;

    using namespace editor::save;
    using namespace editor::util::keyboard;

    SaveEditorPlayerLayout::SaveEditorPlayerLayout() : Layout::Layout()
    {

        //std::cout << "Constructing SaveEditorPlayerLayout" << std::endl;

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit    \ue0f0 Backup Save     \ue0ef Save    \ue0e4 General      \ue0e5 Items");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));
        SetBackgroundImage("romfs:/images/background1.jpg");


        this->generalSectionText = pu::ui::elm::TextBlock::New(10, 50, "General");
        this->generalSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->playerSectionText = pu::ui::elm::TextBlock::New(200, 50, "Player Stats");
        this->playerSectionText->SetColor(COLOR("#00FF00FF"));
        this->itemsSectionText = pu::ui::elm::TextBlock::New(400, 50, "Items");
        this->itemsSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->demonsSectionText = pu::ui::elm::TextBlock::New(600, 50, "Demons");
        this->demonsSectionText->SetColor(COLOR("#FFFFFFFF"));

        // Create the Save menu
        this->generalMenu = pu::ui::elm::Menu::New(0, 95, 1280, COLOR("#0d005900"), 94, 6);        


        // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
        this->Add(this->topRect);
        this->Add(this->botRect);
        this->Add(this->butText);

        this->Add(this->generalSectionText);
        this->Add(this->playerSectionText);
        this->Add(this->itemsSectionText);
        this->Add(this->demonsSectionText);
        this->Add(this->generalMenu);

        using namespace pu::ui::elm;
        stats.push_back({"HP", Offsets::HP_BASE, Offsets::HP_BALM, Offsets::HP_COMBINED});
        stats.push_back({"MP", Offsets::MP_BASE, Offsets::MP_BALM, Offsets::MP_COMBINED});
        stats.push_back({"Strength", Offsets::STRENGTH_BASE, Offsets::STRENGTH_BALM, Offsets::STRENGTH_COMBINED});
        stats.push_back({"Vitality", Offsets::VITALITY_BASE, Offsets::VITALITY_BALM, Offsets::VITALITY_COMBINED});
        stats.push_back({"Magic", Offsets::MAGIC_BASE, Offsets::MAGIC_BALM, Offsets::MAGIC_COMBINED});
        stats.push_back({"Agility", Offsets::AGILITY_BASE, Offsets::AGILITY_BALM, Offsets::AGILITY_COMBINED});
        stats.push_back({"Luck", Offsets::LUCK_BASE, Offsets::LUCK_BALM, Offsets::LUCK_COMBINED});
    }

    void SaveEditorPlayerLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = this->generalMenu->GetSelectedIndex();
            int statIdx = idx / 2; // Should be floor'd already due to int casting
            auto stat = stats[statIdx];
            uint16_t currentValue;

            bool isBase = idx % 2 == 0;

            if (isBase) {
                // Even so it's the base values
                currentValue = saveInterface.get2Bytes(stat.baseOffset);
            }
            else {
                currentValue = saveInterface.get2Bytes(stat.balmOffset);
            }

            auto newValue = keyboard.input2Bytes(currentValue);
            if (newValue == currentValue) {
                return;
            }

            // Recalculate combined
            if (isBase) {
                auto balm = saveInterface.get2Bytes(stat.balmOffset);
                uint16_t combined = newValue + balm;
                saveInterface.put2Bytes(stat.baseOffset, newValue);
                saveInterface.put2Bytes(stat.combinedOffset, combined);
            }
            else {
                auto base = saveInterface.get2Bytes(stat.baseOffset);
                uint16_t combined = newValue + base;
                saveInterface.put2Bytes(stat.balmOffset, newValue);
                saveInterface.put2Bytes(stat.combinedOffset, combined);
            }

            refreshMenuItems();
        }
        else if (Down & HidNpadButton_Right) {
            auto idx = this->generalMenu->GetSelectedIndex();
            if ((idx + 6) < this->generalMenu->GetItemSize())
                this->generalMenu->SetSelectedIndex(idx + 6);
        }
        else if (Down & HidNpadButton_Left) {
            auto idx = this->generalMenu->GetSelectedIndex();
            if ((idx - 6) < this->generalMenu->GetItemSize())
                this->generalMenu->SetSelectedIndex(idx - 6);
        }
    }

    void SaveEditorPlayerLayout::refreshMenuItems() {
        this->generalMenu->ClearItems();

        for (int i = 0; i < stats.size(); i++) {
            auto stat = stats[i];
            pu::String baseString = stat.name + pu::String(" Base: ");
            pu::String balmString = stat.name + pu::String(" Balm: ");
            if (isSaveLoaded) {
                uint16_t baseValue = saveInterface.get2Bytes(stat.baseOffset);
                uint16_t balmValue = saveInterface.get2Bytes(stat.balmOffset);
                uint16_t combinedValue = saveInterface.get2Bytes(stat.combinedOffset);
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
    }

    void SaveEditorPlayerLayout::initialiseFromSave() {
        
        // printf("Initialising Item Page\n");

        this->isSaveLoaded = true;
        refreshMenuItems();

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}
