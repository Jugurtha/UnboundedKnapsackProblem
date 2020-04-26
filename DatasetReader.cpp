//
// Created by CHAKER Jugurtha on 26/04/2020.
//

#include "DatasetReader.h"

DatasetReader::DatasetReader(const std::string &path) : path(path), infile(path) {}


Instance DatasetReader::getInstance()
{
    Instance instance;
    std::string sink;
    std::string line;
    std::getline(infile, line);//##
    std::getline(infile, line);//##EDUK...
    std::getline(infile, line);//blanc

    //n
    std::getline(infile, line);
    std::istringstream iss(line);
    int n;
    iss >> sink >> n;
//    std::cout << sink << " " << n << "\n";

    std::getline(infile, line);//blanc

    //c
    std::getline(infile, line);
    std::istringstream iss2(line);
    int c;
    iss2 >> sink >> c;
    instance.maxWeight = c;
//    std::cout << sink << " " << c << "\n";

    std::getline(infile, line);//blanc
    std::getline(infile, line);//begin data
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int weight, value;
        if (!(iss >> weight >> value)) { break; } // error
        instance.objects.push_back({weight,value});
        // process pair (a,b)
    }
/*    for(auto e : instance.objects)
        std::cout << "Weight : " << e.weight << ", Value : "<< e.value << "\n";
*/    return instance;
}

DatasetReader::~DatasetReader() {
    infile.close();
}
