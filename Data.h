#pragma once
#include "TypeDevice.h"
#include <map>

class DataClimat;

class Prototype
{
public:
	virtual DataClimat clone() = 0;
};

class DataClimat : public Prototype
{
public:

	DataClimat clone()
	{
		return (new DataClimat(this));
	}

	DataClimat(DataClimat* data)
	{
		this->temperature = data->temperature;
		this->co2 = data->co2;
		this->light = data->light;
		this->humidity = data->humidity;
	}

	DataClimat(std::map<TypeDevice, float> data)
	{
		this->temperature = data[TypeDevice::TEMPERATURE];
		this->co2 = data[TypeDevice::CO2];
		this->light = data[TypeDevice::LIGHT];
		this->humidity = data[TypeDevice::HUMIDITY];
	}

	DataClimat()
	{
		this->temperature = -1;
		this->co2 = -1;
		this->light = -1;
		this->humidity = -1;
	}

	int getData(TypeDevice type)
	{
		switch (type)
		{
		case TypeDevice::TEMPERATURE:
			return temperature;
		case TypeDevice::LIGHT:
			return light;
		case TypeDevice::HUMIDITY:
			return humidity;
		case TypeDevice::CO2:
			return co2;
		default:
			return -2;
		}
	}

private:

	int temperature;
	int light;
	int co2;
	int humidity;
};