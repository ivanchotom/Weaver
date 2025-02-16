#pragma once

#include "internal/base/widget/IWidget.h"
#include "core/Element.h"
#include <memory>
#include <string>
#include <functional>

namespace UI
{
    class IButton : public IWidget
    {
    public:
        using IWidget::IWidget; // Inherit constructor
        virtual ~IButton() = default;
        virtual void click() = 0;
        virtual void setText(const std::string &text) = 0;
        virtual std::string getText() const = 0;
        virtual void setImage(void *textureId, float width, float height) = 0;
        virtual bool isClicked() const = 0;
    };
} // namespace UI