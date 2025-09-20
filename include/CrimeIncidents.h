#ifndef __CRIME_INCIDENTS_H__
#define __CRIME_INCIDENTS_H__

#include <iostream>
#include <fstream>
#include <iostream>
#include <memory>
#include "Data.h"

class CrimeIncidents
{
public:
    CrimeIncidents(std::string file_name);
    ~CrimeIncidents();

    void say_hello(){
        std::cout << "Hello, from crime-analysis!\n";
    }

    void LoadJsonFile(const std::string file_name);

    Json::Value getData()
    {
        return data;
    }
    void SetCollection();


    std::unique_ptr<DataCollection> collection;
private:
    Json::Value data;
    std::ifstream file_stream;
    std::string file_path;

};

#endif  //__CRIME_INCIDENTS_H__