#pragma once

#include <events/categories/application.hh>

namespace brasio::events::subevents
{
    class ApplicationTickEvent
        : public categories::ApplicationCategoryEvent<ApplicationTickEvent>
    {
    public:
        ApplicationTickEvent();

        virtual std::string getTypeName() const override
        {
            return "ApplicationTickEvent";
        }
    };
} // namespace brasio::events::subevents
