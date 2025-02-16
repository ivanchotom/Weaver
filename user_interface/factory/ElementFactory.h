#pragma once

#include "core/Element.h"
#include "window/Window.h"
#include "internal/base/widget/IWidget.h"
#include <memory>
#include <string>

namespace UI
{
    class Database;

    class ElementFactory
    {
    public:
        virtual ~ElementFactory() = default;

        // Base element creation
        virtual std::shared_ptr<Element> createElement(Database *db, std::shared_ptr<Element> parent, const std::string &name) = 0;

        // Window creation
        virtual std::shared_ptr<Window> createWindow(Database *db, std::shared_ptr<Element> parent, const std::string &name) = 0;

        // Widget creation template method
        template <typename T>
        std::shared_ptr<T> createWidget(Database *db, std::shared_ptr<Element> parent, const std::string &name)
        {
            if (!parent)
            {
                throw std::runtime_error("Parent cannot be null when creating a widget");
            }

            auto widget = createWidgetImpl(db, parent, name, typeid(T).name());
            return std::dynamic_pointer_cast<T>(widget);
        }

    protected:
        // Widget creation implementation to be overridden by concrete factories
        virtual std::shared_ptr<IWidget> createWidgetImpl(Database *db, std::shared_ptr<Element> parent, const std::string &name, const std::string &widgetType) = 0;
    };
} // namespace UI