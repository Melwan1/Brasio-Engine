#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/window-event-listener.hh>

namespace brasio::events::emitters
{
    class WindowEventEmitter : public DefaultEventEmitter
    {
    public:
        virtual void fire(subevents::WindowCloseEvent &event) override;
        virtual void fire(subevents::WindowFocusEvent &event) override;
        virtual void fire(subevents::WindowLostFocusEvent &event) override;
        virtual void fire(subevents::WindowMoveEvent &event) override;
        virtual void fire(subevents::WindowResizeEvent &event) override;

        void addListener(listeners::WindowEventListener &listener);

    private:
        std::vector<std::reference_wrapper<listeners::WindowEventListener>>
            _listeners;
    };
} // namespace brasio::events::emitters
