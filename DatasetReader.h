//
// Created by CHAKER Jugurtha on 26/04/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H
#define UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "commun.h"



class DatasetReader {
public:
    DatasetReader(const std::string &path);
    Instance getInstance();
    Result getOptimalResult();
public:
    virtual ~DatasetReader();

private:
    std::string path;
    std::ifstream infile;
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H
