from pycppad import AD, ADCG, CG, Independent, Value, ADCGFun
import numpy as np

#/***************************************************************************
#                               the model
#*************************************************************************/

# independent variable vector
n = 2

x = np.array([ADCG(CG(0.)),]*n)
x[0] = ADCG(CG(2.))
x[1] = ADCG(CG(3.))

Independent(x)

# dependent variable vector
m=1
y = np.array([ADCG(CG(0)),]*m)

#the model
a = x[0] / ADCG(CG(1.)) + x[1] * x[1]
y[0] = a / ADCG(CG(2.))

fun = ADCGFun(x, y); # the model tape

