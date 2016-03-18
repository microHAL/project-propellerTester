#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include <vector>
#include <QVector>

class Propeller {
public:
    std::string type;
    unsigned int numberOfBlades;
};

class Measurement
{
public:
    Measurement();

//private:
    std::string engineType;
    std::string ECStype;
    Propeller propeller;
    std::vector<int> time;
    std::vector<double> current;
    std::vector<double> voltage;
    QVector<double> thrust;
    std::vector<double> vibration;
};

#endif // MEASUREMENT_H
