#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{

    class ApplicationUpdateEvent
        : public categories::ApplicationCategoryEvent<ApplicationUpdateEvent>
    {
    public:
        ApplicationUpdateEvent();

        virtual std::string getTypeName() const override
        {
            return "ApplicationUpdateEvent";
        }
    };
} // namespace brasio::events::subevents
