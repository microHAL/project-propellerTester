#ifndef BATTERY_H
#define BATTERY_H

#include <cstdint>
#include <string>

class Battery
{
 public:
    using Manufacturer = std::string;
    using Type = std::string;
    using Capacity = float;
    using Voltage = float;
    using Current = float;

    enum class CellType {
        LiIon,
        LiPol,
        NiCd,
        NiMH
    };

    Battery();

 private:
    Manufacturer manufacturer;
    Type type;
    Capacity capacity;
    CellType cellType;
    Voltage voltage;
    Current maximalCurrent;
};

#endif // BATTERY_H
