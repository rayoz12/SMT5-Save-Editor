#include "ui/mainApplication.hpp"

#include <filesystem>
namespace fs = std::filesystem;

#include <switch.h>
#include "util/state.hpp"
#include "util/config.hpp"
#include "crypto/crypto.hpp"
#include "util/debug.hpp"
#include "save/saveLoader.hpp"

// Implement all the layout/application functions here

namespace editor::ui {
    MainApplication *mainApp;

    void MainApplication::createPages() {
        // Initialise
        this->saveSelectorLayout = SaveSelectorLayout::New();
        this->saveEditorGeneralLayout = SaveEditorGeneralLayout::New();
        this->saveEditorPlayerLayout = SaveEditorPlayerLayout::New();
        this->saveEditorItemLayout = SaveEditorItemLayout::New();
        
        this->demonSelectorLayout = DemonSelectorLayout::New();
        this->demonMainLayout = DemonMainLayout::New();
        this->demonStatsLayout = DemonStatsLayout::New();
        this->demonSkillsPotentialLayout = DemonSkillPotentialLayout::New();
        this->demonSkillsLayout = DemonSkillsLayout::New();

        // Register OnInput
        this->saveSelectorLayout->SetOnInput(std::bind(&SaveSelectorLayout::onInput, this->saveSelectorLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->saveEditorGeneralLayout->SetOnInput(std::bind(&SaveEditorGeneralLayout::onInput, this->saveEditorGeneralLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->saveEditorPlayerLayout->SetOnInput(std::bind(&SaveEditorPlayerLayout::onInput, this->saveEditorPlayerLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->saveEditorItemLayout->SetOnInput(std::bind(&SaveEditorItemLayout::onInput, this->saveEditorItemLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        
        this->demonSelectorLayout->SetOnInput(std::bind(&DemonSelectorLayout::onInput, this->demonSelectorLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->demonMainLayout->SetOnInput(std::bind(&DemonMainLayout::onInput, this->demonMainLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->demonStatsLayout->SetOnInput(std::bind(&DemonStatsLayout::onInput, this->demonStatsLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->demonSkillsPotentialLayout->SetOnInput(std::bind(&DemonSkillPotentialLayout::onInput, this->demonSkillsPotentialLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->demonSkillsLayout->SetOnInput(std::bind(&DemonSkillsLayout::onInput, this->demonSkillsLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    }

    void MainApplication::loadPage(Pages page) {
        switch (page)
        {
        case Pages::General:
            this->saveEditorGeneralLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorGeneralLayout);
            currentPage = page;
            break;
        case Pages::Player:
            this->saveEditorPlayerLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorPlayerLayout);
            currentPage = page;
            break;
        case Pages::Items:
            this->saveEditorItemLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorItemLayout);
            currentPage = page;
            break;
        case Pages::Demons:
            this->demonSelectorLayout->initialiseFromSave();
            this->LoadLayout(this->demonSelectorLayout);
            currentPage = page;
            break;     
        default:
            printf("Page not Implemented");
            break;
        }

        // currentPage = page;
    }

    void MainApplication::nextPage() {

        if (!isInDemonEditMode) {
            if (currentPage == Pages::Demons) {
                return;
            }
            this->loadPage(static_cast<Pages>(static_cast<int>(currentPage) + 1));
        }
        else {
            if (currentDemonPage == DemonPages::Skills) {
                return;
            }
            this->loadDemonPage(static_cast<DemonPages>(static_cast<int>(currentDemonPage) + 1));
        }
    }

    void MainApplication::previousPage() {
        if (!isInDemonEditMode) {
            if (currentPage == Pages::General) {
                return;
            }
            this->loadPage(static_cast<Pages>(static_cast<int>(currentPage) - 1));
        }
        else {
            if (currentDemonPage == DemonPages::General) {
                return;
            }
            this->loadDemonPage(static_cast<DemonPages>(static_cast<int>(currentDemonPage) - 1));
        }
    }

    void MainApplication::loadDemonPage(DemonPages page) {
        switch (page)
        {
        case DemonPages::General:
            this->demonMainLayout->initialiseFromSave();
            this->LoadLayout(this->demonMainLayout);
            currentDemonPage = page;
            break;
        case DemonPages::Stats:
            this->demonStatsLayout->initialiseFromSave();
            this->LoadLayout(this->demonStatsLayout);
            currentDemonPage = page;
            break;
        case DemonPages::Skill_Potential:
            this->demonSkillsPotentialLayout->initialiseFromSave();
            this->LoadLayout(this->demonSkillsPotentialLayout);
            currentDemonPage = page;
            break;
        case DemonPages::Skills:
            this->demonSkillsLayout->initialiseFromSave();
            this->LoadLayout(this->demonSkillsLayout);
            currentDemonPage = page;
            break;     
        default:
            printf("Page not Implemented\n");
            break;
        }

        // currentPage = page;
    }

    void MainApplication::loadDemonEditor() {
        isInDemonEditMode = true;
        loadDemonPage(DemonPages::General);
    }

    void MainApplication::exitDemonEditor() {
        isInDemonEditMode = false;
        loadPage(Pages::Demons);
    }

    void MainApplication::loadSave() {
        // decrypt
        int result = editor::crypto::decrypt(globalState.savePath, globalState.saveData);
        if (result != 0) {
            this->CreateShowDialog("Failed to Read File", "Couldn't read File!", {"OK"}, false);
            return;
        }

        // editor::debug::printBytes(0x1D, 15);

        this->loadPage(Pages::General);
    }

    void MainApplication::writeSave() {
        // encrypt
        

        int result = editor::crypto::encrypt(globalState.savePath, globalState.saveData);
        if (result != 0) {
            this->CreateShowDialog("Failed to Write File", "Couldn't Write File!", {"OK"}, false);
            return;
        }

        if (this->saveSelectorLayout->isLoadedFromGame) {
            // we have to commit our changes
            Result rc = fsdevCommitDevice("save");
            if (R_FAILED(rc)) {
                printf("Failed to Commit Save: %d", rc);
                this->CreateShowDialog("Failed to Commit Save Changes", "Failed to commit save changes", {"OK"}, false);
                return;
            }
        }

        this->CreateShowDialog("Finished Writing", "Your save is ready!", {"OK"}, false);

        // editor::debug::printBytes(0x1D, 15);

        // this->loadPage(Pages::General);
    }


    void MainApplication::OnLoad()
    {
        mainApp = this;

        createPages();

        // Check if backup folder exists or create it
        if (!fs::exists(editor::config::saveBackupFolder)) {
            // mainApp->CreateShowDialog("Save Directory not Found", "Couldn't find save directory. Quitting...", {"Ok"}, true);
            printf("Backup Directory not Found\n");
            fs::create_directory(editor::config::saveBackupFolder);
        }

        // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
        // Simply explained: loading layout = the application will render that layout in the very next frame
        this->LoadLayout(this->saveSelectorLayout);

        // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
        // Using a lambda function here to simplify things
        // You can use member functions via std::bind() C++ wrapper
        this->SetOnInput([&](u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos)
        {
            if(Down & HidNpadButton_B) // If + is pressed, exit application
            {
                if (isInDemonEditMode && currentDemonPage == DemonPages::Skills) {
                    // do nothing. We ignore because the skills page needs to handle the b button
                }
                else if (isInDemonEditMode) {
                    exitDemonEditor();
                }
                else {
                    this->CloseWithFadeOut();
                }
            }
            else if(Down & HidNpadButton_Plus) // If + is pressed, exit application
            {
                int opt = this->CreateShowDialog("Save Changes?", "Write updated Save?", { "Yes", "Cancel" }, true);
                if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
                {
                    return;
                }
                this->writeSave();
            }
            else if (Down & HidNpadButton_Minus) {
                int opt = this->CreateShowDialog("Back up Save?", "Save will be backed up to: " + editor::config::saveBackupFolder, { "Yes", "Cancel" }, true);
                if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
                {
                    return;
                }
                int err = editor::crypto::backupSave(globalState.savePath);
                if (err < 0) {
                    printf("Failed to copy file %x\n", err);
                }
                this->CreateShowDialog("Save Backed up", "Save Backed up", { "OK" }, false);
            }
            else if(Down & HidNpadButton_L) {
                this->previousPage();
            }
            else if(Down & HidNpadButton_R) {
                this->nextPage();
            }
        });
    }
} // namespace editor::ui

