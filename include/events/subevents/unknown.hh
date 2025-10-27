#pragma once

#include <events/categories/categories.hh>

class UnknownEvent : public UnknownCategoryEvent<UnknownEvent>
{
public:
    UnknownEvent();

    virtual std::string getTypeName() const override
    {
        return "UnknownEvent";
    }
};
