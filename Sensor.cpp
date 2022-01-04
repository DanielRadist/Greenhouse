#include "Sensor.h"

ISensor::ISensor(TypeDevice type)
{
	this->type = type;
	this->data = INT_FAST32_MIN;
}

int ISensor::getData()
{
	return data;
}

void ISensor::getData(std::map<TypeDevice, std::pair<int, int>>& data)
{
	//»щем встречалс€ ли в map текущий тип датчика
	auto iter = data.find(getType());

	//если уже есть в коллекции
	if (iter != data.end())
	{
		(*iter).second.first += getData();
		(*iter).second.second++;
	}
	//еще нет в коллекции
	else
	{
		data.insert(std::make_pair(
			getType(),
			std::make_pair(
				getData(),
				1)));
	}
}

void ISensor::setData(int value)
{
	this->data = value;
}

TypeDevice ISensor::getType()
{
	return type;
}


SystemSensor::SystemSensor() : ISensor(TypeDevice::SYSTEM)
{
}

void SystemSensor::add(ISensor* Sensor)
{
	listDevice.push_back(Sensor);
}

void SystemSensor::remove(ISensor* Sensor)
{
	//TODO::
}

DataClimat SystemSensor::getDataClimat()
{
	std::map<TypeDevice, float> data;

	getData(data);

	return new DataClimat(data);
}

void SystemSensor::getData(std::map<TypeDevice, float>& data)
{
	std::map<TypeDevice, std::pair<int, int>> buffData;
	getData(buffData);
	for (auto it = buffData.begin(); it != buffData.end(); it++)
	{
		data.insert(std::make_pair(
			(*it).first,
			(float((*it).second.first) / (*it).second.second)
		));
	}
}

void SystemSensor::setData(int value)
{
	for (auto it = listDevice.begin(); it != listDevice.end(); it++)
		(*it)->setData(value--);
}

std::list<ISensor*> SystemSensor::getListSensor()
{
	return listDevice;
}

void SystemSensor::getData(std::map<TypeDevice, std::pair<int, int>>& data)
{
	//first - key, second.first - Total value, second.second - count value
	//std::map<TypeDevice, std::pair<int, int>> data;

	for (auto it = listDevice.begin(); it != listDevice.end(); it++)
	{
		(*it)->getData(data);
	}
}


SensorLight::SensorLight() : ISensor(TypeDevice::LIGHT)
{
}

SensorTemperature::SensorTemperature() : ISensor(TypeDevice::TEMPERATURE)
{
}

SensorHumidity::SensorHumidity() : ISensor(TypeDevice::HUMIDITY)
{
}

SensorCO2::SensorCO2() : ISensor(TypeDevice::CO2)
{
}
