'''import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = np.loadtxt("../../KeyFrameTrajectory.txt")

x = data[:,1]
y = data[:,2]
z = data[:,3]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot(x, y, z)

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

plt.show()
'''

import numpy as np
import matplotlib.pyplot as plt

# Load ORB-SLAM3 trajectory file
data = np.loadtxt("../../KeyFrameTrajectory.txt")

# Extract positions
x = data[:,1]
z = data[:,2]

# Create figure
plt.figure(figsize=(8,8))

# Plot trajectory
plt.plot(x, z)

# Labels
plt.xlabel("X Position")
plt.ylabel("Z Position")

# Title
plt.title("ORB-SLAM3 2D Trajectory")

# Equal scaling
plt.axis('equal')

# Grid
plt.grid(True)

# Show plot
plt.show()