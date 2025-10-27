#pragma once

#include <events/categories/categories.hh>

class MouseMoveEvent : public MouseCategoryEvent<MouseMoveEvent>
{
public:
    MouseMoveEvent(unsigned positionX, unsigned positionY);

    unsigned getPositionX() const;
    unsigned getPositionY() const;

    virtual std::string getTypeName() const override
    {
        return "MouseMoveEvent";
    }

private:
    unsigned _positionX;
    unsigned _positionY;
};
