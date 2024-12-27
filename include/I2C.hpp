#pragma once

#include <cstdint>
#include <functional>

namespace cmsis
{
    enum class BusSpeed
    {
        Standard, // Standard Speed (100kHz)
        Fast,     // Fast Speed (400kHz)
        FastPlus, // Fast+ Speed (1MHz)
        High      // High Speed (3.4MHz)
    };

    struct Status
    {
        bool busy;            // Busy flag
        bool masterMode;      // Mode: false=Slave, true=Master
        bool receiving;       // Direction: false=Transmitter, true=Receiver
        bool generalCall;     // General Call indication
        bool arbitrationLost; // Master lost arbitration
        bool busError;        // Bus error detected
    };

    enum class Event : uint32_t
    {
        TransferDone = (1UL << 0),       // Master/Slave Transmit/Receive finished
        TransferIncomplete = (1UL << 1), // Master/Slave Transmit/Receive incomplete
        SlaveTransmit = (1UL << 2),      // Addressed as Slave Transmitter
        SlaveReceive = (1UL << 3),       // Addressed as Slave Receiver
        AddressNack = (1UL << 4),        // Address not acknowledged
        GeneralCall = (1UL << 5),        // Slave addressed with general call
        ArbitrationLost = (1UL << 6),    // Master lost arbitration
        BusError = (1UL << 7),           // Bus error detected
        BusCleared = (1UL << 8)          // Bus clear finished
    };

    class I2C
    {
    public:
        using SignalEventCallback = std::function<void(Event event)>;

        virtual ~I2C() = default;

        virtual int32_t initialize(SignalEventCallback callback) = 0;
        virtual int32_t uninitialize() = 0;
        virtual int32_t masterTransmit(uint32_t addr, const uint8_t *data, uint32_t count, bool xferPending) = 0;
        virtual int32_t masterReceive(uint32_t addr, uint8_t *data, uint32_t count, bool xferPending) = 0;
        virtual int32_t slaveTransmit(const uint8_t *data, uint32_t count) = 0;
        virtual int32_t slaveReceive(uint8_t *data, uint32_t count) = 0;
        virtual int32_t getDataCount() const = 0;
        virtual int32_t setBusSpeed(BusSpeed speed) = 0;
        virtual int32_t setOwnAddress(uint32_t address) = 0;
        virtual int32_t clearBus() = 0;
        virtual int32_t abortTransfer() = 0;
        virtual Status getStatus() const = 0;

    protected:
        I2C() = default;
    };

} // namespace i2c
