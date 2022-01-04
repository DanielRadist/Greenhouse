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
		this->soilHumidity = data->soilHumidity;
	}

	DataClimat(std::map<TypeDevice, float> data)
	{
		this->temperature = data[TypeDevice::TEMPERATURE];
		this->co2 = data[TypeDevice::CO2];
		this->light = data[TypeDevice::LIGHT];
		this->humidity = data[TypeDevice::HUMIDITY];
		this->soilHumidity = data[TypeDevice::SOILHUMIDITY];
	}

	DataClimat()
	{
		this->temperature = -1;
		this->co2 = -1;
		this->light = -1;
		this->humidity = -1;
		this->soilHumidity = -1;
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
		case TypeDevice::SOILHUMIDITY:
			return soilHumidity;
		default:
			return -2;
		}
	}

	void setData(TypeDevice type, int value)
	{
		switch (type)
		{
		case TypeDevice::TEMPERATURE:
			temperature = value;
		case TypeDevice::LIGHT:
			light = value;
		case TypeDevice::HUMIDITY:
			humidity = value;
		case TypeDevice::CO2:
			co2 = value;
		case TypeDevice::SOILHUMIDITY:
			soilHumidity = value;
		default:
			return;
		}
	}

private:

	int temperature;
	int light;
	int co2;
	int humidity;
	int soilHumidity;
};