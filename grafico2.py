from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt 
import numpy as np


n_angles = 72
n_radii = 4

radii = np.linspace(0.125,1.0, n_radii)
angles = np.linspace(0, 2*np.pi, n_angles, endpoint = True)
angles = np.repeat(angles[...,np.newaxis], n_radii, axis = 1)

x = np.append(0, (radii*np.cos(angles)).flatten())
y = np.append(0, (radii*np.sin(angles)).flatten())
y1= np.append(0, (radii*np.cos(angles)).flatten())
 
z = (-2/5)*x - (2/5)*y + (11.5667/5)
x1 = 0.76667
y1 = 0.433333
z1 = 1.833334
x2 = np.append(0, (radii*np.cos(angles)).flatten())
y2 = -x2 + 1.200015



fig = plt.figure()
#ax = fig.add_subplot(111,projection = '3d')
ax = fig.gca(projection = '3d')
ax.plot_trisurf(x,y,z, cmap = 'Oranges', linewidth = 0.4)
ax.scatter(x1,y1,z1, c='b', marker ='o')

plt.show()
