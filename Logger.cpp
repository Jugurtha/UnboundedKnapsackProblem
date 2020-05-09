//
// Created by LENOVO on 26/04/2020.
//

#include "Logger.h"

Logger::Logger(const std::string &path) : path(path), outfile(path, std::ios_base::app) {}

Logger::~Logger() {
    outfile.close();
}

void Logger::log(std::string instance, Result const& optimalResult, Result const& instanceResult) {
    outfile << time(NULL)
     << ", " << instance << ", " << optimalResult.value << ", " << optimalResult.weight << ", " << optimalResult.executionTime
     << ", " << instanceResult.value << ", " << instanceResult.weight << ", " << instanceResult.executionTime << "\n";
}


