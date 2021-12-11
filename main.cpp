﻿#include <iostream>
#include <vector>
#include "TypeDevice.h"
#include "Sensor.h"
#include "SystemControl.h"

using namespace std;

// Демонстрация делегата и адаптера для ControlWindow
void demoDelegat()
{
    //Connect light control
    DeviceControl* lightCtrl = new DeviceControl(TypeDevice::LIGHT);

    //Connect window control
    DeviceControl* winCtrl = new DeviceControl(TypeDevice::WINDOW);

    //Connect temperature control
    DeviceControl* tempCtrl = new DeviceControl(TypeDevice::TEMPERATURE);


    cout << lightCtrl->on() << endl;
    cout << lightCtrl->off() << endl;

    cout << winCtrl->on() << endl;
    cout << winCtrl->off() << endl;

    cout << tempCtrl->on() << endl;
    cout << tempCtrl->off() << endl;
}

// Демонстрация работы декоратора у контрллеров климата
void demoDecorator()
{
    //Connect window control
    DeviceControl* winCtrl = new DeviceControl(TypeDevice::WINDOW);

    //Connect Humidity and Decor (humCtrl /=> winCtrl)
    DeviceControl* humCtrl = new DeviceControl(TypeDevice::HUMIDITY, winCtrl);

    //Connect CO2 and Decor (humCtrl /=> winCtrl)
    DeviceControl* co2Ctrl = new DeviceControl(TypeDevice::CO2, winCtrl);

    cout << "1:" << endl;
    cout << winCtrl->on() << endl;
    cout << humCtrl->on() << endl;

    cout << "2:" << endl;
    cout << humCtrl->off() << endl;
    cout << humCtrl->on() << endl;
    cout << humCtrl->off() << endl;

    cout << "3:" << endl;
    cout << winCtrl->on() << endl;
    cout << co2Ctrl->on() << endl;
    cout << humCtrl->on() << endl;
}

// Демонстрация работы композиции на сенсорах климата 
void demoComposit()
{
    SystemSensor* SystemTmp = new SystemSensor();       // система датчиков температуры

    ISensor* tmpSnsr0 = new SensorTemperature();
    ISensor* tmpSnsr1 = new SensorTemperature();
    ISensor* tmpSnsr2 = new SensorTemperature();

    SystemTmp->add(tmpSnsr0);
    SystemTmp->add(tmpSnsr1);
    SystemTmp->add(tmpSnsr2);

    tmpSnsr0->setData(22);
    tmpSnsr1->setData(24);
    tmpSnsr2->setData(25);

    std::map<TypeDevice, float> data;
    SystemTmp->getData(data);

    cout << "1:" << endl;
    cout << "Average temperature: " << to_string(data[TypeDevice::TEMPERATURE]) << endl;

    ///////////////////////////////////////////

    SystemSensor* SystemMain = new SystemSensor();

    ISensor* humSnsr = new SensorHumidity();
    ISensor* lightSnsr = new SensorLight();
    humSnsr->setData(50);
    lightSnsr->setData(850);
    tmpSnsr0->setData(26);

    SystemMain->add(humSnsr);
    SystemMain->add(lightSnsr);
    SystemMain->add(SystemTmp);

    cout << "2:" << endl;
    data.clear();
    SystemMain->getData(data);

    cout << "Average temperature: " << to_string(data[TypeDevice::TEMPERATURE]) << endl;
    cout << "Average humidity: " << to_string(data[TypeDevice::HUMIDITY]) << endl;
    cout << "Average light: " << to_string(data[TypeDevice::LIGHT]) << endl;
}

// Демонстрация работы Итератора коллекции: DeviceControl
void demoIterator()
{
    cout << "1:" << endl;
    //Connect window control
    DeviceControl* winCtrl = new DeviceControl(TypeDevice::WINDOW);

    //Connect Humidity and Decor (humCtrl /=> winCtrl)
    DeviceControl* humCtrl = new DeviceControl(TypeDevice::HUMIDITY, winCtrl);

    //Connect CO2 and Decor (humCtrl /=> winCtrl)
    DeviceControl* co2Ctrl = new DeviceControl(TypeDevice::CO2, winCtrl);

    //Connect light control
    DeviceControl* lightCtrl = new DeviceControl(TypeDevice::LIGHT);

    //Create System Controls
    SystemControl* SystemMain = new SystemControl();

    SystemMain->add(winCtrl);
    SystemMain->add(humCtrl);
    SystemMain->add(co2Ctrl);
    SystemMain->add(lightCtrl);

    co2Ctrl->on();

    cout << "2:" << endl;
    //Task: on light, off CO2, on Hum.
    Iterator* iter = SystemMain->createIterator();
    while (true)     // пока не прошли все эл-ты
    {
        if (iter->getCurrent()->getType() == TypeDevice::LIGHT)
            cout << iter->getCurrent()->on() << endl;

        if (iter->getCurrent()->getType() == TypeDevice::CO2)
            cout << iter->getCurrent()->off() << endl;

        if (iter->getCurrent()->getType() == TypeDevice::HUMIDITY)
            cout << iter->getCurrent()->on() << endl;

        if (iter->hasNext())
            iter->next();
        else
            break;
    }
}

class IProFile
{
public:
    virtual string getData(int id) = 0;
};

class ProFile : public IProFile
{
public:
    ProFile()
    {
        cout << "Connect to DataBase! " << endl;
    }
    ~ProFile()
    {
        cout << "Disconnect to DataBase! " << endl;
    }

    string getData(int id)
    {
        switch (id)
        {
        case 1:
            return "Big Sunflower T:15-25, L:400-800\n";
        case 2:
            return "Coffee T:25-30, L:700-800\n";
        case 3:
            return "Salo T:0-10, L:100-500\n";
        default:
            return "Error!\n";
        }
    }

private:
    //source: dataBase
};

class ProxyProFile : public IProFile
{
public:
    ProxyProFile()
    {
        cout << "On cashe proxy! " << endl;
    }
    ~ProxyProFile()
    {
        cout << "Off cashe proxy! " << endl;
    }

    string getData(int id)
    {
        for (int i = 0; i < cashe.size(); i++)
        {
            if (cashe[i].first == id)
            {
                cout << "Found in cache! " << endl;
                return cashe[i].second;
            }
        }

        ProFile* file = new ProFile();
        string buf = file->getData(id);
        cashe.push_back(make_pair(id, buf));
        delete file;
        return buf;
    }


private:
    vector<pair<int, string>> cashe;
};

void demoProxy()
{
    IProFile* proxy = new ProxyProFile();

    cout << "Check Proxy" << endl;

    cout << proxy->getData(1);
    cout << proxy->getData(2);
    
    cout << endl;

    cout << proxy->getData(1);
    cout << proxy->getData(3);
    cout << proxy->getData(2);
}

int main()
{
    //demoDelegat();
    demoDecorator();
    
    cout << endl << endl;

    demoComposit();

    cout << endl << endl;

    demoIterator();

    //demoProxy();

    return 0;
}
