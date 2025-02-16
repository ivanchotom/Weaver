#pragma once

#include "factory/ImGuiFactory.h"
#include "internal/imGui/widget/ImGuiButton.h"
#include "internal/imGui/window/ImGuiWindow.h"
#include "widget/Button.h"
#include "window/Window.h"
#include "database/Database.h"
#include <stdexcept>
#include <typeinfo>

namespace UI
{
    ImGuiFactory::ImGuiFactory()
    {
        registerWidgetTypes();
    }

    void ImGuiFactory::registerWidgetTypes()
    {
        // Register Button widget type
        widgetCreators[typeid(Button).name()] = [](Database *db, std::shared_ptr<Element> parent, const std::string &name) -> std::shared_ptr<IWidget>
        {
            auto implButton = std::make_shared<ImGuiButton>(parent, name);
            if (db)
            {
                implButton->registerWithDatabase(db);
            }
            return std::make_shared<Button>(implButton);
        };

        // Register other widget types here as needed
    }

    std::shared_ptr<Element> ImGuiFactory::createElement(Database *db, std::shared_ptr<Element> parent, const std::string &name)
    {
        // Cannot create abstract Element directly
        throw std::runtime_error("Cannot create abstract Element directly");
    }

    std::shared_ptr<Window> ImGuiFactory::createWindow(Database *db, std::shared_ptr<Element> parent, const std::string &name)
    {
        auto internalWindow = std::make_shared<ImGuiWindow>(parent, name);
        if (db)
        {
            internalWindow->registerWithDatabase(db);
        }

        std::shared_ptr<IWindow> uiWindow = std::dynamic_pointer_cast<IWindow>(internalWindow);
        if (!uiWindow)
        {
            throw std::runtime_error("Failed to cast to IWindow");
        }

        return std::shared_ptr<Window>(new Window(uiWindow));
    }

    std::shared_ptr<IWidget> ImGuiFactory::createWidgetImpl(Database *db, std::shared_ptr<Element> parent, const std::string &name, const std::string &widgetType)
    {
        auto it = widgetCreators.find(widgetType);
        if (it == widgetCreators.end())
        {
            throw std::runtime_error("Unknown widget type: " + widgetType);
        }

        return it->second(db, parent, name);
    }
} // namespace UI