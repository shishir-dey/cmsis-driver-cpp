#pragma once

#include <cstdint>
#include <functional>

namespace cmsis
{
    enum class Mode
    {
        Inactive,
        Master,
        Slave
    };

    enum class FrameFormat
    {
        CPOL0_CPHA0, // Clock Polarity 0, Clock Phase 0 (default)
        CPOL0_CPHA1, // Clock Polarity 0, Clock Phase 1
        CPOL1_CPHA0, // Clock Polarity 1, Clock Phase 0
        CPOL1_CPHA1, // Clock Polarity 1, Clock Phase 1
        TI_SSI,      // Texas Instruments Frame Format
        Microwire    // National Semiconductor Microwire Frame Format
    };

    enum class BitOrder
    {
        MSB_LSB, // MSB to LSB (default)
        LSB_MSB  // LSB to MSB
    };

    enum class SlaveSelectMode
    {
        MasterUnused,   // Not used (default)
        MasterSoftware, // Software controlled
        MasterHwOutput, // Hardware controlled Output
        MasterHwInput,  // Hardware monitored Input
        SlaveHardware,  // Hardware monitored (default)
        SlaveSoftware   // Software controlled
    };

    struct Status
    {
        bool busy;      // Transmitter/Receiver busy flag
        bool dataLost;  // Data lost: Receive overflow / Transmit underflow
        bool modeFault; // Mode fault detected
    };

    enum class Event : uint32_t
    {
        TransferComplete = (1UL << 0), // Data Transfer completed
        DataLost = (1UL << 1),         // Data lost: Receive overflow / Transmit underflow
        ModeFault = (1UL << 2)         // Master Mode Fault (SS deactivated when Master)
    };

    class SPI
    {
    public:
        using SignalEventCallback = std::function<void(Event event)>;

        virtual ~SPI() = default;

        virtual int32_t initialize(SignalEventCallback callback) = 0;
        virtual int32_t uninitialize() = 0;
        virtual int32_t send(const void *data, uint32_t num) = 0;
        virtual int32_t receive(void *data, uint32_t num) = 0;
        virtual int32_t transfer(const void *dataOut, void *dataIn, uint32_t num) = 0;
        virtual uint32_t getDataCount() const = 0;
        virtual int32_t control(uint32_t control, uint32_t arg) = 0;
        virtual Status getStatus() const = 0;

    protected:
        SPI() = default;
    };

} // namespace spi
