#pragma once

//#include "TypeDevice.h"
#include "Data.h"
#include "Sensor.h"
#include "SystemControl.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

class IStrategy;
class IVisitor;
class IVisitorCollection;

class MainSystem
{
public:
	MainSystem(IStrategy* strategy, SystemSensor* sysSens, SystemControl* sysCtrl);
	void setStrategy(IStrategy* strategy);	// установить стратегию
	void solutionStrategy();				// воспользоваться стратегией

	string getMsg();

private:

	void temperatureUp();
	void temperatureDown();
	void lightOn();
	void lightOff();
	void humidityUp();
	void humidityDown();
	void wateringOn();
	void wateringOff();
	void valveCO2Open();
	void valveCO2Close();

	IStrategy* strategy;
	SystemSensor* sysSens;
	SystemControl* sysCtrl;

	IVisitor* visitorMeteoStation;
	string msg;
};

class IStrategy
{
public:
	virtual list<pair<TypeDevice, TypeStatus>> solution(
		DataClimat climat, DataClimat greenhouse) = 0;
	virtual string getType() = 0;
};

class NormalStrategy : public IStrategy
{
public:
	NormalStrategy(DataClimat threshold);
	list<pair<TypeDevice, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse);
	string getType();

private:
	DataClimat threshold;
	const int maxTemperature = 30;
};
class EcoStrategy : public IStrategy
{
public:
	EcoStrategy(DataClimat threshold);
	list<pair<TypeDevice, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse);
	string getType();

private:
	DataClimat threshold;
	const int maxTemperature = 30;
};
class MildStrategy : public IStrategy
{
public:
	//TODO:
	//MildStrategy();
	//list<pair<TypeDevice, TypeStatus>> solution(DataClimat dataClimat);
	//string getType();
};


class IVisitorCollection
{
public:
	virtual DataClimat accept(IVisitor* v) = 0;
};


class MeteoStation : public IVisitorCollection
{
public:
	MeteoStation(int a, float b, int c);
	DataClimat accept(IVisitor* v);
	void createData();
	map<TypeDevice, float> getData();

private:
	IVisitor* visitor;
	int a;
	float b;
	int c;
	map<TypeDevice, float> data;
};


class IVisitor
{
public:
	virtual DataClimat visit(MeteoStation* ms) = 0;
};


class ExportDataClimat : public IVisitor
{
public:
	DataClimat visit(MeteoStation* ms);
};

