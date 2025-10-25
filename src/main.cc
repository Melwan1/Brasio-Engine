#include <iostream>

#include <application/libapplication.hh>

int main()
{
    Application application;
    if (!application.init())
    {
        return 1;
    }
    application.loop();
    return 0;
}
