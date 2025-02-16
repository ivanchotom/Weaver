#include "window/Window.h"
#include "internal/imGui/window/ImGuiWindow.h"
#include "database/Database.h"
#include "core/Element.h"
#include "internal/base/window/IWindow.h"
#include <stdexcept>

namespace UI
{
    Window::Window(std::shared_ptr<IWindow> implementation)
        : IWindow(implementation->getParent(), implementation->getName()), impl(implementation)
    {
        if (!impl)
        {
            throw std::invalid_argument("Window implementation cannot be null");
        }
    }

    void Window::setFlags(WindowFlags flags)
    {
        impl->setFlags(flags);
    }

    void Window::setInitialSize(float width, float height, WindowCond cond)
    {
        impl->setInitialSize(width, height, cond);
    }

    void Window::setSizeConstraints(float minWidth, float minHeight, float maxWidth, float maxHeight)
    {
        impl->setSizeConstraints(minWidth, minHeight, maxWidth, maxHeight);
    }

    void Window::setInitialPosition(float x, float y, WindowCond cond)
    {
        impl->setInitialPosition(x, y, cond);
    }

    void Window::setBackgroundAlpha(float alpha)
    {
        impl->setBackgroundAlpha(alpha);
    }

    void Window::setScrollX(float scroll_x)
    {
        impl->setScrollX(scroll_x);
    }

    void Window::setScrollY(float scroll_y)
    {
        impl->setScrollY(scroll_y);
    }

    void Window::render()
    {
        impl->render();
    }
} // namespace UI