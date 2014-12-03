import matplotlib.pyplot as plt
import numpy as np

pen10cm = np.fromfile("test-2d_penumbra_10cm", dtype=np.float64)
pen20cm = np.fromfile("test-2d_penumbra_20cm", dtype=np.float64)

pen30cm = np.fromfile("test-2d_penumbra_30cm", dtype=np.float64)
pen40cm = np.fromfile("test-2d_penumbra_40cm", dtype=np.float64)

#dd = np.fromfile("test-2d_ddose", dtype=np.float64)
#map = map.reshape((1000,1000))

#plt.imshow(map)

xvals = np.linspace(-5, 5, 1000)
xvals_dd = np.linspace(-60, 0, 1000)
plt.plot(xvals, pen10cm)
plt.show()
plt.plot(xvals, pen20cm)
plt.show()
plt.plot(xvals, pen30cm)
plt.show()
plt.plot(xvals, pen40cm)

plt.show()

#plt.plot(xvals_dd, dd)
#plt.show()
