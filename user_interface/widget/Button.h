#pragma once

#include <string>
#include <memory>
#include "internal/base/widget/IButton.h"
#include <functional>

namespace UI
{
    class ImGuiButton;
    class Database;
    class Element;

    class Button : public IButton
    {
    private:
        std::shared_ptr<IButton> impl;

    public:
        Button(std::shared_ptr<IButton> implementation);
        virtual ~Button() = default;

        // IWidget interface (inherited from IButton)
        void setVisible(bool visible) override;
        bool isVisible() const override;
        void setEnabled(bool enabled) override;
        bool isEnabled() const override;
        void setFocused(bool focused) override;
        bool isFocused() const override;
        std::shared_ptr<Element> getElement() override;
        void render() override;

        // IButton interface
        void click() override;
        void setText(const std::string &text) override;
        std::string getText() const override;
        void setImage(void *textureId, float width, float height) override;
        bool isClicked() const override;

        friend class ImGuiFactory;
    };
} // namespace UI