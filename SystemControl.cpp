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


void SystemControl::add(DeviceControl* Device)
{
	listDevice.push_back(Device);
}

void SystemControl::remove(DeviceControl* Device)
{
	//TODO:
}

DeviceControl* SystemControl::search(TypeDevice typeDevice)
{
	Iterator* iter = createIterator();
	DeviceControl* rtrn = nullptr;
	while (iter->hasNext())			// пока не прошли все эл-ты
	{
		if (iter->getCurrent()->getType() == typeDevice)
		{
			rtrn = iter->getCurrent();
			break;
		}

		if (iter->hasNext())
			iter->next();
	}
	delete iter;
	return rtrn;
}


Iterator* SystemControl::createIterator()
{
	return new DeviceControlIterator(&listDevice);
}
