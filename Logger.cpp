//
// Created by LENOVO on 26/04/2020.
//

#include "Logger.h"

Logger::Logger(const std::string &path) : path(path), outfile(path, std::ios_base::app) {}

Logger::~Logger() {
    outfile.close();
}

void Logger::log(TabuType type, std::string instance, Result const& optimalResult, Result const& instanceResult, std::string const& parameters) {
    outfile << time(NULL)
     << ", " << instance << ", " << TABU_TYPE_STRING[type] << ", " << optimalResult.value << ", " << optimalResult.weight << ", " << optimalResult.executionTime
     << ", " << instanceResult.value << ", " << instanceResult.weight << ", " << instanceResult.executionTime;
    if(!parameters.empty())
        outfile << ", " << parameters << "\n";
    else
        outfile << "\n";
}


