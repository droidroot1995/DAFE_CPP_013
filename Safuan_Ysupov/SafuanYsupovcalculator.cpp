//Ysupov Safuan 17.10.20  
/*
Simple calculator

version History:

Revised by Yusupov Safuan in October 2020 (09.10.20)
Revised by Bjarne Stroustrup in may 2007
Revised by Bjarne Stroustrup in August 2006.
Revised by Bjarne Stroustrup in August 2004.
Developed by Bjarne Stroustrup (bs@cs.tamu.edu) in the spring of 2004.

This program implements basic calculator expressions.
Input is made from the CIN stream ; output is made to the cou t stream.

Gram TICA to enter :

Instruction:
 The expression
 Conclusion
 Exit

Conclusion:
 ;
Output:
q

Expression:
Term
 Expression + Term
 Expression-Term

Term:
 Primary expression
 Term * Primary expression
 Term / Primary Expression
 Term % Primary expression

Particleengine :
 The number
 ( Expression )
 - Primary expression
 + Particleengine

Number :
 Literalistically

Input from the cin stream via a Token stream named ts.
*/
#include "std_lib_facilities.h"
#include <iostream>
#include "Variable.h"
#include "Functions.h"
using namespace std;

int main()
{
    try
    {
        cout << "use 'help'" << endl << endl;
        setlocale(LC_ALL, "Russian");
        //Predefined names
        define_name("pi", 3.1415926535);
        define_name("e", 2.7182818284);
        define_name("k", 1000);

        calculate();

        //keep_window_open(); // Keeps the console window open
        return 0;
    }
    catch (runtime_error& e)   //exception
    {
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }

    catch (...)
    {
        cerr << "exception \n";
        keep_window_open("~~");
        return 2;
    }
}