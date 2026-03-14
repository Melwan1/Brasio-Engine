#include <gtest/gtest.h>

#include <application/libapplication.hh>

TEST(Application_Init, returnValue)
{
    brasio::application::Application application;
    EXPECT_TRUE(application.init());
}

TEST(Application_Init, windowExists)
{
    brasio::application::Application application;
    application.init();
    EXPECT_NE(application.getWindow(), nullptr);
}
