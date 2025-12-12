#include "library_manager/Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>


void Logger::error(const std::string& message) {
    std::cerr << "ERROR: " << message << "\n";
    writeToFile("ERROR", message);
}

void Logger::info(const std::string& message) {
    std::cout << "INFO: " << message << "\n";
    writeToFile("INFO", message);
}


void Logger::warning(const std::string& message) {
    std::cout << "WARNING: " << message << "\n";
    writeToFile("WARNING", message);
}


void Logger::log(const std::string& operation) {
    writeToFile("INFO", operation);
}


void Logger::writeToFile(const std::string& level, const std::string& message) {
    std::ofstream file("log.txt", std::ios_base::app);

    if (file.fail()) {
        std::cerr << "Failed to open file!" << "\n"; 
    } else {
        file << getCurrentTimestamp() << " [" << level << "] " << message << "\n";
    }

    file.close();
}


std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%m-%d-%Y %H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
    
    return ss.str();
}