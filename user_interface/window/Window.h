#pragma once
#include "internal/base/window/IWindow.h"
#include <memory>
#include <string>
#include <vector>

namespace UI
{
    class ImGuiWindow;
    class Database;
    class Element;

    class Window : public IWindow
    {
    private:
        std::shared_ptr<IWindow> impl;

    public:
        explicit Window(std::shared_ptr<IWindow> implementation);
        ~Window() = default;

        // IWindow interface
        void setFlags(WindowFlags flags) override;
        void setInitialSize(float width, float height, WindowCond cond = WindowCond::FirstUseEver) override;
        void setSizeConstraints(float minWidth, float minHeight, float maxWidth, float maxHeight) override;
        void setInitialPosition(float x, float y, WindowCond cond = WindowCond::Once) override;
        void setBackgroundAlpha(float alpha) override;
        void setScrollX(float scroll_x) override;
        void setScrollY(float scroll_y) override;

        // Element interface (inherited from IWindow)
        void render() override;
        std::shared_ptr<Element> getElement() override { return impl; }
        int getId() const override { return impl->getId(); }
        bool isVisible() const override { return impl->isVisible(); }
        void setVisible(bool visible) override { impl->setVisible(visible); }
        bool isEnabled() const override { return impl->isEnabled(); }
        void setEnabled(bool enabled) override { impl->setEnabled(enabled); }
        const std::string &getName() const override { return impl->getName(); }
        std::shared_ptr<Element> getParent() const override { return impl->getParent(); }
        const std::vector<std::shared_ptr<Element>> &getChildren() const override { return impl->getChildren(); }

        friend class ImGuiFactory;
    };
} // namespace UI