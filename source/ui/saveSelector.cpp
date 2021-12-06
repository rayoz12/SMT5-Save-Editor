#include <string>
#include <iostream>
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

        auto title = pu::ui::elm::TextBlock::New(180, 35, "SMT 5 Save Editor - Select a Save File");
        title->SetColor(COLOR("#dbcc9cFF"));
        

        SetBackgroundImage("romfs:/images/background1.jpg");

        // Create the Save Slots menu
        this->saveMenu = pu::ui::elm::Menu::New(0, 95, 1280, COLOR("#0d005900"), 94, 6);

        if (!fs::exists(editor::config::saveFolder)) {
            // mainApp->CreateShowDialog("Save Directory not Found", "Couldn't find save directory. Quitting...", {"Ok"}, true);
            printf("Save Directory not Found\n");
            fs::create_directory(editor::config::saveFolder);
            // mainApp->Close();
            // return;
            // exit(-1);
        }

        bool isEntryAdded = false;

        for (const auto & entry : fs::directory_iterator(editor::config::saveFolder)) {
            std::string filename = entry.path().filename().string();
            if (!filename.compare("SysSave")) {
                continue;
            }
            //std::cout << entry.path().filename() << std::endl;
            auto saveItem = pu::ui::elm::MenuItem::New(filename);
            saveItem->SetColor(COLOR("#FFFFFFFF"));
            this->saveItems.push_back(filename);
            this->saveMenu->AddItem(saveItem);
            isEntryAdded = true;
        }

        if (!isEntryAdded) {
            auto error = pu::ui::elm::TextBlock::New(150, 500, "Please move save files (using something like nx-shell) to: " + editor::config::saveFolder);
            error->SetColor(COLOR("#FF1111FF"));
            this->Add(error);
        }

        // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
        this->Add(this->topRect);
        this->Add(this->botRect);
        this->Add(this->butText);
        this->Add(this->saveMenu);
        this->Add(title);
    }

    void SaveSelectorLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = this->saveMenu->GetSelectedIndex();
            //std::cout << idx << std::endl;
            if (idx < saveItems.size()) {
                globalState.savePath = std::string(editor::config::saveFolder + "/" + saveItems[idx]);
                //std::cout << saveItems[idx] << std::endl;
                //std::cout << globalState.savePath << std::endl;
                mainApp->loadSave();
            }
        }
    }
}
