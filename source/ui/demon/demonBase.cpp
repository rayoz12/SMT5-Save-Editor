 #include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <switch.h>

#include "ui/demon/demonBase.hpp"
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

    DemonBaseLayout::DemonBaseLayout(int pageIndex) : Layout::Layout()
    {

        //std::cout << "Constructing DemonBaseLayout" << std::endl;

        this->butText = pu::ui::elm::TextBlock::New(10, 678, "\ue0e0 Edit    \ue0e1 Exit    \ue0f0 Backup Save     \ue0ef Save    \ue0e5 Stats");
        this->butText->SetColor(COLOR("#FFFFFFFF"));
        this->topRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 94, COLOR("#0d005980"));
        this->botRect = pu::ui::elm::Rectangle::New(0, 659, 1280, 61, COLOR("#0d005980"));
        SetBackgroundImage("romfs:/images/background1.jpg");


        this->generalSectionText = pu::ui::elm::TextBlock::New(10, 50, "General");
        this->generalSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->statsSectionText = pu::ui::elm::TextBlock::New(200, 50, "Stats");
        this->statsSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->potentialSectionText = pu::ui::elm::TextBlock::New(400, 50, "Skill Potential");
        this->potentialSectionText->SetColor(COLOR("#FFFFFFFF"));
        this->skillsSectionText = pu::ui::elm::TextBlock::New(600, 50, "Skills");
        this->skillsSectionText->SetColor(COLOR("#FFFFFFFF"));

        switch (pageIndex)
        {
        case 0:
            this->generalSectionText->SetColor(COLOR("#00FF00FF"));
            break;
        case 1:
            this->statsSectionText->SetColor(COLOR("#00FF00FF"));
            break;
        case 2:
            this->potentialSectionText->SetColor(COLOR("#00FF00FF"));
            break;
        case 3:
            this->skillsSectionText->SetColor(COLOR("#00FF00FF"));
            break;
        default:
            break;
        }

        // Create the menu
        this->generalMenu = pu::ui::elm::Menu::New(390, 95, 890, COLOR("#0d005900"), 94, 6);        

        // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
        this->Add(this->topRect);
        this->Add(this->botRect);
        this->Add(this->butText);

        this->Add(this->generalSectionText);
        this->Add(this->statsSectionText);
        this->Add(this->potentialSectionText);
        this->Add(this->skillsSectionText);
        this->Add(this->generalMenu);


        // Demon Info
        using namespace pu::ui::elm;
        // Draw Demon Info
        // static inline constexpr std::array<u32, 4> DefaultFontSizes = { 18, 20, 25, 30 };
        auto lvlLabelText = TextBlock::New(46, 121, "Lv");
        lvlLabelText->SetFont("DefaultFont@30");
        lvlLabelText->SetColor(COLOR("#D6DEAF"));
        this->levelText = TextBlock::New(46, 151, "Lv_VAL");
        levelText->SetColor(COLOR("#FFFFFF"));
        this->raceText = TextBlock::New(108, 121, "race_VAL");
        raceText->SetColor(COLOR("#D6DEAF"));
        this->nameText = TextBlock::New(108, 151, "name_VAL");
        nameText->SetColor(COLOR("#FFFFFF"));
        this->Add(lvlLabelText);
        this->Add(levelText);
        this->Add(raceText);
        this->Add(nameText);

        // EXP
        auto expBox = Rectangle::New(24, 222, 342, 26, COLOR("#FFFFFF55"));
        expBox->SetBorderRadius(5);
        auto expLabel = TextBlock::New(30, 225, "EXP");
        expLabel->SetColor(COLOR("#b0e3d4"));
        this->expText = TextBlock::New(150, 225, "EXP_VAL");
        this->expText->SetColor(COLOR("#FFFFFF"));
        this->Add(expBox);
        this->Add(expLabel);
        this->Add(expText);
        
        // Condition
        auto conditionBox = Rectangle::New(24, 256, 191, 23, COLOR("#FFFFFF55"));
        conditionBox->SetBorderRadius(10);
        auto conditionLabel = TextBlock::New(50, 257, "Condition");
        conditionLabel->SetColor(COLOR("#FFFFFF"));
        this->Add(conditionBox);
        this->Add(conditionLabel);

        auto hpBox = Rectangle::New(24, 311, 342, 26, COLOR("#FFFFFF55"));
        hpBox->SetBorderRadius(5);
        auto hpLabel = TextBlock::New(30, 285, "HP");
        hpLabel->SetColor(COLOR("#A0F93F"));
        this->hpText = TextBlock::New(150, 285, "hp_VAL");
        this->hpText->SetColor(COLOR("#FFFFFF"));
        this->Add(hpBox);
        this->Add(hpLabel);
        this->Add(hpText);

        auto mpBox = Rectangle::New(24, 283, 342, 26, COLOR("#FFFFFF55"));
        mpBox->SetBorderRadius(5);
        auto mpLabel = TextBlock::New(30, 313, "MP");
        mpLabel->SetColor(COLOR("#F5D34B"));
        this->mpText = TextBlock::New(150, 313, "mp_VAL");
        this->mpText->SetColor(COLOR("#FFFFFF"));
        this->Add(mpBox);
        this->Add(mpLabel);
        this->Add(mpText);

        // // Resistances
        // auto resistancesBox = Rectangle::New(24, 344, 191, 23, COLOR("#FFFFFF55"));
        // resistancesBox->SetBorderRadius(10);
        // auto resistancesLabel = TextBlock::New(50, 344, "Resistances");
        // resistancesLabel->SetColor(COLOR("#FFFFFF"));
        // this->Add(resistancesBox);
        // this->Add(resistancesLabel);

        // int cellStart = 24;
        // int cellWidth = 49;
        // int cellHeight = 30;
        // for (int i = 0; i < 7; i++) {
        //     auto cell = Rectangle::New(cellStart + (i * cellWidth), 371, cellWidth, cellHeight, COLOR("#6E6E6E"));
        //     auto cellValue = Rectangle::New(cellStart + (i * cellWidth), 401, cellWidth, cellHeight, COLOR("#6E6E6E"));
        //     this->Add(cell);
        //     this->Add(cellValue);
        // }
        // auto physLabel = TextBlock::New(36, 375, "Phys");
        // physLabel->SetColor(COLOR("#FFFFFF"));
        // auto fireLabel = TextBlock::New(85, 375, "Fire");
        // fireLabel->SetColor(COLOR("#FFFFFF"));
        // auto iceLabel = TextBlock::New(134, 375, "Ice");
        // iceLabel->SetColor(COLOR("#FFFFFF"));
        // auto elecLabel = TextBlock::New(183, 375, "Elec");
        // elecLabel->SetColor(COLOR("#FFFFFF"));
        // auto forceLabel = TextBlock::New(232, 375, "Force");
        // forceLabel->SetColor(COLOR("#FFFFFF"));
        // auto lightLabel = TextBlock::New(281, 375, "Light");
        // lightLabel->SetColor(COLOR("#FFFFFF"));
        // auto darkLabel = TextBlock::New(330, 375, "Dark");
        // darkLabel->SetColor(COLOR("#FFFFFF"));
        // this->Add(physLabel);
        // this->Add(fireLabel);
        // this->Add(iceLabel);
        // this->Add(elecLabel);
        // this->Add(forceLabel);
        // this->Add(lightLabel);
        // this->Add(darkLabel);

        // this->physText = TextBlock::New(36, 406, "phys_VAL");
        // this->physText->SetColor(COLOR("#FFFFFF"));
        // this->fireText = TextBlock::New(85, 406, "fire_VAL");
        // this->fireText->SetColor(COLOR("#FFFFFF"));
        // this->iceText = TextBlock::New(134, 406, "ice_VAL");
        // this->iceText->SetColor(COLOR("#FFFFFF"));
        // this->elecText = TextBlock::New(183, 406, "elec_VAL");
        // this->elecText->SetColor(COLOR("#FFFFFF"));
        // this->forceText = TextBlock::New(232, 406, "force_VAL");
        // this->forceText->SetColor(COLOR("#FFFFFF"));
        // this->lightText = TextBlock::New(281, 406, "light_VAL");
        // this->lightText->SetColor(COLOR("#FFFFFF"));
        // this->darkText = TextBlock::New(330, 406, "dark_VAL");
        // this->darkText->SetColor(COLOR("#FFFFFF"));
        // this->Add(this->physText);
        // this->Add(this->fireText);
        // this->Add(this->iceText);
        // this->Add(this->elecText);
        // this->Add(this->forceText);
        // this->Add(this->lightText);
        // this->Add(this->darkText);
        
        auto alignmentResistantcesBox = Rectangle::New(24, 437, 342, 26, COLOR("#FFFFFF55"));
        alignmentResistantcesBox->SetBorderRadius(5);
        this->Add(alignmentResistantcesBox);

        // Stats
        auto statsBox = Rectangle::New(24, 479, 191, 23, COLOR("#FFFFFF55"));
        statsBox->SetBorderRadius(10);
        auto statsLabel = TextBlock::New(50, 479, "Stats");
        statsLabel->SetColor(COLOR("#FFFFFF"));
        this->Add(statsBox);
        this->Add(statsLabel);

        int statHeight = 28;
        int statStart = 503;
        for (int i = 0; i < 5; i++) {
            auto stat = Rectangle::New(24, statStart + (i * statHeight), 342, statHeight, COLOR("#FFFFFF55"));
            this->Add(stat);
        }
        auto strengthLabel = TextBlock::New(30, 503, "Strength");
        strengthLabel->SetColor(COLOR("#FFFFFF"));
        auto vitalityLabel = TextBlock::New(30, 531, "Vitality");
        vitalityLabel->SetColor(COLOR("#FFFFFF"));
        auto magicLabel = TextBlock::New(30, 559, "Magic");
        magicLabel->SetColor(COLOR("#FFFFFF"));
        auto agilityLabel = TextBlock::New(30, 587, "Agility");
        agilityLabel->SetColor(COLOR("#FFFFFF"));
        auto luckLabel = TextBlock::New(30, 615, "Luck");
        luckLabel->SetColor(COLOR("#FFFFFF"));
        this->Add(strengthLabel);
        this->Add(vitalityLabel);
        this->Add(magicLabel);
        this->Add(agilityLabel);
        this->Add(luckLabel);

        this->strengthText = TextBlock::New(150, 503, "strength_VAL");
        this->strengthText->SetColor(COLOR("#FFFFFF"));
        this->vitalityText = TextBlock::New(150, 531, "vitality_VAL");
        this->vitalityText->SetColor(COLOR("#FFFFFF"));
        this->magicText = TextBlock::New(150, 559, "magic_VAL");
        this->magicText->SetColor(COLOR("#FFFFFF"));
        this->agilityText = TextBlock::New(150, 587, "agility_VAL");
        this->agilityText->SetColor(COLOR("#FFFFFF"));
        this->luckText = TextBlock::New(150, 615, "luck_VAL");
        this->luckText->SetColor(COLOR("#FFFFFF"));
        this->Add(this->strengthText);
        this->Add(this->vitalityText);
        this->Add(this->magicText);
        this->Add(this->agilityText);
        this->Add(this->luckText);

        auto dividerBox = Rectangle::New(380, 94, 10, 566, COLOR("#FFFFFF55"));
        this->Add(dividerBox);

    }

    void DemonBaseLayout::refreshScreen() {

        // Update Demon Info
        levelText->SetText(std::to_string(globalState.demon->level));
        raceText->SetText(globalState.demon->race);
        nameText->SetText(globalState.demon->name);

        expText->SetText(std::to_string(globalState.demon->experience));
        hpText->SetText(std::to_string(globalState.demon->hp_combined));
        mpText->SetText(std::to_string(globalState.demon->mp_combined));

        // physText->SetText(std::to_string(globalState.demon->phys));
        // fireText->SetText(std::to_string(globalState.demon->fire));
        // iceText->SetText(std::to_string(globalState.demon->ice));
        // elecText->SetText(std::to_string(globalState.demon->elec));
        // forceText->SetText(std::to_string(globalState.demon->force));
        // lightText->SetText(std::to_string(globalState.demon->light));
        // darkText->SetText(std::to_string(globalState.demon->dark));

        strengthText->SetText(std::to_string(globalState.demon->strength_combined));
        vitalityText->SetText(std::to_string(globalState.demon->vitality_combined));
        magicText->SetText(std::to_string(globalState.demon->magic_combined));
        agilityText->SetText(std::to_string(globalState.demon->agility_combined));
        luckText->SetText(std::to_string(globalState.demon->luck_combined));
        
        

        mainApp->CallForRender();
    }

    void DemonBaseLayout::initialiseFromSave() {
        
        // printf("Initialising Item Page\n");

        refreshScreen();

        this->isSaveLoaded = true;

        //std::cout << "Finished Loading Player Page" << std::endl;
        this->generalMenu->SetVisible(true);
    }
}