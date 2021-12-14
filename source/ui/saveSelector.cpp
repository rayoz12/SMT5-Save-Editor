#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/mainApplication.hpp"
#include "ui/saveSelector.hpp"
#include "util/config.hpp"
#include "util/state.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace editor::ui {
    extern MainApplication* mainApp;
    SaveSelectorLayout::SaveSelectorLayout() : Layout::Layout()
    {
        //std::cout << "Constructing SaveSelectorLayout" << std::endl;
        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Select    \ue0e1 Exit");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));

        this->title = pu::ui::elm::TextBlock::New(180, 35, "SMT 5 Save Editor - Select a Save File");
        title->SetColor(COLOR("#dbcc9cFF"));
        

        SetBackgroundImage("romfs:/images/background1.jpg");

        // Create the Save Slots menu
        this->saveMenu = pu::ui::elm::Menu::New(0, 95, 1280, COLOR("#0d005900"), 94, 6);

        // Load the saves from the game
        // Check which Games are installed
        std::vector<std::uint64_t> titles;
        Result rc = saveLoader.getSMTVTitleIDSaves(titles);
        if (R_FAILED(rc)) {
            printf("Failed to get titles!\n");
            return;
        }
        if (titles.size() == 0) {
            printf("SMT5 is not Installed!\n");
            return;
        }
        else if (titles.size() > 1) {
            isInRegionSelectMode = true;
            title->SetText("SMT 5 Save Editor - Select a Region");
            printf("In Region Select Mode\n");
        }
        else {
            isLoadedFromGame = true;
            selectedTitleID = titles[0];
            printf("Found game\n");
        }

        if (isLoadedFromGame) {
            loadSavesFromTitleID();
        }
        else if (isInRegionSelectMode) {
            auto NA = pu::ui::elm::MenuItem::New("North America: 0x010063B012DC6000");
            auto EU = pu::ui::elm::MenuItem::New("Europe: 0x0100B870126CE000");
            NA->SetColor(COLOR("#FFFFFFFF"));
            EU->SetColor(COLOR("#FFFFFFFF"));
            this->saveMenu->AddItem(NA);
            this->saveMenu->AddItem(EU);
        }

        // loadFromFS();

        // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
        this->Add(this->topRect);
        this->Add(this->botRect);
        this->Add(this->butText);
        this->Add(this->saveMenu);
        this->Add(title);
    }

    void SaveSelectorLayout::loadSavesFromTitleID() {
        // Mount and Read Files
        AccountUid account;
        Result rc = saveLoader.getAccount(account);
        if (R_FAILED(rc)) {
            printf("Failed to get account...\n");
            setError("Failed to Load account");
            loadFromFS();
            return;
        }
        rc = saveLoader.mountSave("save", selectedTitleID, account);
        if (R_FAILED(rc)) {
            printf("Failed to get account...\n");
            setError("Failed to mount save");
            loadFromFS();
            return;
        }

        this->saveMenu->ClearItems();


        bool isEntryAdded = false;

        for (const auto & entry : fs::directory_iterator("save:/")) {
            std::string filename = entry.path().filename().string();
            if (!filename.compare("SysSave")) {
                continue;
            }
            printf("%s\n", entry.path().filename().c_str());
            auto saveItem = pu::ui::elm::MenuItem::New(filename);
            saveItem->SetColor(COLOR("#FFFFFFFF"));
            this->saveItems.push_back("save:/" + filename);
            this->saveMenu->AddItem(saveItem);
            isEntryAdded = true;
        }

        if (!isEntryAdded) {
            setError("No saves found on mounted save. Are you sure you chose the right region?");
        }

        isLoadedFromGame = true;

    }

    void SaveSelectorLayout::loadFromFS() {

        bool isEntryAdded = false;

        for (const auto & entry : fs::directory_iterator(editor::config::saveFolder)) {
            std::string filename = entry.path().filename().string();
            if (!filename.compare("SysSave")) {
                continue;
            }
            printf("%s\n", entry.path().filename().c_str());
            auto saveItem = pu::ui::elm::MenuItem::New(filename);
            saveItem->SetColor(COLOR("#FFFFFFFF"));
            this->saveItems.push_back(editor::config::saveFolder + "/" + filename);
            this->saveMenu->AddItem(saveItem);
            isEntryAdded = true;
        }

        if (!isEntryAdded) {
            setError("Please move save files (using something like nx-shell) to: " + editor::config::saveFolder);
        }
    }

    void SaveSelectorLayout::setError(std::string errorString) {
        auto error = pu::ui::elm::TextBlock::New(150, 500, errorString);
        error->SetColor(COLOR("#FF1111FF"));
        this->Add(error);
    }

    void SaveSelectorLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = this->saveMenu->GetSelectedIndex();
            
            if (isInRegionSelectMode) {
                if (idx == 0) {
                    selectedTitleID = editor::saveLoader::TITLEID_NA;
                }
                else if (idx == 1) {
                    selectedTitleID = editor::saveLoader::TITLEID_EU;
                }
                else {
                    printf("Unknown Index!\n");
                }
                loadSavesFromTitleID();
                isInRegionSelectMode = false;
                title->SetText("SMT 5 Save Editor - Select a Save File");
                return;
            }

            if (idx < saveItems.size()) {
                globalState.savePath = std::string(saveItems[idx]);
                printf("%s\n", saveItems[idx].c_str());
                printf("%s\n", globalState.savePath.c_str());
                mainApp->loadSave();
            }
        }
    }
}
