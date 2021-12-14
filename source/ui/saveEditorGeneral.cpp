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

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit    \ue0f0 Backup Save     \ue0ef Save     \ue0e5 Player");
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


        this->firstName = pu::ui::elm::MenuItem::New("First Name: #!NO_VALUE");
        this->lastName = pu::ui::elm::MenuItem::New("Last Name: #!NO_VALUE");
        this->macca = pu::ui::elm::MenuItem::New("Macca: #!NO_VALUE");
        this->glory = pu::ui::elm::MenuItem::New("Glory: #!NO_VALUE");
        this->difficulty = pu::ui::elm::MenuItem::New("Difficulty: #!NO_VALUE");
        this->playTime = pu::ui::elm::MenuItem::New("Play Time: #!NO_VALUE");
        this->dateSaved = pu::ui::elm::MenuItem::New("Date Saved: #!NO_VALUE");

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
                saveInterface.putString(Offsets::FirstName, 16, newValue);
                saveInterface.putString(Offsets::FirstName2, 16, newValue);
                saveInterface.putString(Offsets::FirstName3, 16, newValue);
                newValue = saveInterface.getString(Offsets::FirstName, 16);
                this->firstName->SetName("First Name: " + newValue);
                break;
            }
            case 1: {
                pu::String currentValue = saveInterface.getString(Offsets::LastName, 16);
                auto newValueStr = keyboard.inputString(currentValue.AsUTF8());
                auto newValue = pu::String(newValueStr);
                if (newValue == currentValue) {
                    return;
                }
                saveInterface.putString(Offsets::LastName, 16, newValue);
                newValue = saveInterface.getString(Offsets::LastName, 16);
                this->lastName->SetName("Last Name: " + newValue);
                break;
            }
            case 2: {
                auto currentValue = saveInterface.get4Bytes(Offsets::Macca);
                auto newValue = keyboard.input4Bytes(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                saveInterface.put4Bytes(Offsets::Macca, newValue);
                newValue = saveInterface.get4Bytes(Offsets::Macca);
                this->macca->SetName("Macca: " + std::to_string(newValue));
                break;
            }
            case 3: {
                auto currentValue = saveInterface.get4Bytes(Offsets::Glory);
                auto newValue = keyboard.input4Bytes(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                saveInterface.put4Bytes(Offsets::Glory, newValue);
                newValue = saveInterface.get4Bytes(Offsets::Glory);
                this->glory->SetName("Glory: " + std::to_string(newValue));
                break;
            }
            case 4: {
                auto currentValue = saveInterface.getByte(Offsets::GameDifficulty);
                auto newValue = keyboard.inputByte(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                if (newValue < 1 || newValue > 3) {
                    mainApp->CreateShowDialog("Error", "Difficulty only allows values 1 to 3", {"OK"}, false);
                    return;
                }
                saveInterface.putByte(Offsets::GameDifficulty, newValue);
                newValue = saveInterface.getByte(Offsets::GameDifficulty);
                this->glory->SetName("Difficulty: " + std::to_string(newValue));
                break;
            }
            default:
                printf("Not Implemented");
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

        this->firstName->SetName(pu::String("First Name: ") + firstNameValue);
        this->lastName->SetName(pu::String("Last Name: ") + lastNameValue);
        this->macca->SetName(pu::String("Macca: ") + std::to_string(maccaValue));
        this->glory->SetName(pu::String("Glory: ") + std::to_string(gloryValue));
        this->difficulty->SetName(pu::String("Difficulty: ") + std::to_string(difficultyValue));
        this->playTime->SetName(pu::String("Play Time: ") + std::to_string(playTimeValue));
        this->dateSaved->SetName(pu::String("Date Saved: ") + std::to_string(dateSavedValue));


        refreshMenuItems();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}
