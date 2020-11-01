// function to convert to lowercase
#include <string>
using namespace std;

void tolower(string& s)
{
    for (char& x : s)
        x = tolower(x);
}