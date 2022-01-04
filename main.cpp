#include <iostream>
#include <vector>

#include "System.h"
#include "MainSystem.h"

using namespace std;

void demoStrategy(IStrategy* strtg)
{
    cout << "__INIT__:" << endl;
    
    SystemDirector* dir;
    dir = SystemDirector::Instance();                               // создаем директора

    SystemControlBuilder* sysCtrlBuild = new SystemControlBuilder();// создаем билдера по созданию системы контроля климата
    SystemSensorBuilder* sysSensBuild = new SystemSensorBuilder();  // аналогично с датчиками климата

    dir->makeSystemControl(sysCtrlBuild);                           // передаем директору билдера    
    dir->makeSystemSensor(sysSensBuild);

    SystemControl* sysCtrl = sysCtrlBuild->getResult();             // Система контроля
    SystemSensor* sysSens = sysSensBuild->getResult();              // Система сенсоров
    
    MainSystem* mainSys = new MainSystem(strtg, sysSens, sysCtrl);  // собираем всю систему в одно

    cout << endl;
    cout << "__1__: " << strtg->getType() << endl;
    list<ISensor*> listSens = sysSens->getListSensor();             // получаем объекты-сенсоры, чтобы задать значение климата в теплице
    for (auto it = listSens.begin(); it != listSens.end(); it++)
    {
        if ((*it)->getType() == TypeDevice::TEMPERATURE)
            (*it)->setData(20);
        else if ((*it)->getType() == TypeDevice::LIGHT)
            (*it)->setData(50);
        else if ((*it)->getType() == TypeDevice::HUMIDITY)
            (*it)->setData(60);
        else if ((*it)->getType() == TypeDevice::SOILHUMIDITY)
            (*it)->setData(65);
        else if ((*it)->getType() == TypeDevice::CO2)
            (*it)->setData(15);
    }
    mainSys->solutionStrategy();                                    // используем стратегию

    cout << endl;
    cout << "__2__: " << strtg->getType() << endl;
    listSens = sysSens->getListSensor();                            // получаем объекты-сенсоры, чтобы задать значение климата в теплице
    for (auto it = listSens.begin(); it != listSens.end(); it++)
    {
        if ((*it)->getType() == TypeDevice::TEMPERATURE)
            (*it)->setData(10);
        else if ((*it)->getType() == TypeDevice::LIGHT)
            (*it)->setData(50);
        else if ((*it)->getType() == TypeDevice::HUMIDITY)
            (*it)->setData(10);
        else if ((*it)->getType() == TypeDevice::SOILHUMIDITY)
            (*it)->setData(65);
        else if ((*it)->getType() == TypeDevice::CO2)
            (*it)->setData(15);
    }
    mainSys->solutionStrategy();                                    // используем стратеги

    delete strtg;
    delete mainSys;
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
    //demoState();

    DataClimat threshold;                                           // задаем коэф. срабатывания для стратегии
    threshold.setData(TypeDevice::TEMPERATURE, 20);
    threshold.setData(TypeDevice::LIGHT, 50);
    threshold.setData(TypeDevice::CO2, 5);
    threshold.setData(TypeDevice::HUMIDITY, 30);
    threshold.setData(TypeDevice::SOILHUMIDITY, 30);

    IStrategy* strtgNrm = new NormalStrategy(threshold);            // создаем стратегию
    IStrategy* strtgEco = new EcoStrategy(threshold);               // создаем стратегию

    demoStrategy(strtgNrm);

    cout << endl << endl;

    demoStrategy(strtgEco);

    cout << endl << endl;


    return 0;
}
