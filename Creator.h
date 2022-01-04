#pragma once
#include "TypeDevice.h"
#include "System.h"


class ICreator
{
public:
	virtual ISystem* createSystem() = 0;
};

class SystemSensorCreator : public ICreator
{
public:
	SystemSensorCreator();

	ISystem* createSystem();
};

class SystemControlCreator : public ICreator
{
public:
	SystemControlCreator();

	ISystem* createSystem();
};

