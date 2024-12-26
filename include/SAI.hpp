#pragma once

#include <cstdint>
#include <functional>

namespace sai
{
    enum class Mode
    {
        Master,
        Slave
    };

    enum class Synchronization
    {
        Asynchronous,
        Synchronous
    };

    enum class Protocol
    {
        User,
        I2S,
        MSBJustified,
        LSBJustified,
        PCMShort,
        PCMLong,
        AC97
    };

    enum class BitOrder
    {
        MSBFirst,
        LSBFirst
    };

    enum class Companding
    {
        None,
        ALaw,
        ULaw
    };

    enum class ClockPolarity
    {
        FallingEdge, // Drive on falling edge, Capture on rising edge
        RisingEdge   // Drive on rising edge, Capture on falling edge
    };

    enum class MasterClockPin
    {
        Inactive,
        Output,
        Input
    };

    enum class FrameSyncPolarity
    {
        High,
        Low
    };

    struct Status
    {
        bool txBusy;      // Transmitter busy flag
        bool rxBusy;      // Receiver busy flag
        bool txUnderflow; // Transmit data underflow detected
        bool rxOverflow;  // Receive data overflow detected
        bool frameError;  // Sync Frame error detected
    };

    enum class Event : uint32_t
    {
        SendComplete = (1UL << 0),    // Send completed
        ReceiveComplete = (1UL << 1), // Receive completed
        TxUnderflow = (1UL << 2),     // Transmit data not available
        RxOverflow = (1UL << 3),      // Receive data overflow
        FrameError = (1UL << 4)       // Sync Frame error in Slave mode
    };

    class SAI
    {
    public:
        using SignalEventCallback = std::function<void(Event event)>;

        virtual ~SAI() = default;

        virtual int32_t initialize(SignalEventCallback callback) = 0;
        virtual int32_t uninitialize() = 0;
        virtual int32_t send(const void *data, uint32_t num) = 0;
        virtual int32_t receive(void *data, uint32_t num) = 0;
        virtual uint32_t getTxCount() const = 0;
        virtual uint32_t getRxCount() const = 0;
        virtual Status getStatus() const = 0;

    protected:
        SAI() = default;
    };

} // namespace sai
