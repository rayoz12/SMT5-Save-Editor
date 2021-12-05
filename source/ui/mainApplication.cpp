#include "ui/mainApplication.hpp"

// Implement all the layout/application functions here

namespace editor::ui
{
    MainApplication *mainApp;

    void MainApplication::createPages() {
        this->saveSelectorLayout = SaveSelectorLayout::New();
        this->saveEditorGeneralLayout = SaveEditorGeneralLayout::New();
        // this->saveEditorPlayerLayout = SaveEditorPlayerLayout::New();
        this->saveEditorItemLayout = SaveEditorItemLayout::New();
    }

    void MainApplication::loadPage(Pages page) {
        switch (page)
        {
        case Pages::General:
            this->saveEditorGeneralLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorGeneralLayout);
            break;
        case Pages::Player:
        case Pages::Items:
            this->saveEditorItemLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorItemLayout);
            break;
        case Pages::Demons:        
        default:
            printf("Page not Implemented");
            break;
        }
    }

    void MainApplication::nextPage() {
        switch (currentPage)
        {
        case Pages::General:
            this->saveEditorGeneralLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorGeneralLayout);
            break;
        case Pages::Player:
        case Pages::Items:
        case Pages::Demons:        
        default:
            printf("Page not Implemented");
            break;
        }
    }

    void MainApplication::previousPage() {
        switch (currentPage)
        {
        case Pages::General:
            this->saveEditorGeneralLayout->initialiseFromSave();
            this->LoadLayout(this->saveEditorGeneralLayout);
            break;
        case Pages::Player:
        case Pages::Items:
        case Pages::Demons:        
        default:
            printf("Page not Implemented");
            break;
        }
    }

    void MainApplication::OnLoad()
    {
        mainApp = this;

        // Create the layout (calling the smart constructor above)
        createPages();

        // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
        // Simply explained: loading layout = the application will render that layout in the very next frame
        this->LoadLayout(this->saveSelectorLayout);

        // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
        // Using a lambda function here to simplify things
        // You can use member functions via std::bind() C++ wrapper
        this->SetOnInput([&](u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos)
        {
            if(Down & HidNpadButton_X) // If X is pressed, start with our dialog questions!
            {
                int opt = this->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
                if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
                {
                    this->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
                }
                else
                {
                    switch(opt)
                    {
                        case 0: // "Yes" was selected
                            this->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true); // Same here ^
                            break;
                        case 1: // "No" was selected
                            this->CreateShowDialog("Answer", "Oh, bad news then...", { "OK" }, true); // And here ^
                            break;
                    }
                }
            }
            else if(Down & HidNpadButton_B) // If + is pressed, exit application
            {
                this->Close();
            }
            else if(Down & HidNpadButton_Plus) {

            }
        });
    }
} // namespace editor::ui

