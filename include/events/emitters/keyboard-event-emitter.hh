#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/keyboard-event-listeners.hh>

namespace brasio::events::emitters
{
    class KeyboardEventEmitter : public DefaultEventEmitter
    {
    public:
        virtual void fire(subevents::KeyboardPressEvent &event) override;
        virtual void fire(subevents::KeyboardLongPressEvent &event) override;
        virtual void fire(subevents::KeyboardReleaseEvent &event) override;

        void addListener(listeners::KeyboardEventListener &listener);

    private:
        std::vector<std::reference_wrapper<listeners::KeyboardEventListener>>
            _listeners;
    };
} // namespace brasio::events::emitters
