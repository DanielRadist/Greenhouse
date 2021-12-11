#include "Control.h"
#include "TypeDevice.h"

IControl::IControl(TypeDevice type)
{
    this->type = type;
    this->status = TypeStatus::OFF;
}

TypeDevice IControl::getType()
{
    return type;
}

TypeStatus IControl::getStatus()
{
    return status;
}



ControlLight::ControlLight() : IControl(TypeDevice::LIGHT)
{
}

string ControlLight::on()
{
    status = TypeStatus::ON;
    return "On Light! ";
}

string ControlLight::off()
{
    status = TypeStatus::OFF;
    return "Off Light! ";
}



ControlTemperature::ControlTemperature() : IControl(TypeDevice::TEMPERATURE)
{
}

string ControlTemperature::on()
{
    status = TypeStatus::ON;
    return "Upper Temperature! ";
}

string ControlTemperature::off()
{
    status = TypeStatus::OFF;
    return "Down Temperature! ";
}




AdapterControlWindow::AdapterControlWindow(ControlWindow* window) : IControl(TypeDevice::WINDOW)
{
    this->window = window;
}

string AdapterControlWindow::on()
{
    status = TypeStatus::ON;
    return string("Open Window! ") + "(" + window->openness(valueOpen) + ") ";
}

string AdapterControlWindow::off()
{
    status = TypeStatus::OFF;
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
