#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class KeyboardPressEvent
        : public categories::KeyboardCategoryEvent<KeyboardPressEvent>
    {
    public:
        KeyboardPressEvent(const std::string &pressedKey);
        const std::string &getPressedKey() const;

        static KeyboardPressEvent create(int key, int scancode, int mods);

        virtual std::string getTypeName() const override
        {
            return "KeyboardPressEvent";
        }

        virtual void print(std::ostream &ostr) override;

    private:
        std::string _pressedKey;
    };
} // namespace brasio::events::subevents
