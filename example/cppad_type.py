from pycppad import AD, Value, Independent
x = AD(2)

print(x)
print(Value(x))

y = AD(3)

z = x+y
print(z)
z2 = x*y
print(z2)
z3 = x-y
print(z3)
z4 = x/y
print(z4)


import numpy as np
dAD = np.dtype(AD)

x = np.array([AD(1), AD(2)], dtype=dAD)
y = np.array([AD(3), AD(4)], dtype=dAD)

Independent(x)

z = x+y
print(z)

z2 = x-y
print(z2)
