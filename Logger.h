//
// Created by LENOVO on 26/04/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_LOGGER_H
#define UNBOUNDEDKNAPSACKPROBLEM_LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "commun.h"
#include <ctime>


class Logger {
public:
    Logger(const std::string &path);
    void log(TabuType type, std::string instance, Result const& optimalResult, Result const& instanceResult, std::string const& parameters);
    virtual ~Logger();

private:
    std::string path;
    std::ofstream outfile;

};


#endif //UNBOUNDEDKNAPSACKPROBLEM_LOGGER_H
