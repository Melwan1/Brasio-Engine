#include <events/subevents/window-resize.hh>

WindowResizeEvent::WindowResizeEvent(bool toggleFullscreen, unsigned sizeX,
                                     unsigned sizeY)
    : WindowCategoryEvent<WindowResizeEvent>(EVENT_WINDOW_RESIZE)
    , _toggleFullscreen(toggleFullscreen)
    , _sizeX(sizeX)
    , _sizeY(sizeY)
{}

bool WindowResizeEvent::getToggleFullscreen() const
{
    return _toggleFullscreen;
}

unsigned WindowResizeEvent::getSizeX() const
{
    return _sizeX;
}

unsigned WindowResizeEvent::getSizeY() const
{
    return _sizeY;
}
