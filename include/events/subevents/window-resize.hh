#pragma once

#include <events/libevents.hh>

class WindowResizeEvent : public WindowCategoryEvent<WindowResizeEvent>
{
public:
    WindowResizeEvent(bool toggleFullscreen, unsigned sizeX, unsigned sizeY);

    bool getToggleFullscreen() const;
    unsigned getSizeX() const;
    unsigned getSizeY() const;

private:
    bool _toggleFullscreen;
    unsigned _sizeX;
    unsigned _sizeY;
};
