#include "config.h"
#include <fstream>
#include <filesystem>

Mode Config::getInputMode(){
    return inputMode;
}

Mode Config::getOutputMode(){
    return outputMode;
}

void Config::setInputMode(Mode mode){
    inputMode = mode;
}

void Config::setOutputMode(Mode mode){
    outputMode = mode;
}

Config::Config(Mode readMode, Mode writeMode) {
    inputMode = readMode;
    outputMode = writeMode;
}

Config::Config(string readMode, string writeMode) {
    if (readMode == "FILE") {
        inputMode = Mode::FILE;
    } else if (readMode == "CONSOLE") {
        inputMode = Mode::CONSOLE;
    }
    if (writeMode == "FILE") {
        outputMode = Mode::FILE;
    } else if (writeMode == "CONSOLE") {
        outputMode = Mode::CONSOLE;
    }
}

bool isFileExist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

Config getConfig() {
    try {
        if(isFileExist("config.txt")) {
            return readConfig();
        }
    }  catch (...) {
        error("Error while reading config");
    }
    return createConfig();
}

Config readConfig() {
    ifstream is = ifstream("config.txt");
    string readMode, writeMode;
    is >> readMode >> writeMode;
    is.close();
    return Config(readMode, writeMode);
}

Config createConfig() {
    ofstream os = ofstream("config.txt");
    os << "CONSOLE\nCONSOLE";
    os.close();
    return readConfig();
}

