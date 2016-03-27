#ifndef MEASUREMENTSETUP_H
#define MEASUREMENTSETUP_H

#include "propeller.h"
#include "engine.h"
#include "esc.h"
#include "battery.h"
#include "measurement.h"

class MeasurementSetup
{
public:
    Propeller propeller;
    Engine engine;
    ESC esc;
    Battery battery;

    Measurement measurement;

    MeasurementSetup();
};

#endif // MEASUREMENTSETUP_H
