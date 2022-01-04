#include "Control.h"
#include "TypeDevice.h"

IControl::IControl(TypeDevice type)
{
    this->type = type;
}

TypeDevice IControl::getType()
{
    return type;
}

string IControl::getTypeToStr()
{
    switch (type)
    {
    case TypeDevice::TEMPERATURE:
        return "Heater ";
    case TypeDevice::LIGHT:
        return "Light ";
    case TypeDevice::HUMIDITY:
        return "Humidifier ";
    case TypeDevice::WINDOW:
        return "Window ";
    case TypeDevice::CO2:
        return "Valve CO2 ";
    case TypeDevice::SOILHUMIDITY:
        return "Valve water ";
    default:
        break;
    }
    return string();
}



ControlLight::ControlLight() : IControl(TypeDevice::LIGHT)
{
}

string ControlLight::on()
{
    return "On Light! ";
}

string ControlLight::off()
{
    return "Off Light! ";
}



ControlTemperature::ControlTemperature() : IControl(TypeDevice::TEMPERATURE)
{
}

string ControlTemperature::on()
{
    return "Heater On! ";
}

string ControlTemperature::off()
{
    return "Heater Off! ";
}




AdapterControlWindow::AdapterControlWindow(ControlWindow* window) : IControl(TypeDevice::WINDOW)
{
    this->window = window;
}

string AdapterControlWindow::on()
{
    return string("Open Window! ") + "(" + window->openness(valueOpen) + ") ";
}

string AdapterControlWindow::off()
{
    return string("Close Window! ") + "(" + window->openness(valueClose) + ") ";
}

void AdapterControlWindow::setValueOpen(int value)
{
    valueOpen = value;
}

void AdapterControlWindow::setValueClose(int value)
{
    valueClose = value;
}



ControlWindow::ControlWindow()
{
}

string ControlWindow::openness(int value)
{
    return string("openness: " + to_string(value) + "%");
}


/*
IControlUnion::IControlUnion(IControl* Control, TypeDevice typeControl) : IControl(typeControl)
{
    this->DecorControl = Control;
}



ControlHumidity::ControlHumidity(IControl* Control) : IControlUnion(Control, TypeDevice::HUMIDITY)
{
}

string ControlHumidity::on()
{
    status = TypeStatus::ON;
    if (DecorControl->getStatus() == TypeStatus::ON)
        return string("Humidifier on! ") + DecorControl->off() + " ";
    else
        return string("Humidifier on! ");
}

string ControlHumidity::off()
{
    status = TypeStatus::OFF;
    return string("Humidifier off! ");
}



ControlCO2::ControlCO2(IControl* Control) : IControlUnion(Control, TypeDevice::CO2)
{
}

string ControlCO2::on()
{
    status = TypeStatus::ON;
    if (DecorControl->getStatus() == TypeStatus::ON)
        return string("CO2 valve open! ") + DecorControl->off() + " ";
    else
        return string("CO2 valve open! ");
}

string ControlCO2::off()
{
    status = TypeStatus::OFF;
    return string("CO2 valve close! ");
}
*/

ControlHumidity::ControlHumidity() : IControl(TypeDevice::HUMIDITY)
{
}

string ControlHumidity::on()
{
    return "Humidifier On! ";
}

string ControlHumidity::off()
{
    return "Humidifier Off! ";
}

ControlCO2::ControlCO2() : IControl(TypeDevice::CO2)
{
}

string ControlCO2::on()
{
    return "Valve CO2 Open! ";
}

string ControlCO2::off()
{
    return "Valve CO2 Close! ";
}

ControlSoilHumidity::ControlSoilHumidity() : IControl(TypeDevice::SOILHUMIDITY)
{
}

string ControlSoilHumidity::on()
{
    return "Valve water Open! ";
}

string ControlSoilHumidity::off()
{
    return "Valve water Close! ";
}
