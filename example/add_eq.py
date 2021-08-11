# python equivalent of the CppAD example https://coin-or.github.io/CppAD/doc/addeq.cpp.htm

from pycppad import AD, Independent, ADFun, Value
import numpy as np


# domain space vector
n = 1;
x0 = 0.5

x = np.array([AD(x0),]*n)

# declare independent variables and start tape recording
Independent(x)

# range space vector
m = 2;
y = np.array([AD(0.),]*m)
y[0] = x[0];         # initial value
y[0] += AD(2);           # AD<double> += int
y[0] += AD(4.);          # AD<double> += double
y[0] += x[0]
y[1] = y[0]; # use the result of a compound assignment

# create f: x -> y and stop tape recording
f = ADFun();
input("raw_input")
f.Dependent(x,y)

f.optimize("no_compare_op")

# check value
assert(Value(y[0]) == x0+2.+4.+x0);

dx = np.zeros(n)
dy = np.zeros(m)

dx[0] = 1.
print("x")
dy = f.Forward(1 ,dx)

print("y")
