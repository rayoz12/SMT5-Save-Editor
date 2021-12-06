
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

#include "ui/saveSelector.hpp"
#include "ui/SaveEditorGeneral.hpp"
#include "ui/SaveEditorItems.hpp"

// Define your application (can't instantiate base class, so need to make a derived one)
namespace editor::ui
{
    enum Pages {
        General,
        Player,
        Items,
        Demons
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

            void loadSave();

        private:
            
            // Layout instance
            SaveSelectorLayout::Ref saveSelectorLayout;
            SaveEditorGeneralLayout::Ref saveEditorGeneralLayout;
            // SaveEditorPlayerLayout::Ref saveEditorPlayerLayout;
            SaveEditorItemLayout::Ref saveEditorItemLayout;
            
    };    
} // namespace editor::ui
