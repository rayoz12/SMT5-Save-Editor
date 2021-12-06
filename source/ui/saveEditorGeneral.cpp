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
        SetBackgroundImage("romfs:/images/background1.jpg");


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

        this->firstName->SetColor(COLOR("#FFFFFFFF"));
        this->lastName->SetColor(COLOR("#FFFFFFFF"));
        this->macca->SetColor(COLOR("#FFFFFFFF"));
        this->glory->SetColor(COLOR("#FFFFFFFF"));
        this->difficulty->SetColor(COLOR("#FFFFFFFF"));
        this->playTime->SetColor(COLOR("#FFFFFFFF"));
        this->dateSaved->SetColor(COLOR("#FFFFFFFF"));

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
        
        this->generalMenu->AddItem(this->firstName);
        this->generalMenu->AddItem(this->lastName);
        this->generalMenu->AddItem(this->macca);
        this->generalMenu->AddItem(this->glory);
        this->generalMenu->AddItem(this->difficulty);
        this->generalMenu->AddItem(this->playTime);
        this->generalMenu->AddItem(this->dateSaved);

        mainApp->CallForRender();
    }

    void SaveEditorGeneralLayout::initialiseFromSave() {
        
        printf("Initialising General Page\n");
        auto firstNameValue = saveInterface.getString(Offsets::FirstName, 16);
        auto lastNameValue = saveInterface.getString(Offsets::LastName, 16);
        auto maccaValue = saveInterface.get4Bytes(Offsets::Macca);
        auto gloryValue = saveInterface.get4Bytes(Offsets::Glory);
        auto difficultyValue = saveInterface.getByte(Offsets::GameDifficulty);
        auto playTimeValue = saveInterface.get4Bytes(Offsets::PlayTime);
        auto dateSavedValue = saveInterface.get8Bytes(Offsets::DateSaved);

        printf("Writing first name %s, %s\n", firstNameValue.AsUTF8().c_str(), lastNameValue.AsUTF8().c_str());
        this->firstName->SetName(pu::String("firstName: ") + firstNameValue);
        this->lastName->SetName(pu::String("lastName: ") + lastNameValue);
        this->macca->SetName(pu::String("macca: ") + std::to_string(maccaValue));
        this->glory->SetName(pu::String("glory: ") + std::to_string(gloryValue));
        this->difficulty->SetName(pu::String("difficulty: ") + std::to_string(difficultyValue));
        this->playTime->SetName(pu::String("playTime: ") + std::to_string(playTimeValue));
        this->dateSaved->SetName(pu::String("dateSaved: ") + std::to_string(dateSavedValue));


        refreshMenuItems();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}
