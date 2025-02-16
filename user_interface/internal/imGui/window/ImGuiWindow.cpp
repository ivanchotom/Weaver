#include "ImGuiWindow.h"
#include <stdexcept>

namespace UI
{
    ImGuiWindow::ImGuiWindow(std::shared_ptr<Element> parent, const std::string &name)
        : IWindow(parent, name)
    {
    }

    void ImGuiWindow::render()
    {
        // Apply settings BEFORE ImGui::Begin()
        if (initialSize.x > 0 && initialSize.y > 0)
        {
            ImGui::SetNextWindowSize(initialSize, convertCond(sizeCondition));
        }
        if (minSize.x > 0 && minSize.y > 0 && maxSize.x > 0 && maxSize.y > 0)
        {
            ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        }

        if (initialPos.x >= 0 && initialPos.y >= 0)
        {
            ImGui::SetNextWindowPos(initialPos, convertCond(posCondition));
        }
        ImGui::SetNextWindowBgAlpha(bgAlpha);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        bool windowOpen = true;
        ImGui::Begin(getName().c_str(), &windowOpen, convertFlags(windowFlags));

        // Render children
        for (const auto &child : getChildren())
        {
            child->render();
        }

        if (scroll_x != 0.0f)
            ImGui::SetScrollHereX(scroll_x);
        if (scroll_y != 0.0f)
            ImGui::SetScrollHereY(scroll_y);

        ImGui::End();

        if (!windowOpen)
        {
            // Window was closed by user
            if (auto parent = getParent())
            {
                parent->removeChild(shared_from_this());
            }
        }
    }

    void ImGuiWindow::setFlags(WindowFlags flags)
    {
        windowFlags = flags;
    }

    void ImGuiWindow::setInitialSize(float width, float height, WindowCond cond)
    {
        initialSize = ImVec2(width, height);
        sizeCondition = cond;
    }

    void ImGuiWindow::setSizeConstraints(float minWidth, float minHeight, float maxWidth, float maxHeight)
    {
        minSize = ImVec2(minWidth, minHeight);
        maxSize = ImVec2(maxWidth, maxHeight);
    }

    void ImGuiWindow::setInitialPosition(float x, float y, WindowCond cond)
    {
        initialPos = ImVec2(x, y);
        posCondition = cond;
    }

    void ImGuiWindow::setBackgroundAlpha(float alpha)
    {
        bgAlpha = alpha;
    }

    void ImGuiWindow::setScrollX(float x)
    {
        scroll_x = x;
    }

    void ImGuiWindow::setScrollY(float y)
    {
        scroll_y = y;
    }

    bool ImGuiWindow::isDemoWindow() const
    {
        return show_demo_window;
    }

    void ImGuiWindow::setDemoWindow(bool show)
    {
        show_demo_window = show;
    }

    const ImVec4 &ImGuiWindow::getClearColor() const
    {
        return clear_color;
    }

    void ImGuiWindow::setClearColor(const ImVec4 &color)
    {
        clear_color = color;
    }

    ImGuiWindowFlags ImGuiWindow::convertFlags(WindowFlags flags)
    {
        ImGuiWindowFlags imFlags = 0;

        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoTitleBar))
            imFlags |= ImGuiWindowFlags_NoTitleBar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoResize))
            imFlags |= ImGuiWindowFlags_NoResize;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoMove))
            imFlags |= ImGuiWindowFlags_NoMove;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoScrollbar))
            imFlags |= ImGuiWindowFlags_NoScrollbar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoCollapse))
            imFlags |= ImGuiWindowFlags_NoCollapse;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::AlwaysAutoResize))
            imFlags |= ImGuiWindowFlags_AlwaysAutoResize;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoBackground))
            imFlags |= ImGuiWindowFlags_NoBackground;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoSavedSettings))
            imFlags |= ImGuiWindowFlags_NoSavedSettings;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoMouseInputs))
            imFlags |= ImGuiWindowFlags_NoMouseInputs;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::MenuBar))
            imFlags |= ImGuiWindowFlags_MenuBar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::HorizontalScrollbar))
            imFlags |= ImGuiWindowFlags_HorizontalScrollbar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoFocusOnAppearing))
            imFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoBringToFrontOnFocus))
            imFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::AlwaysVerticalScrollbar))
            imFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::AlwaysHorizontalScrollbar))
            imFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::AlwaysUseWindowPadding))
            imFlags |= ImGuiWindowFlags_AlwaysUseWindowPadding;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoNavInputs))
            imFlags |= ImGuiWindowFlags_NoNavInputs;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::NoNavFocus))
            imFlags |= ImGuiWindowFlags_NoNavFocus;
        if (static_cast<int>(flags) & static_cast<int>(WindowFlags::UnsavedDocument))
            imFlags |= ImGuiWindowFlags_UnsavedDocument;

        return imFlags;
    }

    ImGuiCond ImGuiWindow::convertCond(WindowCond cond)
    {
        switch (cond)
        {
        case WindowCond::Always:
            return ImGuiCond_Always;
        case WindowCond::Once:
            return ImGuiCond_Once;
        case WindowCond::FirstUseEver:
            return ImGuiCond_FirstUseEver;
        case WindowCond::Appearing:
            return ImGuiCond_Appearing;
        default:
            return ImGuiCond_None;
        }
    }
} // namespace UI