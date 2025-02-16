#include "ImGuiButton.h"
#include <stdexcept>

namespace UI
{
    ImGuiButton::ImGuiButton(std::shared_ptr<Element> parent, const std::string &name)
        : IButton(parent, name)
    {
    }

    void ImGuiButton::render()
    {
        if (!isVisible())
            return;

        ImGui::BeginDisabled(!isEnabled());

        bool clicked = false;
        if (textureId != nullptr)
        {
            clicked = ImGui::ImageButton(getName().c_str(),
                                         reinterpret_cast<ImTextureID>(textureId),
                                         imageSize);
        }
        else
        {
            clicked = ImGui::Button(text.empty() ? getName().c_str() : text.c_str());
        }

        if (clicked && isEnabled() && onClick)
        {
            onClick();
        }

        ImGui::EndDisabled();

        if (isFocused())
        {
            ImGui::SetKeyboardFocusHere(-1);
        }

        if (ImGui::IsItemHovered() && onHover)
        {
            onHover();
        }

        if (ImGui::IsItemFocused())
        {
            setFocused(true);
            if (onFocus)
            {
                onFocus();
            }
        }
        else
        {
            setFocused(false);
        }

        if (!tooltipText.empty() && ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("%s", tooltipText.c_str());
        }

        _isClicked = clicked;
    }

    void ImGuiButton::setVisible(bool visible)
    {
        Element::setVisible(visible);
        _isVisible = visible;
    }

    bool ImGuiButton::isVisible() const
    {
        return Element::isVisible() && _isVisible;
    }

    void ImGuiButton::setEnabled(bool enabled)
    {
        Element::setEnabled(enabled);
        _isEnabled = enabled;
    }

    bool ImGuiButton::isEnabled() const
    {
        return Element::isEnabled() && _isEnabled;
    }

    void ImGuiButton::setFocused(bool focused)
    {
        _isFocused = focused;
    }

    bool ImGuiButton::isFocused() const
    {
        return _isFocused;
    }

    std::shared_ptr<Element> ImGuiButton::getElement()
    {
        return shared_from_this();
    }

    void ImGuiButton::setText(const std::string &newText)
    {
        text = newText;
    }

    std::string ImGuiButton::getText() const
    {
        return text;
    }

    void ImGuiButton::setImage(void *newTextureId, float width, float height)
    {
        textureId = newTextureId;
        imageSize = ImVec2(width, height);
    }
    void ImGuiButton::click()
    {
        if (_isEnabled && onClick)
        {
            onClick();
        }
    }

    bool ImGuiButton::isClicked() const
    {
        return _isClicked;
    }

    void ImGuiButton::setTooltip(const std::string &tooltip)
    {
        tooltipText = tooltip;
    }
} // namespace UI