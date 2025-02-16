#include "Button.h"
#include "internal/imGui/widget/ImGuiButton.h"
#include <stdexcept>

namespace UI
{
    Button::Button(std::shared_ptr<IButton> implementation)
        : IButton(implementation->getElement()->getParent(), implementation->getElement()->getName()), impl(implementation)
    {
        if (!impl)
        {
            throw std::invalid_argument("Button implementation cannot be null");
        }
    }

    // IWidget interface implementation
    void Button::setVisible(bool visible)
    {
        impl->setVisible(visible);
    }

    bool Button::isVisible() const
    {
        return impl->isVisible();
    }

    void Button::setEnabled(bool enabled)
    {
        impl->setEnabled(enabled);
    }

    bool Button::isEnabled() const
    {
        return impl->isEnabled();
    }

    void Button::setFocused(bool focused)
    {
        impl->setFocused(focused);
    }

    bool Button::isFocused() const
    {
        return impl->isFocused();
    }

    std::shared_ptr<Element> Button::getElement()
    {
        return impl->getElement();
    }

    void Button::render()
    {
        impl->render();
    }

    // IButton interface implementation
    void Button::click()
    {
        impl->click();
    }

    void Button::setText(const std::string &text)
    {
        impl->setText(text);
    }

    std::string Button::getText() const
    {
        return impl->getText();
    }

    void Button::setImage(void *textureId, float width, float height)
    {
        impl->setImage(textureId, width, height);
    }

    bool Button::isClicked() const
    {
        return impl->isClicked();
    }
} // namespace UI