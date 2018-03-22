/* 
 * File:   Logger.cpp
 * Author: Jan Dufek
 */

#include "Logger.hpp"

Logger::Logger(string name) {

    general_log_file.open(name + ".txt");

}

Logger::Logger(const Logger& orig) {
}

Logger::~Logger() {
    close();
}

void Logger::log_general(string message) {
    general_log_file << message;
}

void Logger::log_general(double message) {
    general_log_file << message;
}

void Logger::close() {
    general_log_file.close();
}