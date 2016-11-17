import matplotlib.pyplot as plt
import numpy as np

#The values we collected to calibrate our function, in the form -  lux/fc: sensor value
lux_calibration = {1647:884, 624:859, 211:745, 210:744, 98: 678, 43: 525, 44: 483, 6:167, 0:34}
fc_calibration = {58:859, 19.5:745, 19.3:744, 9.2:678, 4:525, 3.6:483, 0.4:167, 0:34}
#Turns the dictionary of values into two lists
keys, values = zip(*lux_calibration.items())

#finds a 3rd degree polynomial that fits the data, with the coefficients a, b, c, and d
a, b, c, d, e = np.polyfit(values, keys, 4)
print a, b, c, d, e

#create a list of the values that the calibrated function would return given the distances used to calibrate
bestfit = []
for key in keys:
    bestfit.append(a*key**4 + b*key**3 + c*key**2 + d*key + e)

#create the values for the curve 
x = np.linspace(0,1010,500)
y = a*x**4 + b*x**3 + c*x**2 + d*x + e

#plot the Calibration Values with blue dots
plt.plot(values, keys, 'bo')
plt.plot(x, y)

#the values we collected to test our calibration function
lux_calibration_test = {395: 811, 508:843, 678:866, 20:368, 54:568, 2444:942, 213:557, 422:813, 305:701}

# #Turn the dictionary of test values into two lists
keys_test, values_test = zip(*lux_calibration_test.items())

# #plot the Test Values with red dots
plt.plot(values_test,keys_test,'ro')

# #label and format the graph
plt.title("Sensor Value to Light (lux) Calibration Test")
plt.xlabel("Sensor Output Value")
plt.ylabel("Light (lux)")
legend = plt.legend(['Calibration Values', 'Fit Curve', 'Test Values'])
legend.get_frame().set_linewidth(0.0)

plt.show()