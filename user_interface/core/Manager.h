#pragma once

#include "database/Database.h"
#include "factory/ImGuiFactory.h"
#include "window/Window.h"
#include <memory>
#include <string>

namespace UI
{
    class Manager
    {
    private:
        std::unique_ptr<Database> database;
        std::unique_ptr<ImGuiFactory> factory;
        std::shared_ptr<Window> rootWindow;

    public:
        Manager();
        ~Manager();

        void initialize();
        std::shared_ptr<Window> getRootWindow() const { return rootWindow; }
    };
} // namespace UI