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


Result DatasetReader::getOptimalResult() {
    std::string line;
    Result result;
    infile.clear();
    infile.seekg(0);
    while (std::getline(infile, line) && line.rfind("end", 0) != 0);

    std::getline(infile, line);//3 superfluous lines
    std::getline(infile, line);
    std::getline(infile, line);

    std::getline(infile, line);//Optimal value
    std::istringstream iss(line);
    iss >> result.value;

    std::getline(infile, line);//1 superfluous lines

    std::getline(infile, line);//Minimal weight for optimal value.
    std::istringstream iss2(line);
    iss2 >> result.weight;

    while (std::getline(infile, line) && line.rfind("Total", 0) != 0);
    std::string sink;
    std::istringstream iss3(line);
    iss3 >> sink >> sink >> sink >> result.executionTime;

    return result;
}



