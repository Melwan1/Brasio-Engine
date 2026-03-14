#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class KeyboardReleaseEvent
        : public categories::KeyboardCategoryEvent<KeyboardReleaseEvent>
    {
    public:
        KeyboardReleaseEvent(const std::string &pressedKey);

        const std::string &getPressedKey() const;

        static KeyboardReleaseEvent create(int key, int scancode, int mods);

        virtual std::string getTypeName() const override
        {
            return "KeyboardReleaseEvent";
        }

        virtual void print(std::ostream &ostr) override;

    private:
        std::string _pressedKey;
    };
} // namespace brasio::events::subevents
