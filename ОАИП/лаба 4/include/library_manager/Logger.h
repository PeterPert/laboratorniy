#pragma once


#include <string>


class Logger {
    public:
        static void log(const std::string& operation);
    
        static void error(const std::string& message);
        static void warning(const std::string& message);
        static void info(const std::string& message);
        
    private:
        static void writeToFile(const std::string& level, const std::string& message);
        static std::string getCurrentTimestamp();
};