#pragma once

#include "Control.h"

class DeviceControl
{
public:
    DeviceControl(TypeDevice typeControl);

    DeviceControl(TypeDevice typeControl, DeviceControl* SubDevice);

    string on();

    string off();

    TypeDevice getType();

    TypeStatus getStatus();

    ~DeviceControl();

private:
    IControl* control;
};

