#ifndef ESC_H
#define ESC_H

#include <cstdint>
#include <string>

class ESC
{
 public:
    using Manufacturer = std::string;
    using Type = std::string;
    using Current = float;
    using SoftwareType = std::string;
    using SoftwareVersion = std::string;

    ESC();

 private:
    Manufacturer manufacturer;
    Type type;
    Current maximalCurrent;
    SoftwareType softwareType;
    SoftwareVersion softwareVersion;
};

#endif // ESC_H
