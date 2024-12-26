#pragma once

#include <cstdint>
#include <functional>

namespace flash
{

    struct SectorInfo
    {
        uint32_t start; // Sector start address
        uint32_t end;   // Sector end address (start+size-1)
    };

    struct FlashInfo
    {
        SectorInfo *sectorInfo; // Sector layout information (nullptr=Uniform sectors)
        uint32_t sectorCount;   // Number of sectors
        uint32_t sectorSize;    // Uniform sector size in bytes (0=sectorInfo used)
        uint32_t pageSize;      // Optimal programming page size in bytes
        uint32_t programUnit;   // Smallest programmable unit in bytes
        uint8_t erasedValue;    // Contents of erased memory (usually 0xFF)
    };

    struct Status
    {
        bool busy;  // Flash busy flag
        bool error; // Read/Program/Erase error flag
    };

    enum class Event : uint32_t
    {
        Ready = (1UL << 0), // Flash Ready
        Error = (1UL << 1)  // Read/Program/Erase Error
    };

    class Flash
    {
    public:
        using SignalEventCallback = std::function<void(Event event)>;

        virtual ~Flash() = default;

        virtual int32_t initialize(SignalEventCallback callback) = 0;
        virtual int32_t uninitialize() = 0;
        virtual int32_t readData(uint32_t addr, void *data, uint32_t count) = 0;
        virtual int32_t programData(uint32_t addr, const void *data, uint32_t count) = 0;
        virtual int32_t eraseSector(uint32_t addr) = 0;
        virtual int32_t eraseChip() = 0;
        virtual Status getStatus() const = 0;
        virtual const FlashInfo *getInfo() const = 0;

    protected:
        Flash() = default;
    };

} // namespace flash
