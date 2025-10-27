#pragma once

#include <events/categories/categories.hh>

class ApplicationUpdateEvent
    : public ApplicationCategoryEvent<ApplicationUpdateEvent>
{
public:
    ApplicationUpdateEvent();

    virtual std::string getTypeName() const override
    {
        return "ApplicationUpdateEvent";
    }
};
