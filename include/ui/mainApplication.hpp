
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

#include "ui/saveSelector.hpp"
#include "ui/SaveEditorGeneral.hpp"
#include "ui/SaveEditorPlayer.hpp"
#include "ui/SaveEditorItems.hpp"
#include "ui/demon/demonSelector.hpp"

#include "ui/demon/demonMain.hpp"
#include "ui/demon/demonStats.hpp"

// Define your application (can't instantiate base class, so need to make a derived one)
namespace editor::ui
{
    enum class Pages {
        General,
        Player,
        Items,
        Demons
    };
    
    enum class DemonPages {
        General,
        Stats,
        Skill_Potential,
        Skills
    };

    class MainApplication : public pu::ui::Application
    {
        public:
            using Application::Application;
            PU_SMART_CTOR(MainApplication)

            // We need to define this, and use it to initialize everything
            void OnLoad() override;

            void createPages();

            Pages currentPage = Pages::General;
            void loadPage(Pages page);
            void nextPage();
            void previousPage();

            bool isInDemonEditMode = false;
            DemonPages currentDemonPage = DemonPages::General;
            void loadDemonPage(DemonPages page);
            void loadDemonEditor();



            void loadSave();
            void writeSave();

        private:
            
            // Layout instance
            SaveSelectorLayout::Ref saveSelectorLayout;
            SaveEditorGeneralLayout::Ref saveEditorGeneralLayout;
            SaveEditorPlayerLayout::Ref saveEditorPlayerLayout;
            SaveEditorItemLayout::Ref saveEditorItemLayout;
            DemonSelectorLayout::Ref demonSelectorLayout;
            
            DemonMainLayout::Ref demonMainLayout;
            DemonStatsLayout::Ref demonStatsLayout;
    };    
} // namespace editor::ui
