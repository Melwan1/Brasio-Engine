#pragma once

#include <events/categories/categories.hh>

class MouseMoveEvent : public MouseCategoryEvent<MouseMoveEvent>
{
public:
    MouseMoveEvent(unsigned positionX, unsigned positionY);

    unsigned getPositionX() const;
    unsigned getPositionY() const;

private:
    unsigned _positionX;
    unsigned _positionY;
};
