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

    SaveEditorGeneralLayout::SaveEditorGeneralLayout() : Layout::Layout()
    {

        //std::cout << "Constructing SaveEditorGeneralLayout" << std::endl;

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit     \ue0ef Save    \ue0e4 Player      \ue0e5 Demons");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));
        SetBackgroundImage("romfs:/images/background2.png");


        this->generalSectionText = pu::ui::elm::TextBlock::New(10, 50, "General");
        this->generalSectionText->SetColor(COLOR("#00FF00FF"));
        this->playerSectionText = pu::ui::elm::TextBlock::New(200, 50, "Player Stats");
        this->playerSectionText->SetColor(COLOR("#FFFFFFFF"));
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


        this->firstName = pu::ui::elm::MenuItem::New("firstName: #!NO_VALUE");
        this->lastName = pu::ui::elm::MenuItem::New("lastName: #!NO_VALUE");
        this->macca = pu::ui::elm::MenuItem::New("macca: #!NO_VALUE");
        this->glory = pu::ui::elm::MenuItem::New("glory: #!NO_VALUE");
        this->difficulty = pu::ui::elm::MenuItem::New("difficulty: #!NO_VALUE");
        this->playTime = pu::ui::elm::MenuItem::New("playTime: #!NO_VALUE");
        this->dateSaved = pu::ui::elm::MenuItem::New("dateSaved: #!NO_VALUE");

        this->generalMenu->AddItem(this->firstName);
        this->generalMenu->AddItem(this->lastName);
        this->generalMenu->AddItem(this->macca);
        this->generalMenu->AddItem(this->glory);
        this->generalMenu->AddItem(this->difficulty);
        this->generalMenu->AddItem(this->playTime);
        this->generalMenu->AddItem(this->dateSaved);
    }

    void SaveEditorGeneralLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        using namespace editor;
        if ((Down & HidNpadButton_A)) {
            auto idx = this->generalMenu->GetSelectedIndex();
            switch (idx) {
            case 0: {
                pu::String currentValue = saveInterface.getString(Offsets::FirstName, 16);
                auto newValueStr = keyboard.inputString(currentValue.AsUTF8());
                auto newValue = pu::String(newValueStr);
                if (newValue == currentValue) {
                    return;
                }
                this->firstName->SetName("First Name: " + newValue);
            }
                

                break;
            
            default:
                break;
            }

            refreshMenuItems();
        }
    }

    void SaveEditorGeneralLayout::refreshMenuItems() {
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

    void SaveEditorGeneralLayout::initialiseFromSave() {
        
        // printf("Initialising Item Page\n");

        itemManager.parseSave();

        refreshMenuItems();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}
