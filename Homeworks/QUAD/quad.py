import numpy as np
from scipy.integrate import quad

f2 = lambda x: 1/np.sqrt(x)
f4 = lambda x : np.log(x)/np.sqrt(x)

eps = 1e-3
acc = 1e-3
a = 0
b = 1
res2 = quad(f2, a, b, full_output = True, epsabs = acc, epsrel = eps)
res4 = quad(f4, a, b, full_output = True, epsabs = acc, epsrel = eps)
print("Value of integral for 1/sqrt(x) from 0 to 1 is", res2[0], ". Amount of evals is", res2[2]['neval'])
print("Value of integral for ln(x)/sqrt(x) from 0 to 1 is", res4[0], ". Amount of evals is", res4[2]['neval'])