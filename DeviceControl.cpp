#include <iostream>
#include <string>

#include "DeviceControl.h"
#include "Control.h"

DeviceControl::DeviceControl(TypeDevice typeControl)
{
    switch (typeControl)
    {
    case TypeDevice::LIGHT:
        this->control = new ControlLight();
        std::cout << "Connect light control " << std::endl;
        break;

    case TypeDevice::TEMPERATURE:
        this->control = new ControlTemperature();
        std::cout << "Connect temperature control " << std::endl;
        break;

    case TypeDevice::WINDOW:
    {
        ControlWindow* window = new ControlWindow();            // объект класса контроллера окна
        this->control = new AdapterControlWindow(window);       // адаптер класса контроллера окна
        std::cout << "Connect window control " << std::endl;
        break;
    }

    //TODO: SoilHum

    default:
        this->control = nullptr;
        break;
    }
}

DeviceControl::DeviceControl(TypeDevice typeControl, DeviceControl* SubDevice)
{
    switch (typeControl)
    {
    case TypeDevice::HUMIDITY:
        this->control = new ControlHumidity(SubDevice->control);
        std::cout << "Connect humidity control " << std::endl;
        break;

    case TypeDevice::CO2:
        this->control = new ControlCO2(SubDevice->control);
        std::cout << "Connect CO2 control " << std::endl;
        break;
    }
}

string DeviceControl::on()
{
    if (getStatus() == TypeStatus::OFF)
        return control->on();
    else
        return "Attention! The device is already on! ";
}

string DeviceControl::off()
{
    if (getStatus() == TypeStatus::ON)
        return control->off();
    else
        return "Attention! The device is already off! ";
}

TypeDevice DeviceControl::getType()
{
    return control->getType();
}

TypeStatus DeviceControl::getStatus()
{
    return control->getStatus();
}

DeviceControl::~DeviceControl()
{
    delete control;
}