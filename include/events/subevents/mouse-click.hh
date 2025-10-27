#pragma once

#include <events/categories/categories.hh>

class MouseClickEvent : public MouseCategoryEvent<MouseClickEvent>
{
public:
    enum MouseClickType
    {
        MOUSE_CLICK_LEFT,
        MOUSE_CLICK_MIDDLE,
        MOUSE_CLICK_RIGHT,
    };

    MouseClickEvent(enum MouseClickType mouseClickType);

    enum MouseClickType getClickType() const;

    virtual std::string getTypeName() const override
    {
        return "MouseClickEvent";
    }

private:
    enum MouseClickType _mouseClickType;
};
