#include "SystemControl.h"
#include <iostream>

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
	while (true)			// пока не прошли все эл-ты
	{
		if (iter->getCurrent()->getType() == typeDevice)
		{
			rtrn = iter->getCurrent();
			break;
		}

		if (iter->hasNext())
			iter->next();
		else
			break;
	}
	delete iter;
	return rtrn;
}


Iterator* SystemControl::createIterator()
{
	return new DeviceControlIterator(&listDevice);
}

void SystemControl::solution(list<pair<TypeDevice, TypeStatus>> solut)
{
	while (solut.size() != 0)
	{
		if (solut.front().second == TypeStatus::ON)
			std::cout << search(solut.front().first)->on();
		else
			std::cout << search(solut.front().first)->off();

		solut.pop_front();
	}
}
