#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class WindowMoveEvent
        : public categories::WindowCategoryEvent<WindowMoveEvent>
    {
    public:
        WindowMoveEvent(int downBy, int rightBy);

        int getDownDisplacement() const;
        int getUpDisplacement() const;
        int getLeftDisplacement() const;
        int getRightDisplacement() const;

        virtual std::string getTypeName() const override
        {
            return "WindowMoveEvent";
        }

    private:
        int _downBy;
        int _rightBy;
    };
} // namespace brasio::events::subevents
