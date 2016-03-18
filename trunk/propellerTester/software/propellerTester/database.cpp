#include "database.h"

Database::Database()
{

}


std::vector<std::string> Database::Propeller::getAllManufacturers() {
    std::vector<std::string> manufacturers;

    manufacturers.push_back(std::string("Unknown"));
    manufacturers.push_back(std::string("GWS"));

    return manufacturers;
}

bool Database::Propeller::findAllTypes(const std::string &manufacturer) {
    if (manufacturer == "Unknown") {
        return false;
    }
    return true;
}

bool Database::Propeller::getParameters(const std::string &manufacturer, const std::string &type) {

}

