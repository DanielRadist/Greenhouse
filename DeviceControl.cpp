#include <iostream>
#include <string>

#include "DeviceControl.h"
#include "Control.h"


ONState::ONState(IControl* control)
{
    this->control = control;
}

string ONState::on()
{
    return string("Error! is On ") + control->getTypeToStr();
}

string ONState::off()
{
    return string("Device control - Off: ") + control->off();
}

TypeStatus ONState::get()
{
    return TypeStatus::ON;
}


OFFState::OFFState(IControl* control)
{
    this->control = control;
}

string OFFState::on()
{
    return string("Device control - On: ") + control->on();
}

string OFFState::off()
{
    return string("Error! is Off: ") + control->getTypeToStr();
}

TypeStatus OFFState::get()
{
    return TypeStatus::OFF;
}


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

    case TypeDevice::HUMIDITY:
        this->control = new ControlHumidity();
        std::cout << "Connect humidity control " << std::endl;
        break;

    case TypeDevice::SOILHUMIDITY:
        this->control = new ControlSoilHumidity();
        std::cout << "Connect soil humidity control " << std::endl;
        break;

    case TypeDevice::CO2:
        this->control = new ControlCO2();
        std::cout << "Connect CO2 control " << std::endl;
        break;


    case TypeDevice::WINDOW:
    {
        ControlWindow* window = new ControlWindow();            // объект класса контроллера окна
        this->control = new AdapterControlWindow(window);       // адаптер класса контроллера окна
        std::cout << "Connect window control " << std::endl;
        break;
    }


    default:
        this->control = nullptr;
        break;
    }

    state = new OFFState(control);                              // изначально выключен
}

/*
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
}*/

string DeviceControl::on()
{
    string msg = "";
    if (state->get() == TypeStatus::ON)
    {
        msg += string(getStatusToStr());
    }
    else
    {
        msg += string(state->on());
        delete state;
        state = new ONState(control);
    }
    return msg + '\n';
}

string DeviceControl::off()
{
    string msg = "";
    if (state->get() == TypeStatus::OFF)
    {
        msg += string(getStatusToStr());
    }
    else
    {
        msg += string(state->off());
        delete state;
        state = new OFFState(control);
    }
    return msg + '\n';
}

TypeDevice DeviceControl::getType()
{
    return control->getType();
}

TypeStatus DeviceControl::getStatus()
{
    return state->get();
}

string DeviceControl::getStatusToStr()
{
    if (state->get() == TypeStatus::ON)
        return control->getTypeToStr() + "On ";
    else
        return control->getTypeToStr() + "Off ";
}

DeviceControl::~DeviceControl()
{
    delete control;
}


