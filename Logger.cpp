//
// Created by LENOVO on 26/04/2020.
//

#include "Logger.h"

Logger::Logger(const std::string &path) : path(path), outfile(path, std::ios_base::app) {}

Logger::~Logger() {
    outfile.close();
}

void Logger::log(std::string instance, int value, int weight, double execTime) {
    outfile << time(NULL) << ", " << instance << ", " << value << ", " << weight << ", " << execTime << "\n";
}
