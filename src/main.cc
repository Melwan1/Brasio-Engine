#include <application/libapplication.hh>

int main()
{
    brasio::application::Application application;
    if (!application.init())
    {
        return 1;
    }
    application.loop();
    return 0;
}
