#pragma once
#include <vector>

#include "Sensor.h"
#include "SystemControl.h"


class SystemBuilder
{
public:

	virtual void makeTemperature(int count) = 0;
	virtual void makeHumidity(int count) = 0;
	virtual void makeCO2(int count) = 0;
	virtual void makeSoilHumidity(int count, std::vector<int> numbersSoil) = 0;
	virtual void makeLight(int count) = 0;
	virtual void makeWindow(int count) = 0;
};

class SystemSensorBuilder : public SystemBuilder
{
public:
	SystemSensorBuilder();

	void makeTemperature(int count);
	void makeHumidity(int count);
	void makeCO2(int count);
	void makeSoilHumidity(int count, std::vector<int> numbersSoil);
	void makeLight(int count);
	void makeWindow(int count);

	SystemSensor* getResult();

	vector<ISensor*> sensors;

private:

	SystemSensor* sysSens;
};

class SystemControlBuilder : public SystemBuilder
{
public:
	SystemControlBuilder();

	void makeTemperature(int count);
	void makeHumidity(int count);
	void makeCO2(int count);
	void makeSoilHumidity(int count, std::vector<int> numbersSoil);
	void makeLight(int count);
	void makeWindow(int count);

	SystemControl* getResult();

private:

	void makeControl(TypeDevice type, int count);

	SystemControl* sysCtrl;
};

class SystemDirector
{
public:
	SystemDirector();

	static SystemDirector* Instance();

	void makeSystemSensor(SystemBuilder* builder);

	void makeSystemControl(SystemBuilder* builder);

private:
	static SystemDirector* _instance;
};


