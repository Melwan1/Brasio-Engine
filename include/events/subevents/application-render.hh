#pragma once

#include <events/categories/application.hh>

class ApplicationRenderEvent
    : public ApplicationCategoryEvent<ApplicationRenderEvent>
{
public:
    ApplicationRenderEvent();
};
