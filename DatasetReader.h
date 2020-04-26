//
// Created by CHAKER Jugurtha on 26/04/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H
#define UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BranchAndBound.h"


struct Instance
{
    int  maxWeight;
    Objects objects;
};


class DatasetReader {
public:
    DatasetReader(const std::string &path);
    Instance getInstance();
private:
public:
    virtual ~DatasetReader();

private:
    std::string path;
    std::ifstream infile;
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_DATASETREADER_H
