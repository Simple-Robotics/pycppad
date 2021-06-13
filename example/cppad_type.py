from pycppad import AD, Value


x = AD(2)

print(x)
print(x.Value())
print(Value(x))
