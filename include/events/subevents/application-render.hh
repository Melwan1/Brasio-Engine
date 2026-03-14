#pragma once

#include <events/categories/application.hh>

namespace brasio::events::subevents
{
    class ApplicationRenderEvent
        : public categories::ApplicationCategoryEvent<ApplicationRenderEvent>
    {
    public:
        ApplicationRenderEvent();

        virtual std::string getTypeName() const override
        {
            return "ApplicationRenderEvent";
        }
    };
} // namespace brasio::events::subevents
