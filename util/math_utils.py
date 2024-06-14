import math
import numpy as np

def get_angle(x, y):
    norm = get_norm(x, y)
    x_normed = x/norm
    y_normed = -y/norm
    angle = math.atan2(y_normed, x_normed)
    return angle

def get_norm(x, y):
    norm = np.sqrt(x**2 + y**2)
    return norm