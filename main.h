//
// Created by julia on 31.05.2023.
//

#ifndef COMMONUTILS_LIBRARY_H
#define COMMONUTILS_LIBRARY_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>


namespace Log {
    enum class LogLevel {
        EMERGENCY,
        ALERT,
        CRITICAL,
        ERROR,
        WARNING,
        NOTICE,
        INFORMATIONAL,
        DEBUG,
        VERBOSE,
        FINEST,
        OFF,
        INFO
    };

    void saveStringToFile(const std::string& fileName, const std::string& content) {
        std::ofstream outputFile(fileName, std::ios::app); // Open the file in append mode
        if (outputFile.is_open()) {
            outputFile << content << std::endl; // Append a new line after the content
            outputFile.close();
        } else {
            std::cout << "Unable to open file " << fileName << std::endl;
        }
    }

    void Log(LogLevel level, const std::string& message, const std::string& programName = " Maeve-Development ", bool writeToLogFile = true, bool showTimestamp = false) {
        std::string LogLevelString;
        std::string LogLevelColorCode;
        std::string ResetColorCode = "\033[0m";

        switch (level) {
            case LogLevel::EMERGENCY:
                LogLevelString = "EMERGENCY";
                LogLevelColorCode = "\033[1;35m";
                break;
            case LogLevel::ALERT:
                LogLevelString = "ALERT    ";
                LogLevelColorCode = "\033[1;36m";
                break;
            case LogLevel::CRITICAL:
                LogLevelString = "CRITICAL ";
                LogLevelColorCode = "\033[1;31m";
                break;
            case LogLevel::ERROR:
                LogLevelString = "ERROR    ";
                LogLevelColorCode = "\033[1;31m";
                break;
            case LogLevel::WARNING:
                LogLevelString = "WARNING  ";
                LogLevelColorCode = "\033[1;33m";
                break;
            case LogLevel::NOTICE:
                LogLevelString = "NOTICE   ";
                LogLevelColorCode = "\033[1;37m";
                break;
            case LogLevel::INFORMATIONAL:
                LogLevelString = "INFO     ";
                LogLevelColorCode = "\033[1;32m";
                break;
            case LogLevel::DEBUG:
                LogLevelString = "DEBUG    ";
                LogLevelColorCode = "\033[1;34m";
                break;
            case LogLevel::VERBOSE:
                LogLevelString = "VERBOSE  ";
                LogLevelColorCode = "\033[1;36m";
                break;
            case LogLevel::FINEST:
                LogLevelString = "FINEST   ";
                LogLevelColorCode = "\033[1;35m";
                break;
            case LogLevel::OFF:
                return; // No logging required
            case LogLevel::INFO:
                LogLevelString = "INFO     ";
                LogLevelColorCode = "\033[1;32m";
                break;
        }

        std::string LogMessage;
        std::string LogMessageToSave;

        std::time_t now = std::time(nullptr);
        std::tm* localtime = std::localtime(&now);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime);

        LogMessage += LogLevelColorCode + "[" + programName + "::" + LogLevelString + "] --> " + message + ResetColorCode;
        LogMessageToSave += "[" + programName + "::" + LogLevelString + "] --> " + message + " --> " + std::string(timestamp);
        saveStringToFile(programName + ".log", LogMessageToSave);

        std::cout << LogMessage << std::endl;
    }
}




namespace Branding {

    namespace Debug {

        void writeAsciiArtToFile(const std::string &fileName, const std::string &programName = " Maeve-Development ") {
            Log::Log(Log::LogLevel::DEBUG, "Writing ASCII art to file...", programName);
            std::ofstream outputFile(fileName);
            Log::Log(Log::LogLevel::DEBUG, "Checking if file is open...", programName);
            if (outputFile.is_open()) {
                Log::Log(Log::LogLevel::DEBUG, "File is open, writing ASCII art to file...", programName);
                outputFile << R"(
    ____  ___                      ______               _                                  _
    |  \/  |                      |  _  \             | |                                | |
    | .  . | __ _  _____   _____  | | | |_____   _____| | ___  _ __  _ __ ___   ___ _ __ | |_
    | |\/| |/ _` |/ _ \ \ / / _ \ | | | / _ \ \ / / _ \ |/ _ \| '_ \| '_ ` _ \ / _ \ '_ \| __|
    | |  | | (_| |  __/\ V /  __/ | |/ /  __/\ V /  __/ | (_) | |_) | | | | | |  __/ | | | |_
    \_|  |_/\__,_|\___| \_/ \___| |___/ \___| \_/ \___|_|\___/| .__/|_| |_| |_|\___|_| |_|\__|
                                                              | |
                                                              |_|
    )";
                Log::Log(Log::LogLevel::DEBUG, "ASCII art written to file successfully.", programName);
                Log::Log(Log::LogLevel::DEBUG, "Closing file...", programName);
                outputFile.close();
                Log::Log(Log::LogLevel::DEBUG, "File closed successfully.", programName);
            } else {
                Log::Log(Log::LogLevel::ERROR, "Unable to open the file: " + fileName, programName);
            }
        }
    }

    void writeAsciiArtToFile(const std::string &fileName, const std::string &programName = " Maeve-Development ") {
        std::ofstream outputFile(fileName);
        if (outputFile.is_open()) {
            outputFile << R"(
    ____  ___                      ______               _                                  _
    |  \/  |                      |  _  \             | |                                | |
    | .  . | __ _  _____   _____  | | | |_____   _____| | ___  _ __  _ __ ___   ___ _ __ | |_
    | |\/| |/ _` |/ _ \ \ / / _ \ | | | / _ \ \ / / _ \ |/ _ \| '_ \| '_ ` _ \ / _ \ '_ \| __|
    | |  | | (_| |  __/\ V /  __/ | |/ /  __/\ V /  __/ | (_) | |_) | | | | | |  __/ | | | |_
    \_|  |_/\__,_|\___| \_/ \___| |___/ \___| \_/ \___|_|\___/| .__/|_| |_| |_|\___|_| |_|\__|
                                                              | |
                                                              |_|
    )";
            outputFile.close();
            Log::Log(Log::LogLevel::NOTICE, "ASCII art written to file successfully.", fileName);
        } else {
            Log::Log(Log::LogLevel::ERROR, "Unable to open the file: " + fileName, programName);
        }
    }
}

