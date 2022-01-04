#include "MainSystem.h"

#include <random>

MainSystem::MainSystem(IStrategy* strategy, SystemSensor* sysSens, SystemControl* sysCtrl)
{
	this->strategy = strategy;
	this->sysSens = sysSens;
	this->sysCtrl = sysCtrl;
}

void MainSystem::setStrategy(IStrategy* strategy)
{
	this->strategy = strategy;
}

void MainSystem::solutionStrategy()
{
	visitorMeteoStation = new ExportDataClimat();					// создаем посетителя
	MeteoStation* connectToMS = new MeteoStation(1, 1.0, 1);		// подключение к метеостанции
	connectToMS->createData();
	DataClimat climat = connectToMS->accept(visitorMeteoStation);	// отправляем за данными о климате на улице

	delete visitorMeteoStation;
	delete connectToMS;

	DataClimat greenhouse = sysSens->getDataClimat();				// данные о климате в теплице

	// Получение решения
	list<pair<TypeDevice, TypeStatus>> solut = strategy->solution(climat, greenhouse);

	sysCtrl->solution(solut);
}

string MainSystem::getMsg()
{
	string buf = "";
	buf += msg;
	msg = "";
	return buf;
}

void MainSystem::temperatureUp()
{
	if (sysCtrl->search(TypeDevice::TEMPERATURE)->getStatus() != TypeStatus::ON)
		msg += sysCtrl->search(TypeDevice::TEMPERATURE)->on() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::TEMPERATURE)->getStatusToStr() + '\n';
}

void MainSystem::temperatureDown()
{
	if (sysCtrl->search(TypeDevice::TEMPERATURE)->getStatus() != TypeStatus::OFF)
		msg += sysCtrl->search(TypeDevice::TEMPERATURE)->off() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::TEMPERATURE)->getStatusToStr() + '\n';
}

void MainSystem::lightOn()
{
	if (sysCtrl->search(TypeDevice::LIGHT)->getStatus() != TypeStatus::ON)
		msg += sysCtrl->search(TypeDevice::LIGHT)->on() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::LIGHT)->getStatusToStr() + '\n';
}

void MainSystem::lightOff()
{
	if (sysCtrl->search(TypeDevice::LIGHT)->getStatus() != TypeStatus::OFF)
		msg += sysCtrl->search(TypeDevice::LIGHT)->off() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::LIGHT)->getStatusToStr() + '\n';
}

void MainSystem::humidityUp()
{
	if (sysCtrl->search(TypeDevice::HUMIDITY)->getStatus() != TypeStatus::ON)
		msg += sysCtrl->search(TypeDevice::HUMIDITY)->on() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::HUMIDITY)->getStatusToStr() + '\n';
}

void MainSystem::humidityDown()
{
	if (sysCtrl->search(TypeDevice::HUMIDITY)->getStatus() != TypeStatus::OFF)
		msg += sysCtrl->search(TypeDevice::HUMIDITY)->off() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::HUMIDITY)->getStatusToStr() + '\n';
}

void MainSystem::wateringOn()
{
	if (sysCtrl->search(TypeDevice::SOILHUMIDITY)->getStatus() != TypeStatus::ON)
		msg += sysCtrl->search(TypeDevice::SOILHUMIDITY)->on() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::SOILHUMIDITY)->getStatusToStr() + '\n';
}

void MainSystem::wateringOff()
{
	if (sysCtrl->search(TypeDevice::SOILHUMIDITY)->getStatus() != TypeStatus::OFF)
		msg += sysCtrl->search(TypeDevice::SOILHUMIDITY)->off() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::SOILHUMIDITY)->getStatusToStr() + '\n';
}

void MainSystem::valveCO2Open()
{
	if (sysCtrl->search(TypeDevice::CO2)->getStatus() != TypeStatus::ON)
		msg += sysCtrl->search(TypeDevice::CO2)->on() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::CO2)->getStatusToStr() + '\n';
}

void MainSystem::valveCO2Close()
{
	if (sysCtrl->search(TypeDevice::CO2)->getStatus() != TypeStatus::OFF)
		msg += sysCtrl->search(TypeDevice::CO2)->off() + '\n';
	else
		msg += sysCtrl->search(TypeDevice::CO2)->getStatusToStr() + '\n';
}

NormalStrategy::NormalStrategy(DataClimat threshold)
{
	this->threshold = threshold;
}

