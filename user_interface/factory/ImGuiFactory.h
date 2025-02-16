#pragma once

#include "factory/ElementFactory.h"
#include "widget/Button.h"
#include "window/Window.h"
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

namespace UI
{
    class ImGuiFactory : public ElementFactory
    {
    private:
        std::unordered_map<std::string, std::function<std::shared_ptr<IWidget>(Database *, std::shared_ptr<Element>, const std::string &)>> widgetCreators;

    public:
        ImGuiFactory();

        // Base element creation
        std::shared_ptr<Element> createElement(Database *db, std::shared_ptr<Element> parent, const std::string &name) override;

        // Window creation
        std::shared_ptr<Window> createWindow(Database *db, std::shared_ptr<Element> parent, const std::string &name) override;

    protected:
        std::shared_ptr<IWidget> createWidgetImpl(Database *db, std::shared_ptr<Element> parent, const std::string &name, const std::string &widgetType) override;

    private:
        // Register widget types
        void registerWidgetTypes();
    };
} // namespace UI