#pragma once

#include "Control.h"
#include "TypeDevice.h"

class IState
{
public:
    virtual string on() = 0;
    virtual string off() = 0;
    virtual TypeStatus get() = 0;
};

class ONState : public IState
{
public:
    ONState(IControl* control);

    string on();
    string off();
    TypeStatus get();

private:
    IControl* control;
};

class OFFState : public IState
{
public:
    OFFState(IControl* control);

    string on();
    string off();
    TypeStatus get();

private:
    IControl* control;
};

class DeviceControl
{
public:
    DeviceControl(TypeDevice typeControl);

    //DeviceControl(TypeDevice typeControl, DeviceControl* SubDevice);

    string on();

    string off();

    TypeDevice getType();

    TypeStatus getStatus();
    string getStatusToStr();

    ~DeviceControl();

private:
    IControl* control;
    IState* state;
};

