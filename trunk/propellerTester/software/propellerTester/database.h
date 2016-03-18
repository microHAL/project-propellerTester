#ifndef DATABASE_H
#define DATABASE_H


#include <string>
#include <vector>

class Database
{
public:
    Database();

    class Propeller {
    public:
        std::vector<std::string> getAllManufacturers();
        bool findAllTypes(const std::string &manufacturer);
        bool getParameters(const std::string &manufacturer, const std::string &type);
    } propeller;

    class ESC {
    public:
    } esc;

    class Engine {
    public:
    } engine;
};

#endif // DATABASE_H
