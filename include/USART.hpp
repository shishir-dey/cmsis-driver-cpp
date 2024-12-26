#pragma once

#include <cstdint>
#include <functional>

namespace usart
{
    enum class Mode
    {
        Asynchronous,      // UART (Asynchronous)
        SynchronousMaster, // Synchronous Master (generates clock signal)
        SynchronousSlave,  // Synchronous Slave (external clock signal)
        SingleWire,        // UART Single-wire (half-duplex)
        IrDA,              // UART IrDA
        SmartCard          // UART Smart Card
    };

    enum class DataBits
    {
        Bits5 = 5,
        Bits6 = 6,
        Bits7 = 7,
        Bits8 = 8, // Default
        Bits9 = 9
    };

    enum class Parity
    {
        None, // Default
        Even,
        Odd
    };

    enum class StopBits
    {
        Bits1, // Default
        Bits2,
        Bits1_5,
        Bits0_5
    };

    enum class FlowControl
    {
        None, // Default
        RTS,
        CTS,
        RTS_CTS
    };

    enum class ClockPolarity
    {
        CPOL0, // Default
        CPOL1
    };

    enum class ClockPhase
    {
        CPHA0, // Default
        CPHA1
    };

    enum class ModemControl
    {
        RTSClear,
        RTSSet,
        DTRClear,
        DTRSet
    };

    struct Status
    {
        bool txBusy;         // Transmitter busy flag
        bool rxBusy;         // Receiver busy flag
        bool txUnderflow;    // Transmit data underflow detected
        bool rxOverflow;     // Receive data overflow detected
        bool rxBreak;        // Break detected on receive
        bool rxFramingError; // Framing error detected on receive
        bool rxParityError;  // Parity error detected on receive
    };

    struct ModemStatus
    {
        bool cts; // CTS state: true=Active, false=Inactive
        bool dsr; // DSR state: true=Active, false=Inactive
        bool dcd; // DCD state: true=Active, false=Inactive
        bool ri;  // RI state: true=Active, false=Inactive
    };

    enum class Event : uint32_t
    {
        SendComplete = (1UL << 0),     // Send completed
        ReceiveComplete = (1UL << 1),  // Receive completed
        TransferComplete = (1UL << 2), // Transfer completed
        TxComplete = (1UL << 3),       // Transmit completed
        TxUnderflow = (1UL << 4),      // Transmit data not available
        RxOverflow = (1UL << 5),       // Receive data overflow
        RxTimeout = (1UL << 6),        // Receive character timeout
        RxBreak = (1UL << 7),          // Break detected on receive
        RxFramingError = (1UL << 8),   // Framing error detected on receive
        RxParityError = (1UL << 9),    // Parity error detected on receive
        CTS = (1UL << 10),             // CTS state changed
        DSR = (1UL << 11),             // DSR state changed
        DCD = (1UL << 12),             // DCD state changed
        RI = (1UL << 13)               // RI state changed
    };

    class USART
    {
    public:
        using SignalEventCallback = std::function<void(Event event)>;

        virtual ~USART() = default;

        virtual int32_t initialize(SignalEventCallback callback) = 0;
        virtual int32_t uninitialize() = 0;
        virtual int32_t send(const void *data, uint32_t num) = 0;
        virtual int32_t receive(void *data, uint32_t num) = 0;
        virtual int32_t transfer(const void *dataOut, void *dataIn, uint32_t num) = 0;
        virtual uint32_t getTxCount() const = 0;
        virtual uint32_t getRxCount() const = 0;
        virtual int32_t control(uint32_t control, uint32_t arg) = 0;
        virtual Status getStatus() const = 0;
        virtual int32_t setModemControl(ModemControl control) = 0;
        virtual ModemStatus getModemStatus() const = 0;

    protected:
        USART() = default;
    };

} // namespace usart