namespace FileActions {
    namespace Debug {
        namespace FileExists {
            bool fileExists(const std::string &fileName) {
                Log::Log(Log::LogLevel::DEBUG, "Checking if file exists...");
                std::ifstream file(fileName);
                if (file.good()) {
                    file.close();
                    Log::Log(Log::LogLevel::DEBUG, "File exists.");
                    return true;
                } else {
                    Log::Log(Log::LogLevel::DEBUG, "File does not exist.");
                    file.close();
                    return false;
                }
            }

            void createFileIfNotExists(const std::string &fileName, const std::string &programName = " Maeve-Development ") {
                if (!fileExists(fileName)) {
                    std::ofstream file(fileName);
                    Log::Log(Log::LogLevel::NOTICE, "Creating file: " + fileName, programName);
                    if (file.is_open()) {
                        file.close();
                        Log::Log(Log::LogLevel::DEBUG, "File created: " + fileName, programName);
                    } else {
                        Log::Log(Log::LogLevel::ERROR, "Unable to create file: " + fileName, programName);
                    }
                } else {
                    Log::Log(Log::LogLevel::DEBUG, "File already exists: " + fileName, programName);
                }
            }
        }

        bool createFile(const std::string &fileName) {
            Log::Log(Log::LogLevel::DEBUG, "Creating file: " + fileName);
            std::ofstream file(fileName);
            Log::Log(Log::LogLevel::DEBUG, "Checking if file is open...");
            file.close();
            Log::Log(Log::LogLevel::DEBUG, "File created: " + fileName);
            return true;
        }

        bool writeToFile(const std::string &fileName, const std::string &content) {
            Log::Log(Log::LogLevel::DEBUG, "Writing to file: " + fileName);
            std::ofstream outputFile(fileName);
            Log::Log(Log::LogLevel::DEBUG, "Checking if file is open...");
            if (outputFile.is_open()) {
                Log::Log(Log::LogLevel::DEBUG, "File is open, writing to file...");
                outputFile << content;
                Log::Log(Log::LogLevel::DEBUG, "Writing to file successful.");
                outputFile.close();
                Log::Log(Log::LogLevel::DEBUG, "Closing file...");
                return true;
            } else {
                Log::Log(Log::LogLevel::ERROR, "Unable to open the file: " + fileName);
                return false;
            }
        }
    }

    namespace FileExists {
        bool fileExists(const std::string& fileName) {
            std::ifstream file(fileName);
            bool exists = file.good();
            file.close();

            if (exists) {
                Log::Log(Log::LogLevel::INFO, "File exists: " + fileName);
                return true;
            } else {
                Log::Log(Log::LogLevel::INFO, "File does not exist: " + fileName);
                return false;
            }
        }
    }

    void createFileIfNotExists(const std::string& fileName, const std::string& programName = " Maeve-Development ") {
        if (!FileExists::fileExists(fileName)) {
            Log::Log(Log::LogLevel::INFO, "Creating file: " + fileName, programName);
            std::ofstream file(fileName);
            if (file.is_open()) {
                file.close();
                Log::Log(Log::LogLevel::INFO, "File created: " + fileName, programName);
            } else {
                Log::Log(Log::LogLevel::ERROR, "Unable to create file: " + fileName, programName);
            }
        } else {
            Log::Log(Log::LogLevel::INFO, "File already exists: " + fileName, programName);
        }
    }
}

namespace Network {
    namespace Debug {
        namespace checkNetwork {
            bool isNetworkAvailable() {
                Log::Log(Log::LogLevel::DEBUG, "Checking if network is available...");
                std::string command = "ping google.com > NUL";
                Log::Log(Log::LogLevel::DEBUG, "Running command: " + command);
                int returnCode = std::system(command.c_str());
                Log::Log(Log::LogLevel::DEBUG, "waiting for response...");
                if (returnCode == 0) {
                    Log::Log(Log::LogLevel::DEBUG, "Network is available.");
                    return true;
                } else {
                    Log::Log(Log::LogLevel::DEBUG, "Network is not available.");
                    return false;
                }
            }
        }
    }

    namespace checkNetwork {
        bool isNetworkAvailable() {
            Log::Log(Log::LogLevel::INFO, "Checking if network is available...");
            std::string command = "ping google.com > NUL";
            int returnCode = std::system(command.c_str());
            if (returnCode == 0) {
                return true;
            } else {
                return false;
            }
        }
    }
}

namespace CommonActions {

    namespace Debug {
        void CloseOnKeypress() {
            std::cout << "Press any key to exit..." << std::endl;
            Log::Log(Log::LogLevel::DEBUG, "Initiated Console Input", "");
            std::cin.get();
            exit(0);
        }
    }

    void CloseOnKeypress() {
        std::cout << "Press any key to exit..." << std::endl;
        std::cin.get();
        exit(0);
    }
}


#endif //COMMONUTILS_LIBRARY_H