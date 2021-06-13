from pycppad import AD, Value


x = AD(2)

print(x)
print(x.Value())
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
