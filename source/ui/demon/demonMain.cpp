 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonMain.hpp"
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

    DemonMainLayout::DemonMainLayout() : DemonBaseLayout(0) {

        //std::cout << "Constructing DemonMainLayout" << std::endl;

        

    }

    void DemonMainLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = generalMenu->GetSelectedIndex();
            switch (idx)
            {
            case 0: {
                uint16_t currentValue = globalState.demon->id;
                auto newValue = keyboard.input2Bytes(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                globalState.demon->id = newValue;
                globalState.demon->save();
                break;
            }
            case 1:{
                uint32_t currentValue = globalState.demon->experience;
                auto newValue = keyboard.input4Bytes(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                globalState.demon->experience = newValue;
                globalState.demon->save();
                break;
            }
            case 2:{
                uint16_t currentValue = globalState.demon->level;
                auto newValue = keyboard.input2Bytes(currentValue);
                if (newValue == currentValue) {
                    return;
                }
                globalState.demon->level = newValue;
                globalState.demon->save();
                break;
            }
            default:
                break;
            }
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

    void DemonMainLayout::refreshScreen() {
        DemonBaseLayout::refreshScreen();
        printf("DemonMain: refreshScreen\n");
        
        generalMenu->ClearItems();

        // printf("DemonMain: refreshScreen: Getting data\n");
        auto id = globalState.demon->id;
        auto exp = globalState.demon->experience;
        auto level = globalState.demon->level;

        // printf("DemonMain: refreshScreen: Creating Items\n");
        auto idItem = pu::ui::elm::MenuItem::New("ID: " + std::to_string(id));
        auto expItem = pu::ui::elm::MenuItem::New("Experience: " + std::to_string(exp));
        auto levelItem = pu::ui::elm::MenuItem::New("Level: " + std::to_string(level));
        idItem->SetColor(COLOR("#FFFFFF"));
        expItem->SetColor(COLOR("#FFFFFF"));
        levelItem->SetColor(COLOR("#FFFFFF"));

        // printf("DemonMain: refreshScreen: Adding items\n");
        generalMenu->AddItem(idItem);
        generalMenu->AddItem(expItem);
        generalMenu->AddItem(levelItem);

        mainApp->CallForRender();
        // printf("DemonMain: refreshScreen Finished\n");
    }

    void DemonMainLayout::initialiseFromSave() { 
        printf("Init DemonMain\n");
        DemonBaseLayout::initialiseFromSave();
        refreshScreen();
    }
}