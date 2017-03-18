import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import numpy as np
from matplotlib import style

style.use("ggplot")

ax1 = plt.subplot2grid((2,2), (0,0))

x = np.arange(10)
y = [2,4,3,6,7,10,12,5,1,9]
ax1.plot(x, y)
ax1.grid(True)

r = np.arange(0, 3, 0.01)
theta = 2*np.pi*r

ax2 = plt.subplot2grid((2,2), (0,1), projection = "polar")
ax2.plot(theta, r)
ax2.set_rmax(2.0)
ax2.grid(True)

x = np.arange(10)
y = [2,4,3,6,7,10,12,5,1,9]
z = [4,5,1,3,12,6,15,4,8,7]
ax3 = plt.subplot2grid((2,2), (1,0), projection = "3d")
ax3.scatter(x, y, z)
ax3.grid(True)

x = np.arange(10)
y = [2,4,3,6,7,10,12,5,1,9]
z = np.zeros(10)
dx = np.ones(10)
dy = np.ones(10)
dz = np.arange(10)
ax4 = plt.subplot2grid((2,2), (1,1), projection = "3d")
ax4.bar3d(x, y, z, dx, dy, dz)
ax4.grid(True)


plt.show()