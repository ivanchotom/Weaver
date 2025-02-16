#pragma once
#include "base/window/IWindow.h"
#include "core/Element.h"
#include <string>
#include <memory>
#include "imgui.h"

namespace UI
{
    class ImGuiWindow : public IWindow
    {
    private:
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        WindowFlags windowFlags = WindowFlags::None;
        ImVec2 initialSize = ImVec2(-1.0f, -1.0f);
        ImVec2 minSize = ImVec2(-1.0f, -1.0f);
        ImVec2 maxSize = ImVec2(-1.0f, -1.0f);
        ImVec2 initialPos = ImVec2(-1.0f, -1.0f);
        float bgAlpha = 1.0f;
        WindowCond sizeCondition = WindowCond::FirstUseEver;
        WindowCond posCondition = WindowCond::Once;
        float scroll_x = 0.0f;
        float scroll_y = 0.0f;

        ImGuiWindowFlags convertFlags(WindowFlags flags);
        ImGuiCond convertCond(WindowCond cond);

    public:
        ImGuiWindow(std::shared_ptr<Element> parent, const std::string &name);
        virtual ~ImGuiWindow() = default;

        // Element implementation (inherited through IWindow)
        void render() override;

        // Add these to the public section
        std::shared_ptr<Element> getElement() override { return shared_from_this(); }
        int getId() const override { return Element::getId(); }

        // IWindow implementation
        void setFlags(WindowFlags flags) override;
        void setInitialSize(float width, float height, WindowCond cond = WindowCond::FirstUseEver) override;
        void setSizeConstraints(float minWidth, float minHeight, float maxWidth, float maxHeight) override;
        void setInitialPosition(float x, float y, WindowCond cond = WindowCond::Once) override;
        void setBackgroundAlpha(float alpha) override;
        void setScrollX(float scroll_x) override;
        void setScrollY(float scroll_y) override;

        // Additional ImGui-specific functionality
        bool isDemoWindow() const;
        void setDemoWindow(bool show);
        const ImVec4 &getClearColor() const;
        void setClearColor(const ImVec4 &color);
    };
} // namespace UI