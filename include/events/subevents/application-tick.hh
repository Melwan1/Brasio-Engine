#pragma once

#include <events/categories/application.hh>

class ApplicationTickEvent
    : public ApplicationCategoryEvent<ApplicationTickEvent>
{
public:
    ApplicationTickEvent();
};
