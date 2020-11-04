#include "printHelp.h"

void printHelp() {
    cout << "\n----HELP----"
            "\n* Calculator Programm *"
            "\n"
            "\n* operations supported: + - % * /"
            "\n* functions supported: sqrt(x), pow(x, y), log(x, y)"
            "\n* after your statement you should leave \';\' symbol"
            "\n* if you want to quit type \"" + quitString + "\""
            "\n* you can create your own variables using # command"
            "\n  like this: # <name> = value"
            "\n  e.g. # a = 12;"
            "\n* you can change value of already created variables"
            "\n  like this: <name> = value"
            "\n  e.g. a = 9;"
            "\n* there are already 3 predefined variables: e, pi, k"
            "\n  e, pi are constant and you can't change them"
            "\n  k, on the other hand, can be changed. k equals 1000 by default"
            "\n*** Example of usage ***"
            "\n  # a = 1;"
            "\n  k = sqrt(a * 4) + pow(2, 2);"
            "\n  " + quitString +
            "\n* That's all, I guess. Thank you for using this app!"
            "\n------------\n";
}
