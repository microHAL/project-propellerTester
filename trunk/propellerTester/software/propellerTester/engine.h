#ifndef ENGINE_H
#define ENGINE_H

#include <cstdint>
#include <string>

class Engine
{
 public:
    using Manufacturer = std::string;
    using Type = std::string;
    using Size = std::string;
    using RPMperVolt = float;
    using Power = float;

    Engine();
 private:
    Manufacturer manufacturer;
    Type type;
    Size size;
    RPMperVolt kV;
    Power power;
    std::string notes;
};

#endif // ENGINE_H
