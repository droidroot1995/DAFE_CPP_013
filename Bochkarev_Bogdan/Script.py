from math import *
x = None
s = str(input())
exec('def f(x):\n    return ' + s)
print(f(5))
