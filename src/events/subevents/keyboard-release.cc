#include <events/subevents/keyboard-release.hh>

KeyboardReleaseEvent::KeyboardReleaseEvent()
    : KeyboardCategoryEvent<KeyboardReleaseEvent>(EVENT_KEYBOARD_RELEASE)
{}
