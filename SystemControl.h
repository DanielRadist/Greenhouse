#pragma once
#include "DeviceControl.h"
#include "System.h"
#include <vector>

class Iterator
{
public:
	virtual void first() = 0;

	virtual void next() = 0;

	virtual bool hasNext() = 0;

	virtual DeviceControl* getCurrent() = 0;
};

class DeviceControlIterator : public Iterator
{
public:
	DeviceControlIterator(vector<DeviceControl*>* listDevice);

	void first();

	void next();

	bool hasNext();

	DeviceControl* getCurrent();

private:
	int currentDevice;		//index

	vector<DeviceControl*>* listDevice;
};

class IControlCollection
{
public:
	virtual Iterator* createIterator() = 0;
};

class SystemControl : public ISystem, public IControlCollection
{
public:
	//void add(DeviceControl* Device);

	//for Factory method
	void add(TypeDevice type);

	//void remove(DeviceControl* Device);

	void search(TypeDevice typeDevice);

	Iterator* createIterator();

private:
	vector<DeviceControl*> listDevice;
};

