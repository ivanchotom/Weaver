#pragma once

#include "core/Element.h"
#include <memory>
#include <cstdint>

namespace UI
{
    enum class WindowFlags : uint32_t
    {
        None = 0,
        NoTitleBar = 1 << 0,
        NoResize = 1 << 1,
        NoMove = 1 << 2,
        NoScrollbar = 1 << 3,
        NoCollapse = 1 << 4,
        AlwaysAutoResize = 1 << 5,
        NoBackground = 1 << 6,
        NoSavedSettings = 1 << 7,
        NoMouseInputs = 1 << 8,
        MenuBar = 1 << 9,
        HorizontalScrollbar = 1 << 10,
        NoFocusOnAppearing = 1 << 11,
        NoBringToFrontOnFocus = 1 << 12,
        AlwaysVerticalScrollbar = 1 << 13,
        AlwaysHorizontalScrollbar = 1 << 14,
        AlwaysUseWindowPadding = 1 << 15,
        NoNavInputs = 1 << 16,
        NoNavFocus = 1 << 17,
        UnsavedDocument = 1 << 18,
        NoNav = NoNavInputs | NoNavFocus,
        NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
        NoInputs = NoMouseInputs | NoNavInputs | NoNavFocus,
    };

    // Operator overloads for WindowFlags
    inline WindowFlags operator|(WindowFlags a, WindowFlags b)
    {
        return static_cast<WindowFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline WindowFlags operator&(WindowFlags a, WindowFlags b)
    {
        return static_cast<WindowFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    enum class WindowCond
    {
        None = 0,
        Always = 1 << 0,
        Once = 1 << 1,
        FirstUseEver = 1 << 2,
        Appearing = 1 << 3
    };

    class IWindow : public Element
    {
    public:
        IWindow(std::shared_ptr<Element> parent, const std::string &name)
            : Element(parent, name) {}
        virtual ~IWindow() = default;

        virtual void setFlags(WindowFlags flags) = 0;
        virtual void setInitialSize(float width, float height, WindowCond cond = WindowCond::FirstUseEver) = 0;
        virtual void setSizeConstraints(float minWidth, float minHeight, float maxWidth, float maxHeight) = 0;
        virtual void setInitialPosition(float x, float y, WindowCond cond = WindowCond::Once) = 0;
        virtual void setBackgroundAlpha(float alpha) = 0;
        virtual void setScrollX(float scroll_x) = 0;
        virtual void setScrollY(float scroll_y) = 0;
    };
} // namespace UI