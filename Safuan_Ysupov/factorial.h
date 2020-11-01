//factorial counting function 
int factorial(double x)
{
    int pr = 1;
    for (int i = 1; i <= x; i++)
        pr *= i;
    return pr;
}

