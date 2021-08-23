# python equivalent of the CppAD example https://coin-or.github.io/CppAD/doc/addeq.cpp.htm

from pycppad import AD, Independent, ADFun, Value
import numpy as np

# domain space vector
n = 1
x0 = 0.5

x = np.array([AD(x0)] * n)

# declare independent variables and start tape recording
Independent(x)

# range space vector
m = 2
y = np.zeros(m, dtype=AD)
y[0] = x[0]
# initial value
y[0] += AD(2)
# AD<double> += int
y[0] += AD(4.)
# AD<double> += double
y[0] += x[0]
y[1] = y[0]
# use the result of a compound assignment

# create f: x -> y and stop tape recording
f = ADFun(x, y)
# input("raw_input")

# f.optimize("no_compare_op")

assert Value(y[0]) == x0 + 2. + 4. + x0
assert Value(y[1]) == Value(y[0])

dx = np.zeros(n)
dy = np.zeros(m)

dx[0] = 1.
dy = f.Forward(1, dx)
assert dy[0] == 2.
assert dy[1] == 2.

# reverse computation of derivative of y[0]
w = np.zeros(m)
dw = np.zeros(n)

w[0] = 1.
w[1] = 0.
dw = f.Reverse(1, w)

assert dw[0] == 2.
