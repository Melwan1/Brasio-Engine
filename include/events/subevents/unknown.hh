#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class UnknownEvent : public categories::UnknownCategoryEvent<UnknownEvent>
    {
    public:
        UnknownEvent();

        virtual std::string getTypeName() const override
        {
            return "UnknownEvent";
        }
    };
} // namespace brasio::events::subevents
