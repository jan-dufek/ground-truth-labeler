/* 
 * File:   Logger.hpp
 * Author: Jan Dufek
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

using namespace std;

class Logger {
public:
    Logger();
    Logger(string);
    Logger(const Logger& orig);
    virtual ~Logger();
    
    void log_general(string);
    
    void log_general(double);
    
    void close();
    
private:
    
    // General log file
    ofstream general_log_file;

};

#endif /* LOGGER_HPP */

