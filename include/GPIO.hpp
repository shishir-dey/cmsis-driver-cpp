#pragma once

#include <cstdint>
#include <functional>

namespace cmsis
{

    using Pin = uint32_t;

    enum class Direction
    {
        Input, // Input (default)
        Output // Output
    };

    enum class OutputMode
    {
        PushPull, // Push-pull (default)
        OpenDrain // Open-drain
    };

    enum class PullResistor
    {
        None,    // None (default)
        PullUp,  // Pull-up
        PullDown // Pull-down
    };

    enum class EventTrigger
    {
        None,        // None (default)
        RisingEdge,  // Rising-edge
        FallingEdge, // Falling-edge
        EitherEdge   // Either edge (rising and falling)
    };

    enum class EventType : uint32_t
    {
        RisingEdge = (1UL << 0),  // Rising-edge detected
        FallingEdge = (1UL << 1), // Falling-edge detected
        EitherEdge = (1UL << 2)   // Either edge detected
    };

    class GPIO
    {
    public:
        using SignalEventCallback = std::function<void(Pin pin, EventType event)>;

        virtual ~GPIO() = default;

        virtual int32_t setup(Pin pin, SignalEventCallback callback) = 0;
        virtual int32_t setDirection(Pin pin, Direction direction) = 0;
        virtual int32_t setOutputMode(Pin pin, OutputMode mode) = 0;
        virtual int32_t setPullResistor(Pin pin, PullResistor resistor) = 0;
        virtual int32_t setEventTrigger(Pin pin, EventTrigger trigger) = 0;
        virtual void setOutput(Pin pin, uint32_t value) = 0;
        virtual uint32_t getInput(Pin pin) const = 0;

    protected:
        GPIO() = default;
    };

} // namespace gpio
