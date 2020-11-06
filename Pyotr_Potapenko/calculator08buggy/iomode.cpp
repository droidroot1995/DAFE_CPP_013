#include "iomode.h"
#include "iomodeutils.h"
#include <fstream>
#include "iostream"

void setInputMode(Config& config) {
    Mode readMode = config.getInputMode();
    if (readMode == Mode::FILE)
        freopen("input.txt", "r", stdin);
    return;
}

void setOutputMode(Config& config) {
    Mode writeMode = config.getOutputMode();
    if (writeMode == Mode::FILE)
        freopen("output.txt", "w", stdout);
    return;
}
