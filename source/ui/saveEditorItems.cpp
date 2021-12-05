#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/SaveEditorItems.hpp"
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

    SaveEditorItemLayout::SaveEditorItemLayout() : Layout::Layout()
    {

        //std::cout << "Constructing SaveEditorItemLayout" << std::endl;

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit     \ue0ef Save    \ue0e4 Player      \ue0e5 Demons");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));
        SetBackgroundImage("romfs:/images/background2.png");


        this->generalSectionText = pu::ui::elm::TextBlock::New(10, 50, "General");
        this->generalSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->playerSectionText = pu::ui::elm::TextBlock::New(200, 50, "Player Stats");
        this->playerSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->itemsSectionText = pu::ui::elm::TextBlock::New(400, 50, "Items");
        this->itemsSectionText->SetColor(COLOR("#00FF00FF"));
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
    }

    void SaveEditorItemLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = this->generalMenu->GetSelectedIndex();
            auto id = this->menuIDs[idx];
            auto& currentValue = this->itemManager.usedItems[id];
            auto newValue = keyboard.inputByte(currentValue.count);
            // printf("%s, %d, %d\n", currentValue.item.name.c_str(), currentValue.count, newValue);
            if (currentValue.count == newValue) {
                return;
            }

            currentValue.count = newValue;

            itemManager.updateSave();
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

    void SaveEditorItemLayout::refreshMenuItems() {
        this->generalMenu->ClearItems();
        this->menuIDs.clear();

        auto usedItems = itemManager.usedItems;
        for (auto &&item : itemManager.usedItems) {
            
            std::ostringstream textElem;
            textElem << item.second.item.name << ": " << std::to_string(item.second.count);
            // printf("%s: %d\n", item.second.item.name.c_str(), item.second.count);
            pu::ui::elm::MenuItem::Ref itemElem = pu::ui::elm::MenuItem::New(textElem.str());
            itemElem->SetColor(COLOR("#FFFFFFFF"));

            this->generalMenu->AddItem(itemElem);
            this->menuIDs.push_back(item.first);
        }

        mainApp->CallForRender();
    }

    void SaveEditorItemLayout::initialiseFromSave() {
        
        // printf("Initialising Item Page\n");

        itemManager.parseSave();

        refreshMenuItems();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}
