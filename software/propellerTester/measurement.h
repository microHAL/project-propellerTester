#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include <vector>
#include <QVector>

class Measurement
{
public:
    Measurement();

//private:
    std::vector<int> time;
    std::vector<double> current;
    std::vector<double> voltage;
    QVector<double> thrust;
    std::vector<double> vibration;
};

#endif // MEASUREMENT_H
