#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/mouse-event-listener.hh>

namespace brasio::events::emitters
{
    class MouseEventEmitter : public DefaultEventEmitter
    {
    public:
        virtual void fire(subevents::MouseClickEvent &event) override;
        virtual void fire(subevents::MouseMoveEvent &event) override;
        virtual void fire(subevents::MouseReleaseEvent &event) override;
        virtual void fire(subevents::MouseScrollEvent &event) override;

        void addListener(listeners::MouseEventListener &listener);

    private:
        std::vector<std::reference_wrapper<listeners::MouseEventListener>>
            _listeners;
    };
} // namespace brasio::events::emitters
