 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonSelector.hpp"
#include "ui/mainApplication.hpp"
#include "util/config.hpp"
#include "util/debug.hpp"
#include "util/state.hpp"
#include "util/keyboard.hpp"
#include "crypto/crypto.hpp"
#include "save/offsets.hpp"
#include "save/saveInterface.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)

std::vector<long> demonOffsets = {0xA94, 0xC1C, 0xDA4, 0xF2C, 0x10B4, 0x123C, 0x13C4, 0x154C, 0x16D4, 0x185C, 0x19E4, 0x1B6C, 0x1CF4, 0x1E7C, 0x2004, 0x218C, 0x2314, 0x249C, 0x2624, 0x27AC, 0x2934, 0x2ABC, 0x2C44, 0x2DCC };


namespace editor::ui {
    extern MainApplication* mainApp;

    using namespace editor::save;
    using namespace editor::util::keyboard;

    DemonSelectorLayout::DemonSelectorLayout() : Layout::Layout()
    {

        //std::cout << "Constructing DemonSelectorLayout" << std::endl;

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit    \ue0f0 Backup Save     \ue0ef Save    \ue0e4 Player      \ue0e5 Demons");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));
        SetBackgroundImage("romfs:/images/background1.jpg");


        this->generalSectionText = pu::ui::elm::TextBlock::New(10, 50, "General");
        this->generalSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->playerSectionText = pu::ui::elm::TextBlock::New(200, 50, "Player Stats");
        this->playerSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->itemsSectionText = pu::ui::elm::TextBlock::New(400, 50, "Items");
        this->itemsSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->demonsSectionText = pu::ui::elm::TextBlock::New(600, 50, "Demons");
        this->demonsSectionText->SetColor(COLOR("#00FF00FF"));

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
    }

    void DemonSelectorLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = this->generalMenu->GetSelectedIndex();
            auto offset = menuOffsets[idx];
            globalState.demon = save::Demon(offset);
            mainApp->loadDemonEditor();
            // refreshMenuItems();
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

    void DemonSelectorLayout::refreshMenuItems() {
        this->generalMenu->ClearItems();       
        
        for (auto &&offset : demonOffsets) {
            auto hp = saveInterface.get2Bytes(offset);
            // If hp != 0 that means a demon exists here
            if (hp == 0) {
                continue;
            }

            // Get the ID
            uint16_t id = saveInterface.get2Bytes(offset + 82);
            std::string name = demonDB.getName(id);
            if (name.find("Unknown") != std::string::npos) {
                // Add the HP and MP for identification
                auto mp = saveInterface.get2Bytes(offset + 2);
                name += ", HP: " + std::to_string(hp) + ", MP: " + std::to_string(mp);
            }

            auto demonItem = pu::ui::elm::MenuItem::New(name);
            demonItem->SetColor(COLOR("#FFFFFFFF"));
            this->generalMenu->AddItem(demonItem);
            this->menuOffsets.push_back(offset);

        }
        

        mainApp->CallForRender();
    }

    void DemonSelectorLayout::initialiseFromSave() {
        
        // printf("Initialising Item Page\n");

        refreshMenuItems();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}