list<pair<TypeDevice, TypeStatus>> NormalStrategy::solution(DataClimat climat, DataClimat greenhouse)
{
	list<pair<TypeDevice, TypeStatus>> solut;

	// Температура в теплице ниже минимальной
	if (greenhouse.getData(TypeDevice::TEMPERATURE) < threshold.getData(TypeDevice::TEMPERATURE))
		solut.push_back(make_pair(TypeDevice::TEMPERATURE, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::TEMPERATURE, TypeStatus::OFF));

	// Влажность в теплице ниже минимальной
	if (greenhouse.getData(TypeDevice::HUMIDITY) < threshold.getData(TypeDevice::HUMIDITY))
		solut.push_back(make_pair(TypeDevice::HUMIDITY, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::HUMIDITY, TypeStatus::OFF));

	// Влажность почвы в теплице ниже минимальной
	if (greenhouse.getData(TypeDevice::SOILHUMIDITY) < threshold.getData(TypeDevice::SOILHUMIDITY))
		solut.push_back(make_pair(TypeDevice::SOILHUMIDITY, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::SOILHUMIDITY, TypeStatus::OFF));

	// Недостаток СО2
	if (greenhouse.getData(TypeDevice::CO2) < threshold.getData(TypeDevice::CO2))
		solut.push_back(make_pair(TypeDevice::CO2, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::CO2, TypeStatus::OFF));

	// Солнце село за горизонт
	if (greenhouse.getData(TypeDevice::LIGHT) < threshold.getData(TypeDevice::LIGHT))
		solut.push_back(make_pair(TypeDevice::LIGHT, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::LIGHT, TypeStatus::OFF));

	// Окно всегда загрыто при этой стратегии, кроме случая, когда температура выше макисмума
	if (greenhouse.getData(TypeDevice::TEMPERATURE) > maxTemperature)
		solut.push_back(make_pair(TypeDevice::WINDOW, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::WINDOW, TypeStatus::OFF));

	return solut;
}

string NormalStrategy::getType()
{
	return "Normal Strategy ";
}

DataClimat ExportDataClimat::visit(MeteoStation* ms)
{
	map<TypeDevice, float> data = ms->getData();
	return DataClimat(data);
}

EcoStrategy::EcoStrategy(DataClimat threshold)
{
	this->threshold = threshold;
}

list<pair<TypeDevice, TypeStatus>> EcoStrategy::solution(DataClimat climat, DataClimat greenhouse)
{
	list<pair<TypeDevice, TypeStatus>> solut;

	bool winFlag = false;

	// Температура выше максимальной
	if (greenhouse.getData(TypeDevice::TEMPERATURE) > maxTemperature)
		solut.push_back(make_pair(TypeDevice::WINDOW, TypeStatus::ON));
	// Температура в теплице ниже минимальной
	else if (greenhouse.getData(TypeDevice::TEMPERATURE) < threshold.getData(TypeDevice::TEMPERATURE))
	{
		// если на улице теплее, иначе только печка
		if (climat.getData(TypeDevice::TEMPERATURE) > greenhouse.getData(TypeDevice::TEMPERATURE))
			solut.push_back(make_pair(TypeDevice::WINDOW, TypeStatus::ON));
		else
			solut.push_back(make_pair(TypeDevice::TEMPERATURE, TypeStatus::ON));
	}
	else
		solut.push_back(make_pair(TypeDevice::TEMPERATURE, TypeStatus::OFF));

	// Влажность в теплице не регулируем в данной стратегии
	solut.push_back(make_pair(TypeDevice::HUMIDITY, TypeStatus::OFF));

	// Влажность почвы в теплице ниже минимальной
	if (greenhouse.getData(TypeDevice::SOILHUMIDITY) < threshold.getData(TypeDevice::SOILHUMIDITY))
		solut.push_back(make_pair(TypeDevice::SOILHUMIDITY, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeDevice::SOILHUMIDITY, TypeStatus::OFF));

	// Недостаток СО2 не регулируем в данной стратегии
	solut.push_back(make_pair(TypeDevice::CO2, TypeStatus::OFF));

	// Солнце село за горизонт не регулируем в данной стратегии
	solut.push_back(make_pair(TypeDevice::LIGHT, TypeStatus::OFF));

	return solut;
}

string EcoStrategy::getType()
{
	return "Eco Strategy ";
}

MeteoStation::MeteoStation(int a, float b, int c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

DataClimat MeteoStation::accept(IVisitor* v)
{
	return v->visit(this);
}

void MeteoStation::createData()
{
	std::random_device random_device;			// Источник энтропии.
	std::mt19937 generator(random_device());	// Генератор случайных чисел.
												// (Здесь берется одно инициализирующее значение, можно брать больше)

	// Температура
	std::uniform_int_distribution<> distributionTemp(10, 35); // Равномерное распределение [10, 35]
	data.insert({ TypeDevice::TEMPERATURE, distributionTemp(generator) });

	// Свет
	std::uniform_int_distribution<> distributionL(40, 60);
	data.insert({ TypeDevice::LIGHT, distributionL(generator) });

	data.insert({ TypeDevice::CO2, 20 });
	data.insert({ TypeDevice::SOILHUMIDITY, 20 });
	data.insert({ TypeDevice::HUMIDITY, 40 });
}

map<TypeDevice, float> MeteoStation::getData()
{
	return data;
}


