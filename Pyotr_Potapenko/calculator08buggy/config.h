#ifndef CONFIG_H
#define CONFIG_H

#include "iomode.h"
#include <string>
#include "std_lib_facilities.h"

class Config {
private:
    Mode inputMode;
    Mode outputMode;
public:
    Config(Mode readMode, Mode writeMode);
    Config(string readMode, string writeMode);

    Mode getInputMode();
    Mode getOutputMode();
    void setInputMode(Mode mode);
    void setOutputMode(Mode mode);
};

Config getConfig();
Config createConfig();
Config readConfig();

#endif // CONFIG_H
