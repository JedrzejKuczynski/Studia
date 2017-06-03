import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import numpy as np
from matplotlib import style
from scipy.interpolate import spline

style.use("ggplot")

#ax1 = plt.subplot2grid((1,1), (0,0))

x = np.array([0.5, 1.25, 2.5, 5, 7.5, 10, 12.5])
y = np.array([0.0059, 0.0120, 0.0216, 0.0488, 0.0433, 0.0383, 0.0354])
#x_smooth = np.linspace(x.min(), x.max(), 300)
#y_smooth = spline(x, y, x_smooth)
#ax1.set_title("Wykres zależności szybkości reakcji katalizowanej przez NADP-ME od stężenia jabłczanu")
#ax1.set_xlabel("Stężenie substratu [mM]")
#ax1.set_ylabel("Szybkość reakcji [ΔA]")
#ax1.plot(x_smooth, y_smooth)
#ax1.grid(True)

ax2 = plt.subplot2grid((1,1), (0,0))
x2 = np.array([1/s for s in x])
y2 = np.array([1/v for v in y])
print(x2, y2)
ax2.set_title("Wykres Lineweara-Burka")
ax2.set_xlabel("Odwrotność stężenia substratu [1/mM]")
ax2.set_ylabel("Odwrotność szybkości reakcji [1/ΔA]")
ax2.plot(x2, y2)
ax2.grid(True)


"""x = np.arange(10)
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
ax4.grid(True)"""


plt.show()