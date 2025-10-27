#include <events/listeners/keyboard-event-listeners.hh>

#include <iostream>

#include <io/escapes/ansi-escapes.hh>

template <typename KeyboardEventType>
static void printEvent(const KeyboardEventType &event)
{
    std::time_t creationTime =
        std::chrono::system_clock::to_time_t(event.getCreationTime());
    std::tm local_time = *std::localtime(&creationTime);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  event.getCreationTime().time_since_epoch())
        % 1000;
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - event.getCreationTime());

    std::cout << FG_ESC(244) << "[" << oss.str() << "."
              << std::format("{:03}", ms.count());
    std::cout << FG_ESC(15) << " in " << FG_ESC(76) << std::setw(3)
              << std::setfill(' ') << duration.count() << FG_ESC(15) << " ms";
    std::cout << "]" << FG_ESC(15) << " Handling " << event.getTypeName()
              << FG_ESC(220) << " " << event.getPressedKey() << ESC_RESET
              << "\n";
}

void KeyboardEventListener::onEvent(KeyboardLongPressEvent &event)
{
    printEvent<KeyboardLongPressEvent>(event);
    event.handle();
}

void KeyboardEventListener::onEvent(KeyboardPressEvent &event)
{
    printEvent<KeyboardPressEvent>(event);
    event.handle();
}

void KeyboardEventListener::onEvent(KeyboardReleaseEvent &event)
{
    printEvent<KeyboardReleaseEvent>(event);
    event.handle();
}
