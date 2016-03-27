#ifndef PROPELLER_H
#define PROPELLER_H

#include "cstdint"
#include "string"

class Propeller
{
 public:
    using Manufacturer = std::string;
    using Type = std::string;
    using Diameter = float;
    using Angle = float;
    enum class RotationalDirection : uint8_t {
        CW,
        CCW
    };

    Propeller();

 private:
    Manufacturer manufacturer;
    Type type;
    Diameter diameter;
    Angle bladeAngle;
    Diameter shaftDiameter;
    uint8_t bladeCount;
    RotationalDirection rotationalDirection;
};

#endif // PROPELLER_H
