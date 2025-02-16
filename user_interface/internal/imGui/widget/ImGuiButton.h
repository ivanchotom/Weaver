#pragma once

#include "base/widget/IButton.h"
#include "core/Element.h"
#include "imgui.h"
#include <string>
#include <functional>

namespace UI
{
    class ImGuiButton : public IButton
    {
    private:
        std::string text;
        bool _isEnabled = true;
        bool _isVisible = true;
        std::function<void()> onClick;
        std::function<void()> onHover;
        std::function<void()> onFocus;
        std::string tooltipText;
        bool _isFocused = false;
        bool _isClicked = false;
        bool _isHovered = false;

        // Image properties
        void *textureId = nullptr;
        ImVec2 imageSize = ImVec2(0, 0);

    public:
        ImGuiButton(std::shared_ptr<Element> parent, const std::string &name);
        virtual ~ImGuiButton() = default;

        // IWidget implementation
        void setVisible(bool visible) override;
        bool isVisible() const override;
        void setEnabled(bool enabled) override;
        bool isEnabled() const override;
        void setFocused(bool focused) override;
        bool isFocused() const override;
        std::shared_ptr<Element> getElement() override;

        // Element implementation
        void render() override;

        // IButton implementation
        void click() override;
        void setText(const std::string &text) override;
        std::string getText() const override;
        void setImage(void *textureId, float width, float height) override;
        bool isClicked() const override;

        // ImGui-specific
        void setTooltip(const std::string &tooltip);
    };
} // namespace UI