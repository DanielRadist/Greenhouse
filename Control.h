#pragma once

#include "TypeDevice.h"
#include <string>

using namespace std;

class ControlWindow;

class IControl
{
protected:
    TypeDevice type;
    TypeStatus status;
public:

    IControl(TypeDevice type);

    virtual string on() = 0;
    virtual string off() = 0;

    TypeDevice getType();
    TypeStatus getStatus();
};

class ControlLight : public IControl
{
public:
    ControlLight();

    string on();
    string off();
};

class ControlTemperature : public IControl
{
public:
    ControlTemperature();

    string on();
    string off();
};

class ControlWindow
{
public:
    ControlWindow();

    string openness(int value);
};

// Ïðèìåð ÀÄÀÏÒÅÐ
class AdapterControlWindow : public IControl
{
protected:
    int valueOpen = 80;
    int valueClose = 0;

    ControlWindow* window;

public:
    AdapterControlWindow(ControlWindow* window);

    string on();
    string off();

    void setValueOpen(int value);
    void setValueClose(int value);
};


// Ïðèìåð ÄÅÊÎÐÀÒÎÐ
class IControlUnion : public IControl
{
protected:
    IControl* DecorControl;

    IControlUnion(IControl* Control, TypeDevice typeControl);
};

class ControlHumidity : public IControlUnion
{
public:
    ControlHumidity(IControl* Control);

    string on();
    string off();
};

class ControlCO2 : public IControlUnion
{
public:
    ControlCO2(IControl* Control);

    string on();
    string off();
};



