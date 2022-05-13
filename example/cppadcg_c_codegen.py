from pycppad import AD, ADCG, CG, Independent, Value, ADCGFun, CodeHandler, LanguageC, LangCDefaultVariableNameGenerator
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


# /***************************************************************************
# *                        Generate the C source code
# **************************************************************************/

# /**
# * start the special steps for source code generation for a Jacobian
# */
handler = CodeHandler(50)

indVars = np.array([CG(0.)]*n)
handler.makeVariables(indVars)

jac = fun.Jacobian(indVars)

langC = LanguageC("double", 3)
nameGen = LangCDefaultVariableNameGenerator("y","x","v","array","sarray")
code = handler.generateCode(langC, jac, nameGen, "source")
output = code.splitlines()
assert(output[0]=='   y[1] = 0.5 * x[1] + 0.5 * x[1];')
assert(output[1]=='   // dependent variables without operations')
assert(output[2]=='   y[0] = 0.5;')
print(code)
