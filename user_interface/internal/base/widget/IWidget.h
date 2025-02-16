#pragma once
#include "core/Element.h"
#include <functional>

namespace UI
{
    class IWidget : public Element
    {
    public:
        IWidget(std::shared_ptr<Element> parent, const std::string &name)
            : Element(parent, name) {}
        virtual ~IWidget() = default;

        // Widget state
        virtual void setVisible(bool visible) = 0;
        virtual bool isVisible() const = 0;
        virtual void setEnabled(bool enabled) = 0;
        virtual bool isEnabled() const = 0;

        // Focus management
        virtual void setFocused(bool focused) = 0;
        virtual bool isFocused() const = 0;

        // Element access
        virtual std::shared_ptr<Element> getElement() = 0;
    };
} // namespace UI