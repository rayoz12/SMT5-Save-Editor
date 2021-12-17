 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonSkills.hpp"
#include "ui/mainApplication.hpp"
#include "util/state.hpp"
#include "util/keyboard.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace editor::ui {
    extern MainApplication* mainApp;

    using namespace editor::save;
    using namespace editor::util::keyboard;

    DemonSkillsLayout::DemonSkillsLayout() : DemonBaseLayout(3) {

        //std::cout << "Constructing DemonSkillsLayout" << std::endl;

        

    }

    void DemonSkillsLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        // //std::cout << "OnInput\n";
        if ((Down & HidNpadButton_A)) {
            auto idx = generalMenu->GetSelectedIndex();

            if (isInSkillSelectionMode) {
                // Get selected skill and change it on the demon
                auto& selectedSkill = save::skills::skillList[idx];
                auto& demon = globalState.demon.value();

                demon.skills[editedSkillIndex] = selectedSkill.id;
                demonSkills[editedSkillIndex] = selectedSkill;

                demon.save();
                editedSkillIndex = -1;
                isInSkillSelectionMode = false;
            }
            else {
                // Get the selected skill and store it's index in `editedSkillIndex`
                editedSkillIndex = idx;
                isInSkillSelectionMode = true;
            }

            
            refreshScreen();
        }
        else if (Down & HidNpadButton_B) {
            if (isInSkillSelectionMode) {
                editedSkillIndex = -1;
                isInSkillSelectionMode = false;
                this->generalMenu->SetSelectedIndex(0);
                refreshScreen();
            }
            else {
                mainApp->exitDemonEditor();
            }
            
        }
        else if (Down & HidNpadButton_Right) {
            int menuSize = 0;
            if (isInSkillSelectionMode) {
                menuSize = save::skills::skillList.size();
            }
            else {
                menuSize = 8;
            }
            auto idx = generalMenu->GetSelectedIndex();
            if ((idx + 6) < menuSize)
                generalMenu->SetSelectedIndex(idx + 6);
        }
        else if (Down & HidNpadButton_Left) {
            int menuSize = 0;
            if (isInSkillSelectionMode) {
                menuSize = save::skills::skillList.size();
            }
            else {
                menuSize = 8;
            }
            auto idx = generalMenu->GetSelectedIndex();
            if ((idx - 6) < menuSize)
                generalMenu->SetSelectedIndex(idx - 6);
        }
    }

    void DemonSkillsLayout::refreshScreen() {
        DemonBaseLayout::refreshScreen();
        printf("DemonSkillsLayout: refreshScreen\n");
        
        generalMenu->ClearItems();

        if (isInSkillSelectionMode) {
            for (size_t i = 0; i < save::skills::skillList.size(); i++) {
                auto& skillName = save::skills::skillList[i].name;
                pu::ui::elm::MenuItem::Ref skillMenuItem = pu::ui::elm::MenuItem::New(skillName);
                skillMenuItem->SetColor(COLOR("#FFFFFFFF"));
                this->generalMenu->AddItem(skillMenuItem);
            }
        }
        else {
            for (int i = 0; i < demonSkills.size(); i++) {
                auto skill = demonSkills[i];
                pu::String nameString = "Skill " + std::to_string(i + 1) + ": ";
                if (isSaveLoaded) {
                    std::string name = skill.name;
                    nameString += skill.name;
                }

                pu::ui::elm::MenuItem::Ref skillMenuItem = pu::ui::elm::MenuItem::New(nameString);
                skillMenuItem->SetColor(COLOR("#FFFFFFFF"));
                this->generalMenu->AddItem(skillMenuItem);
            }
        }

        generalMenu->SetSelectedIndex(0);

        

        mainApp->CallForRender();
        // printf("DemonStats: refreshScreen Finished\n");
    }

    void DemonSkillsLayout::initialiseFromSave() { 
        printf("Init DemonMain\n");
        DemonBaseLayout::initialiseFromSave();

        isInSkillSelectionMode = false;

        auto& demon = globalState.demon.value();
        demonSkills.clear();
        for (size_t i = 0; i < demon.skills.size(); i++) {
            auto& skillID = demon.skills[i];
            demonSkills.push_back(skillsDB.getEntry(skillID));
        }
        

        refreshScreen();
    }
}