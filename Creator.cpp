#include "Creator.h"

#include "Sensor.h"
#include "SystemControl.h"
#include <iostream>

SystemSensorCreator::SystemSensorCreator()
{
    std::cout << "Create SystemSensorCreator" << endl;
}

ISystem* SystemSensorCreator::createSystem()
{
    ISystem* sysSens = new SystemSensor();
    std::cout << "Create SystemSensor" << endl;
    sysSens->add(TypeDevice::TEMPERATURE);
    sysSens->add(TypeDevice::LIGHT);
    sysSens->add(TypeDevice::CO2);
    sysSens->add(TypeDevice::HUMIDITY);

    return sysSens;
}

SystemControlCreator::SystemControlCreator()
{
    std::cout << "Create SystemControlCreator" << endl;
}

ISystem* SystemControlCreator::createSystem()
{
    ISystem* sysCtrl = new SystemControl();
    std::cout << "Create SystemControl" << endl;
    sysCtrl->add(TypeDevice::TEMPERATURE);
    sysCtrl->add(TypeDevice::LIGHT);
    sysCtrl->add(TypeDevice::WINDOW);

    return sysCtrl;
}
