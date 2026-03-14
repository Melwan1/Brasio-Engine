#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class WindowResizeEvent
        : public categories::WindowCategoryEvent<WindowResizeEvent>
    {
    public:
        WindowResizeEvent(bool toggleFullscreen, unsigned sizeX,
                          unsigned sizeY);

        bool getToggleFullscreen() const;
        unsigned getSizeX() const;
        unsigned getSizeY() const;

        virtual std::string getTypeName() const override
        {
            return "WindowResizeEvent";
        }

    private:
        bool _toggleFullscreen;
        unsigned _sizeX;
        unsigned _sizeY;
    };
} // namespace brasio::events::subevents
