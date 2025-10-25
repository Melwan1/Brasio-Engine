#include <gtest/gtest.h>

#include <application/libapplication.hh>

TEST(Application_Init, returnValue)
{
    Application application;
    EXPECT_TRUE(application.init());
}

TEST(Application_Init, windowExists)
{
    Application application;
    application.init();
    EXPECT_NE(application.getWindow(), nullptr);
}
