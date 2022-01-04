#include "System.h"
#include <iostream>

SystemSensorBuilder::SystemSensorBuilder()
{
	sysSens = new SystemSensor();
}

void SystemSensorBuilder::makeTemperature(int count)
{
	if (count < 1)
		return;
	else if (count == 1)
	{
		// создаем 1 экз. класса 
		sysSens->add(new SensorTemperature());
		cout << "Create SensorTemperature" << endl;
	}
	else if (count > 1)
	{
		// создаем ветвь в дереве из несколькил однотипных датчиков
		SystemSensor* tmp = new SystemSensor();

		for (int i = 0; i < count; i++)
		{
			tmp->add(new SensorTemperature());
			cout << "Create SensorTemperature" << endl;
		}

		sysSens->add(tmp);
	}
	return;		//Error
}

void SystemSensorBuilder::makeHumidity(int count)
{
	if (count < 1)
		return;
	else if (count == 1)
	{
		// создаем 1 экз. класса 
		sysSens->add(new SensorHumidity());
		cout << "Create SensorHumidity" << endl;
	}
	else if (count > 1)
	{
		// создаем ветвь в дереве из несколькил однотипных датчиков
		SystemSensor* tmp = new SystemSensor();

		for (int i = 0; i < count; i++)
		{
			tmp->add(new SensorHumidity());
			cout << "Create SensorHumidity" << endl;
		}

		sysSens->add(tmp);
	}
	return;		//Error
}

void SystemSensorBuilder::makeCO2(int count)
{
	if (count < 1)
		return;
	else if (count == 1)
	{
		// создаем 1 экз. класса 
		sysSens->add(new SensorCO2());
		cout << "Create SensorCO2" << endl;
	}
	else if (count > 1)
	{
		// создаем ветвь в дереве из несколькил однотипных датчиков
		SystemSensor* tmp = new SystemSensor();

		for (int i = 0; i < count; i++)
		{
			tmp->add(new SensorCO2());
			cout << "Create SensorCO2" << endl;
		}

		sysSens->add(tmp);
	}
	return;		//Error
}

void SystemSensorBuilder::makeSoilHumidity(int count)
{
	// TODO:
}

void SystemSensorBuilder::makeLight(int count)
{
	if (count < 1)
		return;
	else if (count == 1)
	{
		// создаем 1 экз. класса 
		sysSens->add(new SensorLight());
		cout << "Create SensorLight" << endl;
	}
	else if (count > 1)
	{
		// создаем ветвь в дереве из несколькил однотипных датчиков
		SystemSensor* tmp = new SystemSensor();

		for (int i = 0; i < count; i++)
		{
			tmp->add(new SensorLight());
			cout << "Create SensorLight" << endl;
		}

		sysSens->add(tmp);
	}
	return;		//Error
}

void SystemSensorBuilder::makeWindow(int count)
{
}

SystemSensor* SystemSensorBuilder::getResult()
{
	return sysSens;
}



SystemControlBuilder::SystemControlBuilder()
{
	sysCtrl = new SystemControl();
}

void SystemControlBuilder::makeTemperature(int count)
{
	makeControl(TypeDevice::TEMPERATURE, count);
}

void SystemControlBuilder::makeHumidity(int count)
{
	makeControl(TypeDevice::HUMIDITY, count);
}

void SystemControlBuilder::makeCO2(int count)
{
	makeControl(TypeDevice::CO2, count);
}

void SystemControlBuilder::makeSoilHumidity(int count)
{
	makeControl(TypeDevice::SOILHUMIDITY, count);
}

void SystemControlBuilder::makeLight(int count)
{
	makeControl(TypeDevice::LIGHT, count);
}

void SystemControlBuilder::makeWindow(int count)
{
	makeControl(TypeDevice::WINDOW, count);
}

SystemControl* SystemControlBuilder::getResult()
{
	return sysCtrl;
}

void SystemControlBuilder::makeControl(TypeDevice type, int count)
{
	for (int i = 0; i < count; i++)
	{
		sysCtrl->add(new DeviceControl(type));
	}
}



SystemDirector::SystemDirector()
{
	std::cout << "Create Director-Builder" << endl;
}

SystemDirector* SystemDirector::Instance()
{
	if (_instance == nullptr)
		_instance = new SystemDirector();
	else
		cout << "Call the Director-Builder" << endl;
	return _instance;
}

void SystemDirector::makeSystemSensor(SystemBuilder* builder)
{
	builder->makeTemperature(3);
	builder->makeLight(1);
	builder->makeHumidity(1);
	builder->makeCO2(2);
}

void SystemDirector::makeSystemControl(SystemBuilder* builder)
{
	builder->makeTemperature(1);
	builder->makeLight(1);
	builder->makeHumidity(1);
	builder->makeSoilHumidity(1);
	builder->makeCO2(1);
	builder->makeWindow(1);
}

SystemDirector* SystemDirector::_instance = nullptr;
