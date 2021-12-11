#pragma once
#include "TypeDevice.h"
#include <map>
#include <list>
#include <tuple>

class ISensor
{
public:
	ISensor(TypeDevice type);

	virtual int getData();

	virtual void getData(std::map<TypeDevice, std::pair<int, int>>& data);

	virtual void setData(int value);	// метод необходим для демонстрации работы

	virtual TypeDevice getType();

protected:
	int data;

	TypeDevice type;
};


class SystemSensor : public ISensor
{
public:
	SystemSensor();
	
	void add(ISensor* Sensor);
	
	void remove(ISensor* Sensor);

	void getData(std::map<TypeDevice, float>& data);

protected:

	void getData(std::map<TypeDevice, std::pair<int, int>>& data);

	std::list<ISensor*> listDevice;
};


class SensorLight : public ISensor
{
public:
	SensorLight();
};


class SensorTemperature : public ISensor
{
public:
	SensorTemperature();
};


class SensorHumidity : public ISensor
{
public:
	SensorHumidity();
};


class SensorCO2 : public ISensor
{
public:
	SensorCO2();
};
