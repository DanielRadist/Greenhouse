#include "SystemControl.h"

DeviceControlIterator::DeviceControlIterator(vector<DeviceControl*>* listDevice)
{
	this->listDevice = listDevice;
	currentDevice = 0;
}

void DeviceControlIterator::first()
{
	currentDevice = 0;
}

void DeviceControlIterator::next()
{
	currentDevice++;
}

bool DeviceControlIterator::hasNext()
{
	if (currentDevice + 1 == listDevice->size())
		return false;
	else
		return true;
}

DeviceControl* DeviceControlIterator::getCurrent()
{
	return (*listDevice)[currentDevice];
}

//for Factory method
void SystemControl::add(TypeDevice type)
{
	listDevice.push_back(new DeviceControl(type));
}
/*
void SystemControl::add(DeviceControl* Device)
{
	listDevice.push_back(Device);
}

void SystemControl::remove(DeviceControl* Device)
{
	//TODO:
}*/

void SystemControl::search(TypeDevice typeDevice)
{
}


Iterator* SystemControl::createIterator()
{
	return new DeviceControlIterator(&listDevice);
}
